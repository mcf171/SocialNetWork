//
//  BestEffort.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "BestEffort.hpp"
#include "Graph.hpp"
#include "Query.h"
#include "Node.hpp"
#include "Edge.hpp"
#include "Tree.hpp"
#include <vector>

double hat_delta_theta(Node u,map<int, Node>S,Query q)
{
    double result = 0;
    
    result = hat_delta_p_u(u.MIA) - 1;
    
    if (S.size() != 0) {
        
        result = (1-u.ap_node_S_gamma)*result;
    }
    
    return  result;
}

//针对LocalGraph算法，当进行在线查询时进行重构MIA
void preprocessOnline(Graph&g, Query q)
{
    map<int, Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
		Node node = nodeIter->second;
        
        map<int, Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = edgeIter->second;
            
            double distance = q.topicDistribution[0]*edge->realDistribution[0]+q.topicDistribution[1]*edge->realDistribution[1]+q.topicDistribution[2]*edge->realDistribution[2];
            edge->distance = distance;
            edge->weight = distance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
		Dijkstra( nodeIter->second,(nodeIter->second.MIA));
    }
}


/*
 * 基于Precomputation的方法
 * precomputation方法只选取每条边上topic分布最大的topic
 * @param g 社交网络图
 */

void precomputationBased(Graph& g)
{
    
    map<int, Node>::iterator nodeIter;

    //对于图中的每个节点都将边设置为最大的topic值
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {

        //获取每个节点
		Node node = nodeIter->second;
        
        map<int, Edge*>::iterator edgeIter;
        (*nodeIter).ap_node_S_gamma = 1.0;
        //获取节点的每个邻边
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
			Edge* edge = edgeIter->second;

            double maxDistance = 0;

			for (int i = 0; i < DIM; i++)
			{
				if(edge->realDistribution[i] > maxDistance)
                    maxDistance = edge->realDistribution[i];
			}
            edge->distance = maxDistance;
            edge->weight = maxDistance;
            edge->isVisited = false;
        }
    }
    
    //对每个节点计算构建MIA
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
		Dijkstra( nodeIter->second,(nodeIter->second.MIA));

    }
    
    //cout<<"create MIA";
}

void getLocalGraph(Tree tree,double theta,vector<Node> &nodes){
    
    if (tree.node->influence > theta)
        nodes.push_back(*tree.node);
    
    vector<Tree*>::iterator iterator;
    for (iterator = tree.nextNode.begin(); iterator != tree.nextNode.end(); iterator++)
        getLocalGraph(*(*iterator), theta, nodes);
    
}

/*
* localGraph算法是基于Precomputation算法的，然后通过Precomputation算法构建的图再构建一个子图
* @param g 社交网络图
* @param theta，用户自定义的阈值
* @param q 在线
*/
void localGraphBased(Graph& g,double theta, Query q)
{
    map<int, Node>::iterator nodeIter;
    precomputationBased(g);
/*
for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
		Node node = nodeIter->second;
        
        map<int,Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = edgeIter->second;
            //vector<double>::iterator distanceIter;
            double maxDistance = 0;
            //for (distanceIter = edge->realDistribution.begin(); distanceIter != edge->realDistribution.end(); distanceIter++) {
            //    if(*distanceIter > maxDistance)
            //        maxDistance = *distanceIter;
            //}
			for (int i = 0; i < DIM; i++)
			{
				if(edge->realDistribution[i] > maxDistance)
                    maxDistance = edge->realDistribution[i];
			}
            edge->distance = maxDistance;
            edge->weight = maxDistance;
        }
    }
*/

    //得到每个User的hat_gama;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( nodeIter->second,(nodeIter->second.MIA));
        double distance = getLocalDistance(nodeIter->second.MIA, theta);

     //   cout<<"the hat_gama of "<<(*nodeIter).number<<" is :"<<distance<<endl;
    }
    
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        Node node = nodeIter->second;
        vector<Node> nodes;
        nodes.clear();
        getLocalGraph(*node.MIA, theta, nodes);
        
        //tempNode.push_back(*nodeIter.)
    }

}

