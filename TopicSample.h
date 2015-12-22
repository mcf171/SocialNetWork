//
//  TopicSample.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//
#pragma once

#ifndef TopicSample_h
#define TopicSample_h

#include <iostream>
#include "Graph.h"
#include "Query.h"
#include "Node.h"
#include "BestEffort.cpp"
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;
#define INFMAX 100000000

/*
 *  进行主题挖掘
 */
vector<Query> queryMinning(Graph g, double theta){
    
    vector<Query> topicDistributions;
	
	//TODO：直接从预先聚类好的结果文件读进来

	//计算每个的S
	for (int i = 0; i < topicDistributions.size(); i++)
	{
		Query q = topicDistributions[i];
		q.S = bestEffort(g, q, theta);
	}
    
    return topicDistributions;
}

/*
 *  主题采样离线部分
 */
void topicSampleOffline(Graph g, double theta){
    
    //首先从log中挖掘可能的主题分布
    vector<Query> topicDistributions = queryMinning(g, theta);//P

}





/*
 *  找到最近的上下界
 */
bool findClosestBound(Query q, vector<Query> topicDistributions, Query* upperBound, Query* lowerBound)
{
	double upperDist = INFMAX;
	double lowerDist = INFMAX;

	upperBound=NULL;
	lowerBound=NULL;

	vector<int> lowerBoundIds;

	for (int i = 0; i < topicDistributions.size(); i++)
	{
		if(topicDistributions[i].isUpperBound(q))
		{
			double dKL = topicDistributions[i].dKL(q);
			if(dKL<upperDist)
			{
				upperDist=dKL;
				upperBound = &topicDistributions[i];
			}
		}
		else if(topicDistributions[i].isLowerBound(q))
		{
			lowerBoundIds.push_back(i);
		}
	}

	if(upperBound==NULL) return false;

	for (int i = 0; i < lowerBoundIds.size(); i++)
	{
		double dKL = upperBound->dKL(topicDistributions[lowerBoundIds[i]]);
		if(dKL<lowerDist)
		{
			lowerDist=dKL;
			lowerBound = &topicDistributions[lowerBoundIds[i]];
		}
	}
	if(lowerBound==NULL) return false;
	return true;

}

vector<Query> loadSampleOfflineResult()
{
	//从文件中读取Offline结果
	vector<Query> result;
	return result;
}


Query* topicSampleOnline(Graph g,Query q, double theta){
    
    //找到与离线系统中上下界最接近的上下界    
    Query* upperBound=NULL;
	Query* lowerBound=NULL;
	
	vector<Query> topicDistributions = loadSampleOfflineResult();
    
	bool getBound = findClosestBound(q, topicDistributions, upperBound, lowerBound);


    //如果找到的边界满足不等式直接返回种子集合
	if (getBound && lowerBound->sigma > q.epsilon * upperBound->sigma ) {
        return lowerBound;
    }
    
	Query* qResult = new Query(q.k, q.epsilon);
	Query* q1 = new Query(q);
	q1->k=1;

    for(int i = 0 ; i < q.k; i ++)
    {
        //从BestEffort中找到一个种子,默认返回是一个vector，设置q的值为1，取vector的第一个元素即可
        vector<Node> u = bestEffort(g, *q1, theta);
		qResult->S.push_back(u[0]);

		if(lowerBound!=NULL)
		{
			vector<Node>::iterator t = find_if(lowerBound->S.begin(),lowerBound->S.end(),u[0].compare);
		}


        //接下来一系列判断
    }
	return qResult;
}

void topiSample(Graph g,Query q, double theta)
{

    //loadSampleOfflineResult();
    topicSampleOnline(g, q, theta);
}

#endif /* TopicSample_h */
