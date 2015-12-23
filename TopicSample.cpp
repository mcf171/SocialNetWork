//
//  TopicSample.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//



#include <iostream>
#include "Graph.hpp"
#include "Query.h"
#include "Node.hpp"
#include "BestEffort.hpp"
#include "TopicSample.hpp"
#include <vector>



#include <cstdlib>
#include <algorithm>
#include <string> 
#include <fstream>
#include <sstream>

#include "json/json.h"
using namespace std;

#pragma comment(lib,"lib_json.lib") 

#define NNODE 10
#define NEDGE 35
#define NSAMPLE 200
#define DIM 3

#define NODE_PATH "../nodetest.txt"
#define EDGE_PATH "../edgetest.txt"
#define PROP_PATH "../proptest.txt"
#define SAMPLE_PATH "../m.csv"


//#define 

#define INFMAX 100000000


/*
 *  进行主题挖掘
 */

void LoadData(double* nodedata, double* edgedata, double* propdata, double* sampledata){
	ifstream fnode (NODE_PATH);
	ifstream fedge (EDGE_PATH);
	ifstream fprop (PROP_PATH);
	ifstream fsample (SAMPLE_PATH);
	string value;

	//double* sampledata = new double[NSAMPLE*DIM];

	for (int i = 0; i < NSAMPLE; i++)
	{
		for (int j = 0; j < DIM-1; j++)
		{
			getline(fsample, value, ',')>>sampledata[i*DIM+j];
		}
		fsample>>sampledata[i*DIM+DIM-1];
		cout<<sampledata[i*DIM+DIM-1]<<endl;
	}


	//double* nodedata = new double[NNODE];

	for (int i = 0; i < NNODE; i++)
	{
		fnode>>nodedata[i];
		cout<<nodedata[i]<<endl;
	}


	//double* edgedata = new double[NEDGE*2];

	for (int i = 0; i < NEDGE; i++)
	{
		fedge>>edgedata[i*2]>>edgedata[i*2+1];
		cout<<edgedata[i*2]<<endl;
	}


	//double* propdata = new double[NEDGE*DIM];

	for (int i = 0; i < NEDGE; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			fprop>>propdata[i*DIM+j];
		}
		cout<<propdata[i*DIM]<<endl;
	}


}

vector<Query> queryMinning(Graph g, double theta, int K, double Epsilon, double* sampledata){
    
    vector<Query> topicDistributions;


	for (int i = 0; i < NSAMPLE; i++)
	{
		Query q(K,Epsilon);
		q.topicDistribution = sampledata+i*DIM*sizeof(double);
		//计算每个的S
		q.S = bestEffort(g, q, theta);
		topicDistributions.push_back(q);
	}

    return topicDistributions;
}

/*
 *  主题采样离线部分
 */
void topicSampleOffline(Graph g, double theta, int K, double Epsilon){

	double* nodedata = new double[NNODE];
	double* edgedata = new double[NEDGE*2];
	double* propdata = new double[NEDGE*DIM];
	double* sampledata = new double[NSAMPLE*DIM];

	LoadData(nodedata, edgedata, propdata, sampledata);

	//直接从预先聚类好的结果文件读进来

    //首先从log中挖掘可能的主题分布
    vector<Query> topicDistributions = queryMinning(g, theta, K, Epsilon, sampledata);//P

	Json::Value root;

	for (int i = 0; i < NSAMPLE; i++)
	{
		//TODO:Save
		for (int j = 0; j < topicDistributions[i].S.size(); j++)
		{
			root[i]["S"][j]=topicDistributions[i].S[j].number;
		}
		
		root[i]["sigma"]=topicDistributions[i].sigma;
	}


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

	upperBound = new Query(*upperBound);//新对象

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

	lowerBound = new Query(*lowerBound);//新对象

	return true;

}



vector<Query> loadSampleOfflineResult()
{
	//TODO:从文件中读取Offline结果
	vector<Query> result;
	return result;
}


Query* topicSampleOnline(Graph g,Query q, double theta){


    
    //找到与离线系统中上下界最接近的上下界    
    Query* upperBound=NULL;
	Query* lowerBound=NULL;
	
	vector<Query> topicDistributions = loadSampleOfflineResult();
    
	bool getBound = findClosestBound(q, topicDistributions, upperBound, lowerBound);


    
	if(!getBound)
	{
		//TODO
		vector<Node> u = bestEffort(g, q, theta);
		//q.S = u;
		return &q;
	}
	else if (lowerBound->sigma > q.epsilon * upperBound->sigma ) {
        //如果找到的边界满足不等式直接返回种子集合
		return lowerBound;
    }else{
    
		Query* qResult = new Query(q.k, q.epsilon);
		Query* q1 = new Query(q);
		q1->k=1;
		q1->sigma=0;
		q1->S.clear();

		for(int i = 0 ; i < q.k; i ++)
		{
			//从BestEffort中找到一个种子,默认返回是一个vector，设置q的值为1，取vector的第一个元素即可
			vector<Node> u = bestEffort(g, *q1, theta);
			qResult->S.push_back(u[0]);

			vector<Node>::const_iterator iter = findNodeIter(lowerBound->S,u[0]);

			if(iter!=lowerBound->S.end())
			{
				lowerBound->S.erase(iter);
			}
			else
			{
				//TODO
			}
			//lowerBound->sigma=
			if (lowerBound->sigma > q.epsilon * upperBound->sigma ){
				for (int i = 0; i < lowerBound->S.size(); i++)
				{
					qResult->S.push_back(lowerBound->S[i]);
				}
				qResult->sigma = lowerBound->sigma;
				return qResult;
			}

		}
		return qResult;
	}
}

void topiSample(Graph g,Query q, double theta)
{
    //loadSampleOfflineResult();

    topicSampleOnline(g, q, theta);
}