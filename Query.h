//
//  Query.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Query_h
#define Query_h
#include <vector>
#include <math.h>

#include "Node.hpp"
#include "Load.hpp"

class Query{
    
public:
	    
	//参数
	double* topicDistribution;
    int k;//number of seed
    double epsilon;
	double theta;
	//输出的结果
	map <int, Node> S;
	double sigma;

	map <int, Node> skipNodes;


    Query(){};
	Query(int K, double Epsilon,double Theta)
	{
		k=K;
		epsilon=Epsilon;
		theta=Theta;
		sigma=0;
	}
/*
	Query(Query* q)
	{
		for (int i = 0; i < q->topicDistribution.size(); i++)
		{
			topicDistribution.push_back(q->topicDistribution[i]);
		}
		for (int i = 0; i < q->S.size(); i++)
		{
			S.push_back(q->S[i]);
		}
		k=q->k;
		epsilon=q->epsilon;
		sigma=q->sigma;
	}
*/

	bool isUpperBound(Query q)
	{
		for (int i = 0; i < DIM; i++)
		{
			if(topicDistribution[i]<q.topicDistribution[i])
			{
				return false;
			}
		}
		return true;
	}

	bool isLowerBound(Query q)
	{
		for (int i = 0; i < DIM; i++)
		{
			if(topicDistribution[i]>q.topicDistribution[i])
			{
				return false;
			}
		}
		return true;
	}

	//double dKL(Query gamma)
	//{
	//	double res=0;
	//	for (int i = 0; i < DIM; i++)
	//	{
	//		if(topicDistribution[i]==0)continue;
	//		else if(gamma.topicDistribution[i]==0){
	//			res += INFMAX;
	//		}else{
	//			res -= gamma.topicDistribution[i] * log(gamma.topicDistribution[i]/topicDistribution[i]);
	//		}
	//	}
	//	return res;
	//}

	double dKL(Query gamma)
	{
		double res=0;
		for (int i = 0; i < DIM; i++)
		{
			//res += abs(gamma.topicDistribution[i]-topicDistribution[i]);
			res += (gamma.topicDistribution[i]-topicDistribution[i])*(gamma.topicDistribution[i]-topicDistribution[i]);
		}
		return res;
	}

};


#endif /* Query_h */
