//
//  BestEffort.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef BestEffort_h
#define BestEffort_h

#include <iostream>
#include <queue>
#include <vector>

#include "Query.h"

class Graph;
using namespace std;

class Node;
class BestEffort{
    
public:
    
    priority_queue<Node> L;
    //priority_queue<Node*> L;
};

void precomputationBased(Graph g);
void localGraphBased();
void neighborhoodBased();
double estInfUB(Node node, Graph g, double theta);
void bestEffortOffline(Graph g, double theta, BestEffort& bestEffort);
void bestEffortOnline(Graph g ,Query q, double theta);
vector<Node> bestEffort(Graph g, Query q, double theta);

#endif /* BestEffort_h */
