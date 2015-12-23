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

class Graph;
using namespace std;

class Node;
class BestEffort{
    
public:
    
    priority_queue<Node> L;
    //priority_queue<Node*> L;
};

void precomputationBased(Graph g);



#endif /* BestEffort_h */
