//
//  BestEffort.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//
#pragma once

#ifndef BestEffort_h
#define BestEffort_h

#include <iostream>
#include "Graph.h"
#include "Query.h"
#include "Node.h"
#include <vector>

using namespace std;

double estInfUB(Node node, Graph g, double theta)
{
    double maxInfluence;
    
    return maxInfluence;
}

/*
 * 离线部分主要功能计算每个点的最大影响上界
 */

void bestEffortOffline(Graph g, double theta)
{
    
    vector<Node> nodes = g.nodes;
    
    for (int i = 0 ; i < nodes.size();  i ++) {
        //计算每个node的影响上界
        double  maxInfluence = estInfUB(nodes[0], g, theta);
        //维护优先队列
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
    
    return node;
}


#endif /* BestEffort_h */
