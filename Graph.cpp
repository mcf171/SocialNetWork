//
//  Graph.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "Graph.hpp"
#include <iostream>

#include "Node.hpp"
#include "Tree.hpp"
#include "Edge.hpp"
#include "Load.hpp"
#include "Query.h";
using namespace std;

/*
 * 根据给定主题改变图中所有的边权重
 * @param q 查询语句
 */
void Graph::changeGraph(Query q){
    map<int,Node>::iterator nodeItera;
    
    for (nodeItera = this->nodes.begin(); nodeItera != this->nodes.end(); nodeItera++) {
    
        map<int,Edge*>::iterator edgeItera;
        
        for (edgeItera = nodeItera->second.neighbourEdge.begin(); edgeItera != nodeItera->second.neighbourEdge.end(); edgeItera++) {
            
            //cout<< edgeItera->second->realDistribution[0]<<" "<< edgeItera->second->realDistribution[1]<<" "<<edgeItera->second->realDistribution[2]<<endl;
            edgeItera->second->weight = edgeItera->second->realDistribution[0] * q.topicDistribution[0] + edgeItera->second->realDistribution[1] * q.topicDistribution[1]+edgeItera->second->realDistribution[2] * q.topicDistribution[2];
        }
    }
}

void Graph::Load()
{
	int* nodedata = new int[NNODE];
	int* edgedata = new int[NEDGE*2];
	double* propdata = new double[NEDGE*DIM];
	LoadGraphData(nodedata,edgedata,propdata);

	for (int i = 0; i < NNODE; i++)
	{
		Node* node = new Node(nodedata[i]);
		nodes[nodedata[i]]=*node;
	}
	for (int i = 0; i < NEDGE; i++)
	{
		int sourceId=edgedata[2*i];
		int targetId=edgedata[2*i+1];
		Edge* edge = new Edge(i,&nodes[sourceId],&nodes[targetId],&propdata[DIM*i]);
		edges.push_back(*edge);
	}

}

Node Graph::findNode(int number)
{
	return nodes[number];
}



double getLocalDistance(Tree* tree, double theta)
{
    double distance = 0;
    if(tree->node->influence < theta)
        distance +=tree->node->influence;
    vector<Tree*>::iterator nextNodeIter;
    
    for ( nextNodeIter = tree->nextNode.begin(); nextNodeIter != tree->nextNode.end(); nextNodeIter++) {
        
        distance += getLocalDistance(*nextNodeIter, theta);
    }
    tree->node->hat_delta_sigma_p = distance;
    
    return distance;
}


/*
 * 在构建了每个节点的MIA之后可以计算每个节点的影响力上界
 * @param g 社交网络图
 */

void calculateGraph(Graph& g)
{
    map<int,Node>::iterator nodeItera;
    
    for (nodeItera = g.nodes.begin(); nodeItera != g.nodes.end(); nodeItera++) {
        
        //计算影响力
		double distance = hat_delta_p_u((nodeItera->second).MIA);
        
        //因为在上一个函数中多算了自己的影响力，所以减去自己的影响力
        (nodeItera->second).influence = distance - 1;
        
        //下述代码为了调试
       // cout<<"the weight of "<<(nodeItera->second).number<<" is :"<<distance-1<<endl;
    }
}

/*
 * 计算MIA树的影响力
 * @param tree，MIA树
 */
double hat_delta_p_u(Tree* tree)
{

    double distance = tree->node->influence;
    vector<Tree*>::iterator nextNodeIter;
    
    for ( nextNodeIter = tree->nextNode.begin(); nextNodeIter != tree->nextNode.end(); nextNodeIter++) {

        //迭代计算子树的影响力
        distance += hat_delta_p_u(*nextNodeIter);
    }
    
    return distance;
}

/*
 * 利用Dijstra的思想构建一个基于节点node的MIA模型
 * @param MIA，需要构建的MIA树
 * @param inputNode，需要构建MIA的节点
 * @param g 社交网络图
 */
