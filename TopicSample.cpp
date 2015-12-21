//
//  TopicSample.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include "Query.h"
#include "Node.h"
#include "BestEffort.cpp"
#include <vector>

using namespace std;

/*
 *  进行主题挖掘
 */
vector<Query> queryMinning(){
    
    vector<Query> topicDistributions;
    
    
    
    return topicDistributions;
}

/*
 *  主题采样离线部分
 */
void topicSampleOffline(){
    
    //首先从log中挖掘可能的主题分布
    vector<Query> topicDistributions = queryMinning();
    
    //计算上下边界
    
}

/*
 *  找到最近的上下界
 */
void findClosestBound()
{
    
}

void topicSampleOnline(Graph g,Query q, double xita){
    
    //找到与离线系统中上下界最接近的上下界
    
    findClosestBound();

    //如果找到的边界满足不等式直接返回种子集合
    if (true) {
        //返回种子
    }
    
    for(int i = 0 ; i < q.k; i ++)
    {
        //从BestEffort中找到一个种子,默认返回是一个vector，设置q的值为1，取vector的第一个元素即可
        vector<Node> u = bestEffort(g, q, xita);
        //接下来一系列判断
    }
    
}

void topiSample(Graph g,Query q, double xita)
{
    topicSampleOffline();
    topicSampleOnline(g, q, xita);
}
