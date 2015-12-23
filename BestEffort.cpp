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

double hat_delta_theta(Node u,vector<Node>S,Query q)
{
    double result = 0;
    
    result = hat_delta_p_u(u.MIA) - 1;
    
    if (S.size() != 0) {
        
        result = (1-calAP(u, S, q))*result;
    }
    
    return  result;
}

void preprocessOnline(Graph&g, Query q)
{
    vector<Node>::iterator nodeIter;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++) {
        Node node = *nodeIter;
        
        vector<Edge*>::iterator edgeIter;
        for (edgeIter = node.neighbourEdge.begin(); edgeIter != node.neighbourEdge.end(); edgeIter++) {
            Edge* edge = *edgeIter;
            
            double distance = q.topicDistribution[0]*edge->realDistribution[0]+q.topicDistribution[1]*edge->realDistribution[1]+q.topicDistribution[2]*edge->realDistribution[2];
            edge->distance = distance;
            edge->weight = distance;
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( *nodeIter);
    }
}

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

void getLocalGraph(Tree tree,double theta,vector<Node> &nodes){
    
    if (tree.node->influence > theta)
        nodes.push_back(*tree.node);
    
    vector<Tree*>::iterator iterator;
    for (iterator = tree.nextNode.begin(); iterator != tree.nextNode.end(); iterator++)
        getLocalGraph(*(*iterator), theta, nodes);
    
}

void localGraphBased(Graph& g,double theta, Query q)
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
    //得到每个User的hat_gama;
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( *nodeIter);
        double distance = getLocalDistance((*nodeIter).MIA, theta);

     //   cout<<"the hat_gama of "<<(*nodeIter).number<<" is :"<<distance<<endl;
    }
    
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        Node node = *nodeIter;
        vector<Node> nodes;
        nodes.clear();
        getLocalGraph(*node.MIA, theta, nodes);
        
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

void bestEffortOffline(Graph g, double theta, BestEffort& bestEffort,Query q)
{
    
    vector<Node> nodes = g.nodes;
    
    
    
    localGraphBased(g, theta, q);
    
    for(auto node : g.nodes){
        node.influence = node.hat_gamma_p;
        bestEffort.L.push(node);
    }
    
    
}



/*
 * 在线部分主要计算在给定主题分布下的精确上界
 */

void bestEffortOnline(Graph g ,Query q, double theta, BestEffort& bestEffort)
{
    //Initial an empty heap H and set S
    auto &H = bestEffort.H;
    vector<Node> S;
    auto &L = bestEffort.L;
    while (!H.empty()) {
        H.pop();
    }

    S.clear();
    preprocessOnline(g, q);
    
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
                double sigma_new = hat_delta_theta(u, S, q);
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
				S.push_back(u);
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
	CALCMARGIN
 */
double CalcMargin(Node u, Graph g, double theta, Query gamma, vector<Node> S)
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
        
		if (findNode(S, w) || w.influence < theta)
            continue;
        
        vector<Node> C_W;
        C_W.clear();
        w.MIA->getAllNode(C_W);
        
        for (auto v: C_W)//v belongs to C(w)
        {
            Edge edge = g.findeEdgeFromTwoNode(w, v);
            if(edge.isVisited)
            Node v = *(edge.targetNode);
            Node old_v = v;
            if (edge.isVisited)
                continue;
            
            double influence = w.influence * calPP(w, v);
            
            if (!findNodeInM(v, M) || influence > v.influence)
            {
                v.influence = influence;
                v.deta_u = w.deta_u * calPP(w, v) *calAP(v, S, gamma);
                
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

double prodChild(Tree* node,vector<Node>S)
{
    double ap = 0;
    
    if(findNode(S, *(node->node)))
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
double calAP(Node& u, vector<Node> S, Query &q)
{
    double res = 0.0;
    
    if(findNode(S, u))
        res = 1;
    else
    {
        res = prodChild(u.MIA, S);
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
    
    bestEffortOffline(g, theta, bestEffort,q);
    
    return node;
}
