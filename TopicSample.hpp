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
 *  离线部分
 */


//调用BestEffort，离线计算每一个采样点的S和sigma值，保存在Query的She sigma两个属性中，传出来
vector<Query>* queryMinning(Graph* g, double theta, int K, double Epsilon, double* sampledata);

//离线部分主函数调用queryMinning，计算并存盘
void topicSampleOffline(Graph* g, double theta, int K, double Epsilon);

/*
 *  在线部分
 */
//找到最近的上下界
bool findClosestBound(Query q, vector<Query> topicDistributions, Query** upperBound, Query** lowerBound);

//从文件读取topicSampleOffline的结果
vector<Query> loadSampleOfflineResult(Graph* g, double theta, int K, double Epsilon);

//在线部分，Algorithm 5
Query* topicSampleOnline(Graph* g,Query q);

/*
 *  下面这两个没什么用
 */

//Query* topicSample(Graph g,Query q, double theta, int K, double Epsilon);

#endif /* TopicSample_h */
