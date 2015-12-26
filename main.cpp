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
	
    double Epsilon = 0.8;
    //创建查询语句
    
    double topicDistribution []= {0.2, 0.3, 0.5};


	double theta=0.99;

	int K=3;

	

	Query q(K,Epsilon,theta);

    q.topicDistribution = topicDistribution;

	g.Load(q);
	/*
     BestEffort* bestEffort = new BestEffort(&g, &q, theta, precomputation);
     bestEffort->bestEffortOffline();
     map<int, Node>* S = bestEffort->bestEffortOnline();

    BestEffort* bestEffort = new BestEffort(g, q,theta, precomputation);
    //调用bestEffort返回k个种子
    //离线部分生成优先队列的文件L.txt注意修改路径
    
    bestEffort->bestEffortOffline();
    
    //只要有L.txt文件在线部分独立执行
    map<int, Node>* S =  bestEffort->bestEffortOnline();
    map<int, Node> seeds;
    Tree* tree = new Tree();
    
    seeds[g.nodes[1].number]  = g.nodes[1];
   // seeds[g.nodes[2].number]  = g.nodes[2];
    
    tree->seeds = seeds;
    
    Dijkstra(g, tree,seeds);
    
    double influence= sigma(seeds, g, q);
    
//    precomputationBased(g);
	*/

	Query* qResult = topicSampleOnline(&g,q);

	cout<<endl;
	cout<<"Result:"<<endl;
	cout<<"\tsigma: "<<qResult->sigma<<endl;
	cout<<qResult->k<<" Points:"<<endl;
	for (map<int,Node>::iterator iter = qResult->S.begin();iter!=qResult->S.end();iter++)
	{
		cout<<iter->first<<endl;
	}

	cout<<"end."<<endl;

    return 0;
}
