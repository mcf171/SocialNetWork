//
//  TopicSample.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//




#include "Graph.hpp"
#include "Query.h"
#include "Node.hpp"
#include "BestEffort.hpp"
#include "TopicSample.hpp"
#include "Load.hpp"

/*
 *  进行主题挖掘
 */



vector<Query>* queryMinning(Graph g, double theta, int K, double Epsilon, double* sampledata){
    
    vector<Query>* topicDistributions = new vector<Query>();

        cout<<endl;
	for (int i = 0; i < NSAMPLE; i++)
	{
		Query* q = new Query(K,Epsilon);
		q->topicDistribution = &(sampledata[i*DIM]);
		//计算每个的S
        double* p = q->topicDistribution;

        cout<<"topic distribution :"<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
        
        BestEffort* bestEffort = new BestEffort(g, *q, theta,precomputation);
        
        
        map<int, Node>* tempS = bestEffort->bestEffortOnline();
		for (map<int, Node>::iterator iter = tempS->begin();iter != tempS->end();iter++)
		{
			q->S[iter->first]=iter->second;
			//q->sigma+=iter->second.influence;
		}
		q->sigma=sigma(*tempS,g,*q);
        cout<<"sigma :"<<q->sigma<<endl;
		topicDistributions->push_back(*q);
        //cout<<i<<"..."<<endl;
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
    vector<Query>* topicDistributions = queryMinning(g, theta, K, Epsilon, sampledata);//P

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
	ss<<TSO_DIR<<"K"<<K<<"T"<<theta<<".tso";
	string ofname;
	ss>>ofname;

	ofstream fout(ofname);

	for (int i = 0; i < NSAMPLE; i++)
	{
		fout<<(*topicDistributions)[i].sigma;
		for (map<int,Node>::iterator iter = (*topicDistributions)[i].S.begin(); iter!=(*topicDistributions)[i].S.end(); iter++)
		{
			fout<<" "<<iter->first;
		}
		fout<<endl;
	}
	fout.close();

}





/*
 *  找到最近的上下界
 */
bool findClosestBound(Query q, vector<Query> topicDistributions, Query** upperBound, Query** lowerBound)
{
	double upperDist = INFMAX;
	double lowerDist = INFMAX;

	*upperBound=NULL;
	*lowerBound=NULL;

	vector<int> lowerBoundIds;

	for (int i = 0; i < topicDistributions.size(); i++)
	{
		if(topicDistributions[i].isUpperBound(q))
		{
			double dKL = topicDistributions[i].dKL(q);
			if(dKL<upperDist)
			{
				upperDist=dKL;
				*upperBound = &(topicDistributions[i]);
			}
		}
		else if(topicDistributions[i].isLowerBound(q))
		{
			lowerBoundIds.push_back(i);
		}
	}

	if(*upperBound==NULL) return false;

	*upperBound = new Query(**upperBound);//新对象

	for (int i = 0; i < lowerBoundIds.size(); i++)
	{
		double dKL = (*upperBound)->dKL(topicDistributions[lowerBoundIds[i]]);
		if(dKL<lowerDist)
		{
			lowerDist=dKL;
			*lowerBound = &(topicDistributions[lowerBoundIds[i]]);
		}
	}
	if(lowerBound==NULL) return false;

	*lowerBound = new Query(**lowerBound);//新对象

	return true;

}


vector<Query> loadSampleOfflineResult(Graph g, double theta, int K, double Epsilon)
{
	//从文件中读取Offline结果
	double* sampledata = new double[NSAMPLE*DIM];
	LoadSampleData(sampledata);


	stringstream ss;
	ss<<TSO_DIR<<"K"<<K<<"T"<<theta<<".tso";
	string ifname;
	ss>>ifname;

	ifstream fin;
	fin.open(ifname);

	if(!fin){
		cout<<ifname<<" not found. Running TopicSampleOffline ..."<<endl;
		topicSampleOffline(g,theta,K,Epsilon);
		cout<<"TopicSampleOffline finished."<<endl;
		cout<<ifname<<" saved."<<endl;
	}


	vector<Query> result;

	for (int i = 0; i < NSAMPLE; i++)
	{
		Query q(K,Epsilon);
		fin>>q.sigma;
		for (int j = 0; j < K; j++)
		{
			int nodeid;
			fin>>nodeid;
			q.S[nodeid]=NULL;
			q.topicDistribution=&sampledata[i*DIM];
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
	
	vector<Query> Samples = loadSampleOfflineResult(g, theta, K, Epsilon);
    
	bool getBound = findClosestBound(q, Samples, &upperBound, &lowerBound);
    
	if(!getBound)
	{
		return NULL;
		//which can not happen if we put in 000 and 111
	}
	else if (lowerBound->sigma > q.epsilon * upperBound->sigma ) {
        //如果找到的边界满足不等式直接返回种子集合
		return lowerBound;
    }else{
    
		Query* qResult = new Query(q.k, q.epsilon);
		map<int, Node> S_i;
		map<int, Node> PL;
		for (map<int, Node>::iterator iter= lowerBound->S.begin();iter!=lowerBound->S.end();iter++)
		{
			PL[iter->first]=g.findNode(iter->first);
		}



		Query* q1 = new Query(q);
		q1->k=1;
		q1->sigma=0;
		q1->S.clear();



		for(int i = 0 ; i < q.k; i ++)
		{
			//从BestEffort中找到一个种子,默认返回是一个vector，设置q的值为1，取vector的第一个元素即可
            BestEffort* bestEffort = new BestEffort(g, *q1, theta, precomputation);

            map<int, Node>* umap = bestEffort->bestEffortOnline();
			Node u = umap->begin()->second;

			qResult->S[u.number]=u;
			S_i[u.number]=u;

			//vector<int>::const_iterator iter = findIntIter(lowerBound->S,u[0].number);

			if(findKey(PL,u.number))
			{
				PL.erase(PL.find(u.number));
			}
			else
			{
				int minpoint=-1;
				double minsig = INFMAX;
				for (map<int, Node>::iterator iter = PL.begin();iter!=PL.end();iter++ )
				{

                    // can't guarantee it's true...
					double sig = delta_sigma_v_S_gamma(iter->second, S_i ,q,theta,g);
					if(sig<minsig){
						minsig=sig;
						minpoint=iter->second.number;
					}
				}
				PL.erase(PL.find(minpoint));
				
			}

            
			map<int, Node>* nowUnion = new map<int, Node>();
			for (map<int, Node>::iterator iter= PL.begin();iter!=PL.end();iter++)
				{
					(*nowUnion)[iter->first]=iter->second;
				}
			for (map<int, Node>::iterator iter= S_i.begin();iter!=S_i.end();iter++)
				{
					(*nowUnion)[iter->first]=iter->second;
				}
            
            //sigma是不是还要传个Q
			qResult->sigma = sigma(*nowUnion, g, q);

			if (qResult->sigma > q.epsilon * upperBound->sigma ){
				for (map<int, Node>::iterator iter= PL.begin();iter!=PL.end();iter++)
				{
					qResult->S[iter->first]=iter->second;
				}
				return qResult;
			}

		}
		return qResult;
	}
}
/*
Query* topicSample(bool doOffline, Graph g,Query q, double theta, int K, double Epsilon)
{
	//offline
	if(doOffline){
		topicSampleOffline(g, theta, K, Epsilon);
	}
	//online
    Query* qResult = topicSampleOnline(g, q, theta, K, Epsilon);
	return qResult;
}
*/

