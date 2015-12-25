//
//  main.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include <iostream>
#include "Node.hpp"
#include "BestEffort.hpp"
#include "TopicSample.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include <vector>


using namespace std;

void testBestEffort();

//Graph* getGraph();

void testFindNode();

void testpriorityQueue();

void testPriorityQueueEdge();

int main(int argc, const char * argv[]) {
   
	Graph g;
    
    //从文件加载Graph
	g.Load();
    
    //创建查询语句
    Query q(3,0.01);
    double topicDistribution []= {0.2,0.8,0};
    q.topicDistribution = topicDistribution;
    
    //调用bestEffort返回k个种子
    map<int, Node>* S =  bestEffort(g, q, 0.4, precomputation);
    
//    precomputationBased(g);
    return 0;
}