void neighborhoodBased(Graph& g)
{
    map<int, Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
        Node node = nodeIter->second;
        
        map<int, Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = edgeIter->second;
            //vector<double>::iterator distanceIter;
            double maxDistance = 0;
            //for (distanceIter = edge->realDistribution.begin(); distanceIter != edge->realDistribution.end(); distanceIter++) {
            //    if(*distanceIter > maxDistance)
            //        maxDistance = *distanceIter;
            //}
			for (int i = 0; i < DIM; i++)
			{
				if(edge->realDistribution[i] > maxDistance)
                    maxDistance = edge->realDistribution[i];
			}
            edge->distance = maxDistance;
            edge->weight = maxDistance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( nodeIter->second,(nodeIter->second.MIA));
    }
}

double estInfUB(Node node, Graph g, double theta)
{
    double maxInfluence;
    
    return maxInfluence;
}

/*
 * 离线部分主要功能计算每个点的最大影响上界
 * 在Precomputation算法中是脱离了在线部分的查询Q，但是对于LocalGraph算法是需要结合在线查询的Q，但是只计算影响力大的点
 * @param g 社交网络图
 * @param theta 用户自定义阈值
 * @param bestEffort bestEffort算法对象
 * @param q 查询语句
 */

void bestEffortOffline(Graph g, double theta, BestEffort& bestEffort,Query q,algorithm chooseAlgorithm)
{
    
    //获取图中所有的Users
    map<int, Node> nodes = g.nodes;
    

    if (chooseAlgorithm == precomputation) {
        //precomputaion算法
        precomputationBased(g);
    }
    else if(chooseAlgorithm == localGraph){
        //LocalGraph算法
        localGraphBased(g, theta, q);
    }

    //将计算后的节点插入优先队列
	for (map<int, Node>::iterator iter=nodes.begin(); iter!=nodes.end(); iter++)  
    {  
		iter->second.influence = iter->second.hat_delta_sigma_p;
        bestEffort.L.push(iter->second);
    }  
    
    
}



/*
 * 在线部分主要计算在给定主题分布下的精确上界
 */

void bestEffortOnline(Graph g ,Query q, double theta, BestEffort& bestEffort,algorithm chooseAlgorithm)
{
    //Initial an empty heap H and set S
    auto &H = bestEffort.H;
    map<int, Node> S;
    
    auto &L = bestEffort.L;
    //初始化一个空的最大堆
    while (!H.empty()) {
        H.pop();
    }

    S.clear();
    //预处理在线节点针对LocalGraph算法，如果不是LocalGraph算法，进行注释
    if(chooseAlgorithm == localGraph)
        preprocessOnline(g, q);
    
    //K次循环找到所有合适的种子
    for (int i = 0; i < q.k ; i++)
    {

        
        while (!H.empty())
        {
            //从离线的优先队列中和最大堆中考虑是否加入新的元素
            insertCandidates(L, H);
            
            //从堆顶取一个元素
            Node u = H.top();
            H.pop();
            
            //如果是初始状态那么久进一步计算在gama主题分布下的上界
            if (initial == u.currentStatus)
            {
                double sigma_new = hat_delta_theta(u, S, q);
                u.currentStatus = bounded;
                u.influence = sigma_new;
                H.push(u);
            }
            //如果已经是gamga主题分布下的上界则计算精确的上界
            else if (bounded == u.currentStatus)
            {
                double sigma_new = CalcMargin(u, g, theta, q, S);
                u.currentStatus = exact;
                u.influence = sigma_new;
                H.push(u);
            }
            //如果已经是精确上界则直接弹出
            else if (exact == u.currentStatus)
            {
				S[u.number]=u;
                vector<Node>::iterator itertor;
                for (itertor = g.nodes.begin(); itertor != g.nodes.end(); itertor ++) {
                    
                    if(!findNode(S, *itertor))
                       (*itertor).ap_node_S_gamma =  calAP(*itertor, S, q);
                    
                }
                
                break;
            }
        }//end while    
    }//end for
}


/*
	Adding posible candidates from L
 */
void insertCandidates(priority_queue<Node> &L, priority_queue<Node> &H)
{
    //return if L or H is empty
    if (L.empty() || H.empty())
    {
        return;
    }
    
    //insertion process until H.top > L.top
    while (!L.empty())
    {
        if (H.top() <= L.top())
        {
            H.push(L.top());
            L.pop();
        }
        else
        {
            break;
        }
    }
}


void initEdge(Graph g)
{
    
}


double sigma(vector<Node> nodes, Graph g ,Query q)
{
    
    vector<Node>::iterator itertor;
    double result = 0;
    for(itertor = g.nodes.begin(); itertor != g.nodes.end() ; itertor ++)
        calAP(*itertor, nodes, q );
    
    return 0;
}

/*
	CALCMARGIN
 */
