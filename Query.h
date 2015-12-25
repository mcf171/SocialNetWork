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

	//输出的结果
	map <int, Node> S;
	double sigma;

    Query(){};
	Query(int K, double Epsilon)
	{
		k=K;
		epsilon=Epsilon;
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

	double dKL(Query gamma)
	{
		double res=0;
		for (int i = 0; i < DIM; i++)
		{
			if(gamma.topicDistribution[i]==0 || topicDistribution[i]==0)continue;
			res += gamma.topicDistribution[i] * log(gamma.topicDistribution[i]/topicDistribution[i]);
		}
		return res;
	}

};


#endif /* Query_h */
