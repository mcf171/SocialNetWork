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
    // insert code here...
    
    
    //getGraph();
    
	//Graph g;
	//topicSampleOffline(g, 0.1, 5, 0.5);

	Graph g;
	g.Load();
    
    Query q(3,0.01);
    double topicDistribution []= {0.2,0.8,0};
    q.topicDistribution = topicDistribution;
    
   map<int, Node>* S =  bestEffort(g, q, 0.4, precomputation);
    
//    precomputationBased(g);
    return 0;
}