double CalcMargin(Node u, Graph g, double theta, Query gamma, map<int, Node> S)
{
    double res = 0.0;
    
    priority_queue<Node> M;
    u.influence = 1;
    u.deta_u = 1 - calAP(u, S, gamma);
    
    M.push(u);
    
    while (!M.empty())
    {
        Node w = M.top();
        M.pop();
        
		if (findKey(S, w.number) || w.influence < theta)
            continue;
        
        vector<Node> C_W;
        C_W.clear();
        w.MIA->getAllNode(C_W);
        
        for (Node v: C_W)//v belongs to C(w)
        {
			map<int, Edge*>::iterator iter;
			Edge* pedge=NULL;
			for(iter = w.neighbourEdge.begin();iter != w.neighbourEdge.end();iter++){
				Edge* pedge= iter->second;
				if(pedge->targetNode->number==v.number){
					break;
				}
			}

			if(pedge && pedge->isVisited){
				continue;
			}

            
            double influence = w.influence * calPP(w, v);
            
            if (!findNodeInM(v, M) || influence > v.influence)
            {
                v.influence = influence;
                v.deta_u = w.deta_u * calPP(w, v) *calAP(v, S, gamma);
                
                if (!findNodeInM(v, M))
                    M.push(v);
                else
					adjustM(v, influence, M);
            }
        }
    }//end while
    
    res = calDetaUSR(g.nodes, theta);
    
    return res;
}





double delta_sigma_v_S_gamma(Node v, vector<Node> S_i, Query q, double theta, Graph g)
{
    CalcMargin(v, g, theta, q, S_i);
    return 1;
}

double prodChild(Tree* node,map<int, Node> S)
{
    double ap = 0;
    
	if(findKey(S, node->node->number))
        ap = 1;
    else
    {
        vector<Tree*>::iterator iterator;
        double childAp = 1;
        for (iterator = node->nextNode.begin(); iterator != node->nextNode.end(); iterator++) {
            
            childAp *=(1-prodChild(*iterator, S)*calPP(*((*iterator)->node),*node->node));
        }
    }
    
    return ap;
}

/*
	calculate the ap(u|S,r) i.e. equation (4) in paper
 */
double calAP(Node& u, map<int, Node> S, Query &q)
{
    double res = 0.0;
    
    if (S.size() == 0) 
//if(findKey(S, u.number))
{
        res = 1;
    }else{
        if(findNode(S, u))
            res = 1;
        else
        {
            res = prodChild(u.MIA, S);
        }
    }
    return res;
}



/*
	calculate the pp(w,v|r)
 */
double calPP(Node w, Node v)
{
 
    
  
    Tree* tree = findNode(w.MIA, &v);
    
    return tree->node->influence;
}

/*
	find Node in M
 */
bool findNodeInM(const Node & findNode,  priority_queue<Node> M)
{
    
    while (!M.empty())
    {
        Node u  = M.top();
        M.pop();
        if (findNode.number == u.number)
            return true;
    }
    
    return false;
}

/*
	Adjust M due to new v.influence
 */
void adjustM(Node& oldNode, double new_inf, priority_queue<Node>& M)
{
    Node newNode = oldNode;
    newNode.influence = new_inf;
    priority_queue<Node> M_;
    while (!M.empty()) {
        Node u = M.top();
        M.pop();
        if (oldNode.number == u.number)
        {
            u = newNode;
            M_.push(u);
            return;
        }
        M_.push(u);
    }
    M = M_;
}

/*
	calculate the deta(u|S,r) showed in Line 14 in Algorithm 2
 */
double calDetaUSR(map<int, Node>&V, double theta)
{
    double res = 0.0;
    
	for (map<int, Node>::iterator i=V.begin(); i!=V.end(); i++)  
    {  
		if (i->second.influence >= theta)
            res += i->second.deta_u;
    }  

    return res;
}


/**
 * bestEffort算法入口，输入为一个图G，查询语句Q，以及用户定义的theta,最后一个参数是要选择的上界计算算法
 */
vector<Node> bestEffort(Graph g, Query q, double theta, algorithm chooseAlgorithm)
{
    vector<Node> node;
    
    BestEffort bestEffort;
    
    
    //首先进行离线处理
    bestEffortOffline(g, theta, bestEffort,q,chooseAlgorithm);
    
    //进行在线处理
    bestEffortOnline(g, q, theta, bestEffort,chooseAlgorithm);
    
    return node;
}
