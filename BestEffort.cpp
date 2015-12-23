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

/**
 *  基于Precomputation的方法
 */
void precomputationBased(Graph& g)
{
    
    vector<Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
        Node node = *nodeIter;
        
        vector<Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = *edgeIter;
            vector<double>::iterator distanceIter;
            double maxDistance = 0;
            for (distanceIter = edge->realDistribution.begin(); distanceIter != edge->realDistribution.end(); distanceIter++) {
                if(*distanceIter > maxDistance)
                    maxDistance = *distanceIter;
            }
            edge->distance = maxDistance;
            edge->weight = maxDistance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( *nodeIter);
    }
    
    //cout<<"create MIA";
}

vector<Node> getLocalGraph(Tree MIA,double theta){
    
    vector<Node> nodes;
    priority_queue<Node> temppNode;
    
    
    do{
        temppNode.push(*(MIA.node));
        Node node = temppNode.top();
        temppNode.pop();
        if(node.influence >= theta)
            nodes.push_back(node);
        else
            break;
        
        
        
    }while (!temppNode.empty());
    return nodes;
}

void localGraphBased(Graph& g,double theta)
{
    vector<Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
        Node node = *nodeIter;
        
        vector<Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = *edgeIter;
            vector<double>::iterator distanceIter;
            double maxDistance = 0;
            for (distanceIter = edge->realDistribution.begin(); distanceIter != edge->realDistribution.end(); distanceIter++) {
                if(*distanceIter > maxDistance)
                    maxDistance = *distanceIter;
            }
            edge->distance = maxDistance;
            edge->weight = maxDistance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( *nodeIter);
        double distance = getLocalDistance((*nodeIter).MIA, theta);

     //   cout<<"the hat_gama of "<<(*nodeIter).number<<" is :"<<distance<<endl;
    }
    
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        Graph local_g;
        g.nodes.clear();
        
        vector<Node> tempNode;
        tempNode.clear();
        //tempNode.push_back(*nodeIter.)
    }

}

void neighborhoodBased(Graph& g)
{
    vector<Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
        Node node = *nodeIter;
        
        vector<Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = *edgeIter;
            vector<double>::iterator distanceIter;
            double maxDistance = 0;
            for (distanceIter = edge->realDistribution.begin(); distanceIter != edge->realDistribution.end(); distanceIter++) {
                if(*distanceIter > maxDistance)
                    maxDistance = *distanceIter;
            }
            edge->distance = maxDistance;
            edge->weight = maxDistance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( *nodeIter);
    }
}

double estInfUB(Node node, Graph g, double theta)
{
    double maxInfluence;
    
    return maxInfluence;
}

/*
 * 离线部分主要功能计算每个点的最大影响上界
 */

void bestEffortOffline(Graph g, double theta, BestEffort& bestEffort)
{
    
    vector<Node> nodes = g.nodes;
    
    for (int i = 0 ; i < nodes.size();  i ++) {
        //计算每个node的影响上界
        estInfUB(nodes[i], g, theta);
        //维护优先队列
        bestEffort.L.push(nodes[i]);
        //bestEffort.L.push(nodes[i]);
    }
    
}



/*
 * 在线部分主要计算在给定主题分布下的精确上界
 */

void bestEffortOnline(Graph g ,Query q, double theta, BestEffort& bestEffort)
{
    //Initial an empty heap H and set S
    auto &H = bestEffort.H;
    auto &S = q.S;
    auto &L = bestEffort.L;
    while (!H.empty()) {
        H.pop();
    }

    S.clear();
    
    //K次循环找到所有合适的种子
    for (int i = 0; i < q.k ; i++)
    {
        vector<Node>::iterator itertor;
        
        while (!H.empty())
        {
            insertCandidates(L, H);
            
            Node u = H.top();
            H.pop();
            
            if (initial == u.currentStatus)
            {
                double sigma_new = EstMarginUB(u, g, theta, q);
                u.currentStatus = bounded;
                u.influence = sigma_new;
                H.push(u);
            }
            else if (bounded == u.currentStatus)
            {
                double sigma_new = CalcMargin(u, g, theta, q, S);
                u.currentStatus = exact;
                u.influence = sigma_new;
                H.push(u);
            }
            else if (exact == u.currentStatus)
            {
				S.push_back(u.number);
                updateAP();
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

/*
	EstMarginUB
 */
double EstMarginUB(const Node& u, const Graph& g, double theta, const Query& gamma)
{
    double res = 0.0;
    
    return res;
}

/*
	CALCMARGIN
 */
double CalcMargin(Node& u, Graph& g, double theta, Query& gamma, vector<int>& S)
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
        
		if (findInt(S, w.number) || w.influence < theta)
            continue;
        
        for (auto &edge: w.dijkstraEdge)//v belongs to C(w)
        {
            Node v = *(edge->targetNode);
            Node old_v = v;
            if (edge->isVisited)
                continue;
            
            double influence = w.influence * calPP(w, v, gamma);
            
            if (!findNodeInM(v, M) || influence > v.influence)
            {
                v.influence = influence;
                v.deta_u = w.deta_u * calPP(w, v, gamma) *calAP(v, S, gamma);
                
                if (!findNodeInM(v, M))
                    M.push(v);
                else
                    adjustM(old_v, influence, M);
            }
        }
    }//end while
    
    res = calDetaUSR(g.nodes, theta);
    
    return res;
}



/*
	Update ap(v|S,r) for each v in V - S
 */
void updateAP()
{
    
}

/*
	calculate the ap(u|S,r) i.e. equation (4) in paper
 */
double calAP(Node& u, vector<int> &S, Query &q)
{
    double res = 0.0;
    
    return res;
}

/*
	calculate the pp(w,v|r)
 */
double calPP(Node& w, Node& v, Query q)
{
    double res = 0.0;
    
    return res;
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
}

/*
	calculate the deta(u|S,r) showed in Line 14 in Algorithm 2
 */
double calDetaUSR(vector<Node>&V, double theta)
{
    double res = 0.0;
    
    for (auto &i: V)
    {
        if (i.influence >= theta)
            res += i.deta_u;
    }
    
    return res;
}

vector<Node> bestEffort(Graph g, Query q, double theta)
{
    vector<Node> node;
    
    BestEffort bestEffort;
    
    bestEffortOffline(g, theta, bestEffort);
    
    return node;
}