void Dijkstra(Graph g, Node inputNode,Tree* MIA)
{
    //S记录已经存在在MIA模型中的节点

	Node* startNode = new Node(inputNode);

    map<int, Node> S;
    //现将根节点放入S中
	S[startNode->number]=*startNode;
    
    //构建优先队列从而挑选出当前到以后节点集合S中最小的路径，temp是用于辅助输出，可以没有。
    priority_queue<Edge*,vector<Edge*>,EdgeCompare> edges,temp;
    map<int,Edge*>::iterator iterEdge;
    
    //首先将所有的邻边加入优先队列edges中
    for(iterEdge = startNode->neighbourEdge.begin(); iterEdge != startNode->neighbourEdge.end(); iterEdge++){

        edges.push(iterEdge->second);
    }
    

    //初始化MIA的第一个节点为自己
    MIA->node = startNode;
    MIA->node->influence = 1;
    
    //当还存在边的时候，即可能还有节点可以加入S时进行循环构建
    while (!edges.empty())
    {
        
        Edge* edge = edges.top();
        edges.pop();
 
        //边的两端只要有一个节点不在集合S中则加入MIA中
		if(!findKey(S, edge->targetNodeId) || !findKey(S, edge->sourceNodeId)){
            
            //下面则是构建MIA模型中的一个点
            //首先获取边的源节点，查找源节点在MIA中的位置
            Tree* sourceNode = findNode(MIA,edge->sourceNode);
            
            //创建节点的下一层节点
            Tree* treeNext = new Tree();
            
            //获取目标节点
			Node* targetNode = new Node(*edge->targetNode);
            
            //将节点状态设置为initial
            targetNode->currentStatus = initial;
            
            //下一层节点设置为目标节点
            treeNext->node = targetNode;
            
            //设置下一层节点的权重
            treeNext->node->weight = edge->weight;

            //如果是根节点则直接赋予权重，否则需要用当前节点到根节点的距离*权重
            if (sourceNode->node->number == startNode->number) 
                treeNext->node->influence = edge->weight;
            else
                treeNext->node->influence = edge->distance*edge->weight;
            
            //设置源节点的下一层节点
            sourceNode->nextNode.push_back(treeNext);
            
            S[edge->targetNodeId] = *edge->targetNode;
            
            //这一步是对于新加入的点同时将这个点的可达的点全部加入Edge中
            for(iterEdge = edge->targetNode->neighbourEdge.begin(); iterEdge != edge->targetNode->neighbourEdge.end(); iterEdge ++)
            {
				if(!findKey(S, iterEdge->second->targetNodeId) || !findKey(S, iterEdge->second->sourceNodeId)){
                    iterEdge->second->distance = iterEdge->second->distance*sourceNode->node->influence;
                    edges.push(iterEdge->second);
                }
            }
            
            //下面代码是为了测试用的
            /*
            long size = edges.size();
            temp = edges;
            for(int i = 0 ; i < size; i ++)
            {
                Edge* edge = temp.top();
                cout<<edge->sourceNode->number<<" "<<edge->targetNode->number<<" "<<edge->weight<<" "<<edge->distance<<endl;
                temp.pop();
            }
            cout<<"------"<<endl;
            */
            
        }

    }
    
     
};

void Dijkstra(Graph g, Tree* MIA,map<int, Node> seeds)
{
    //S记录已经存在在MIA模型中的节点
    
    
    map<int, Node> S;
    
    //构建优先队列从而挑选出当前到以后节点集合S中最小的路径，temp是用于辅助输出，可以没有。
    priority_queue<Edge*,vector<Edge*>,EdgeCompare> edges,temp;
    map<int,Edge*>::iterator iterEdge;
    map<int,Node>::iterator iterNode;

    //首先设置Node到自己的距离为1
    for (iterNode = seeds.begin();  iterNode != seeds.end();  iterNode++) {
        
        for(iterEdge = iterNode->second.neighbourEdge.begin(); iterEdge != iterNode->second.neighbourEdge.end(); iterEdge++){
            (iterEdge->second)->distance = 1;
            edges.push(iterEdge->second);
        }
        iterNode->second.influence = 1;
        S[iterNode->second.number] = iterNode->second;
    }
    //初始化MIA的第一个节点为自己
    MIA->seeds = seeds;

    
    //当还存在边的时候，即可能还有节点可以加入S时进行循环构建
    while (!edges.empty())
    {
        
        Edge* edge = edges.top();
        edges.pop();
        
        //边的两端只要有一个节点不在集合S中则加入MIA中
        if(!findKey(S, edge->targetNodeId) || !findKey(S, edge->sourceNodeId)){
            
            //下面则是构建MIA模型中的一个点
            Tree* sourceNode = findNodes(MIA,edge->sourceNode);
            Tree* treeNext = new Tree();
            Node* targetNode = new Node(*edge->targetNode);
            //targetNode->neighbourEdge = edge->targetNode->neighbourEdge;
            //targetNode->number = edge->targetNode->number;
            targetNode->currentStatus = initial;
            treeNext->node = targetNode;
            treeNext->node->weight = edge->weight;
            //treeNext->node->realTopicDistribute = edge->realDistribution;
            treeNext->node->influence = edge->distance*edge->weight;
            sourceNode->nextNode.push_back(treeNext);
            
            S[edge->targetNodeId] = *edge->targetNode;
            
            //这一步是对于新加入的点同时将这个点的可达的点全部加入Edge中
            for(iterEdge = edge->targetNode->neighbourEdge.begin(); iterEdge != edge->targetNode->neighbourEdge.end(); iterEdge ++)
            {
                if(!findKey(S, iterEdge->second->targetNodeId) || !findKey(S, iterEdge->second->sourceNodeId)){
                    iterEdge->second->distance = iterEdge->second->distance*sourceNode->node->influence;
                    edges.push(iterEdge->second);
                }
            }
            
            /*
             long size = edges.size();
             temp = edges;
             for(int i = 0 ; i < size; i ++)
             {
             Edge* edge = temp.top();
             cout<<edge->sourceNode->number<<" "<<edge->targetNode->number<<" "<<edge->weight<<" "<<edge->distance<<endl;
             temp.pop();
             }
             cout<<"------"<<endl;
             */
            
        }
        
    }
    
    
};


