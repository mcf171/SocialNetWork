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
    
    double topicDistribution []= {0.2,0.8,0};
	double theta=0.4;
	int K=3;
	double Epsilon = 0.8;

	Query q(K,Epsilon);

    q.topicDistribution = topicDistribution;
    
    BestEffort* bestEffort = new BestEffort();
    //调用bestEffort返回k个种子
    //离线部分生成优先队列的文件L.txt注意修改路径
    
    //bestEffortOffline(g, theta, *bestEffort, q, precomputation);
    
    //只要有L.txt文件在线部分独立执行
    //map<int, Node>* S =  bestEffortOnline(g, q, theta, *bestEffort, precomputation);
    
//    precomputationBased(g);

	Query* qResult = topicSampleOnline(g,q,theta,K,Epsilon);


    return 0;
}
