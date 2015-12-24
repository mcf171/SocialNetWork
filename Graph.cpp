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
using namespace std;
/*
Edge Graph::findeEdgeFromTwoNode(Node sourceNode, Node targetNode)
{
    
    Edge edge;
    edge.sourceNode = &sourceNode;
    edge.targetNode = &targetNode;
    vector<Edge>::iterator iter;
    iter = find(this->edges.begin(), this->edges.end(), edge);
    if( iter != (this->edges.end()))
        edge = *iter;
    
    return edge;
}
*/

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



void calculateGraph(Graph& g)
{
    map<int,Node>::iterator nodeItera;
    for (nodeItera = g.nodes.begin(); nodeItera != g.nodes.end(); nodeItera++) {
        
		double distance = hat_delta_p_u((nodeItera->second).MIA);
        (nodeItera->second).influence = distance - 1;
        cout<<"the weight of "<<(nodeItera->second).number<<" is :"<<distance-1<<endl;
    }
}

double hat_delta_p_u(Tree* tree)
{

    double distance = tree->node->influence;
    vector<Tree*>::iterator nextNodeIter;
    
    for ( nextNodeIter = tree->nextNode.begin(); nextNodeIter != tree->nextNode.end(); nextNodeIter++) {
        
        distance += hat_delta_p_u(*nextNodeIter);
    }
    
    return distance;
}

/*
 * 利用Dijstra的思想构建一个基于节点node的MIA模型
 * @param MIA，需要构建的MIA树
 * @param g 社交网络图
 */
void Dijkstra(Graph g,Node startNode,Tree* MIA)
{
    //S记录已经存在在MIA模型中的节点
    map<int, Node> S;
	S[startNode.number]=startNode;
    
    //构建优先队列从而挑选出当前到以后节点集合S中最小的路径，temp是用于辅助输出，可以没有。
    priority_queue<Edge*,vector<Edge*>,EdgeCompare> edges,temp;
    map<int,Edge*>::iterator iterEdge;
    
    //首先设置Node到自己的距离为1
    for(iterEdge = startNode.neighbourEdge.begin(); iterEdge != startNode.neighbourEdge.end(); iterEdge++){
		(iterEdge->second)->distance = 1;
        edges.push(iterEdge->second);
    }
    

    //初始化MIA的第一个节点为自己
    MIA->node = &startNode;
    MIA->node->influence = 1;
    
    //当还存在边的时候，即可能还有节点可以加入S时进行循环构建
    while (!edges.empty())
    {
        
        Edge* edge = edges.top();
        edges.pop();
 
        //边的两端只要有一个节点不在集合S中则加入MIA中
		if(!findKey(S, edge->targetNodeId) || !findKey(S, edge->sourceNodeId)){
            
            //下面则是构建MIA模型中的一个点
            Tree* sourceNode = findNode(MIA,edge->sourceNode);
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
            
            sourceNode->node->dijkstraEdge.push_back(edge);
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
    
     cout<<"ts"<<endl;
};


