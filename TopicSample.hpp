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
#include "Graph.hpp"
#include "Query.h"
#include "Node.hpp"
#include "BestEffort.hpp"
#include <vector>


using namespace std;

#include <cstdlib>
#include <algorithm>
#include <string> 
#include <fstream>
#include <sstream>


/*
 *  进行主题挖掘
 */

void LoadGraphData(double* nodedata, double* edgedata, double* propdata);

void LoadSampleData(double* sampledata);

vector<Query> queryMinning(Graph g, double theta, int K, double Epsilon, double* sampledata);
/*
 *  主题采样离线部分
 */
void topicSampleOffline(Graph g, double theta, int K, double Epsilon);

/*
 *  找到最近的上下界
 */
bool findClosestBound(Query q, vector<Query> topicDistributions, Query* upperBound, Query* lowerBound);


vector<Query> loadSampleOfflineResult(Graph g, double theta, int K, double Epsilon);


Query* topicSampleOnline(Graph g,Query q, double theta, int K, double Epsilon);

void topiSample(Graph g,Query q, double theta, int K, double Epsilon);

#endif /* TopicSample_h */
