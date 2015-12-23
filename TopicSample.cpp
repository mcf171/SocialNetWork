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



#define NNODE 10
#define NEDGE 35
#define NSAMPLE 500
#define DIM 3

#define NODE_PATH "../SocialNetWorkGit/data/nodetest.txt"
#define EDGE_PATH "../SocialNetWorkGit/data/edgetest.txt"
#define PROP_PATH "../SocialNetWorkGit/data/proptest.txt"
#define SAMPLE_PATH "../SocialNetWorkGit/data/samples.txt"

#define INFMAX 100000000


/*
 *  进行主题挖掘
 */

void LoadGraphData(int* nodedata, int* edgedata, double* propdata){
	ifstream fnode (NODE_PATH);
	ifstream fedge (EDGE_PATH);
	ifstream fprop (PROP_PATH);

	//int* nodedata = new int[NNODE];

	for (int i = 0; i < NNODE; i++)
	{
		fnode>>nodedata[i];
		cout<<nodedata[i]<<endl;
	}


	//int* edgedata = new int[NEDGE*2];

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

void LoadSampleData(double* sampledata){
	ifstream fsample (SAMPLE_PATH);
	string value;

	//double* sampledata = new double[NSAMPLE*DIM];


	for (int i = 0; i < NSAMPLE; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			fsample>>sampledata[i*DIM+j];
		}
		cout<<sampledata[i*DIM]<<endl;
	}


	//for (int i = 0; i < NSAMPLE; i++)
	//{
	//	for (int j = 0; j < DIM-1; j++)
	//	{
	//		getline(fsample, value, ',')>>sampledata[i*DIM+j];
	//	}
	//	fsample>>sampledata[i*DIM+DIM-1];
	//	cout<<sampledata[i*DIM+DIM-1]<<endl;
	//}
}


vector<Query> queryMinning(Graph g, double theta, int K, double Epsilon, double* sampledata){
    
    vector<Query> topicDistributions;


	for (int i = 0; i < NSAMPLE; i++)
	{
		Query q(K,Epsilon);
		q.topicDistribution = sampledata+i*DIM*sizeof(double);
		//计算每个的S
		vector<Node> S = bestEffort(g, q, theta); 
		for (int i = 0; i < S.size(); i++)
		{
			q.S.push_back(S[i].number);
		}
		topicDistributions.push_back(q);
	}

    return topicDistributions;
}

/*
 *  主题采样离线部分
 */
void topicSampleOffline(Graph g, double theta, int K, double Epsilon){
	double* sampledata = new double[NSAMPLE*DIM];

	LoadSampleData(sampledata);
	//直接从预先聚类好的结果文件读进来

    //首先从log中挖掘可能的主题分布
    vector<Query> topicDistributions = queryMinning(g, theta, K, Epsilon, sampledata);//P

	//Json::Value root;
	//for (int i = 0; i < NSAMPLE; i++)
	//{
	//	//TODO:Save
	//	for (int j = 0; j < topicDistributions[i].S.size(); j++)
	//	{
	//		root[i]["S"][j]=topicDistributions[i].S[j].number;
	//	}
	//	
	//	root[i]["sigma"]=topicDistributions[i].sigma;
	//}

	stringstream ss;
	ss<<"K"<<K<<"T"<<theta;
	string ofname;
	ss>>ofname;

	ofstream fout(ofname);

	for (int i = 0; i < NSAMPLE; i++)
	{
		//TODO:Save
		fout<<topicDistributions[i].sigma;
		for (int j = 0; j < topicDistributions[i].S.size(); j++)
		{
			fout<<" "<<topicDistributions[i].S[i];
		}
		fout<<endl;
	}
	fout.close();

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


vector<Query> loadSampleOfflineResult(double theta, int K, double Epsilon)
{
	//TODO:从文件中读取Offline结果
	double* sampledata = new double[NSAMPLE*DIM];
	LoadSampleData(sampledata);


	stringstream ss;
	ss<<"K"<<K<<"T"<<theta;
	string ifname;
	ss>>ifname;

	ifstream fin(ifname);

	vector<Query> result;

	for (int i = 0; i < NSAMPLE; i++)
	{
		//TODO:Save
		Query q(K,Epsilon);
		fin>>q.sigma;
		for (int j = 0; j < K; j++)
		{
			int nodeid;
			fin>>nodeid;
			q.S.push_back(nodeid);
		}

		result.push_back(q);
	}
	fin.close();
	
	return result;
}


Query* topicSampleOnline(Graph g,Query q, double theta, int K, double Epsilon){


    
    //找到与离线系统中上下界最接近的上下界    
    Query* upperBound=NULL;
	Query* lowerBound=NULL;
	
	vector<Query> topicDistributions = loadSampleOfflineResult(theta, K, Epsilon);
    
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
			qResult->S.push_back(u[0].number);
			vector<int>::const_iterator iter = findIntIter(lowerBound->S,u[0].number);

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

void topiSample(Graph g,Query q, double theta, int K, double Epsilon)
{
	//offline
	topicSampleOffline(g, theta, K, Epsilon);
	//online
    topicSampleOnline(g, q, theta, K, Epsilon);
}


void loadTest(){
	int* nodedata = new int[NNODE];
	int* edgedata = new int[NEDGE*2];
	double* propdata = new double[NEDGE*DIM];
	LoadGraphData(nodedata,edgedata,propdata);


	//double* sampledata = new double[NSAMPLE*DIM];
	//LoadSampleData(sampledata);
}