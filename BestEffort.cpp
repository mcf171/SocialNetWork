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
        }
    }
    
    for (nodeIter = g.nodes.begin(); nodeIter != g.nodes.end(); nodeIter ++)
    {
        
        Dijkstra( *nodeIter);
    }
    
    //cout<<"create MIA";
}

void localGraphBased()
{
    
}

void neighborhoodBased()
{
    
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

void bestEffortOnline(Graph g ,Query q, double theta)
{
    
    //K次循环找到所有合适的种子
    for (int i = 0; i < q.k ; i++) {
        
        
    }
}

vector<Node> bestEffort(Graph g, Query q, double theta)
{
    vector<Node> node;
    
    BestEffort bestEffort;
    
    bestEffortOffline(g, theta, bestEffort);
    
    return node;
}
