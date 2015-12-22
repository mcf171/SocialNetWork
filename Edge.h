//
//  Edage.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Edage_h
#define Edage_h

#include "Node.h"

#include <vector>

class Node;

using namespace std;

class Edge{
    
public:
    
    Node* targetNode;
    //topic分布
    vector<double> realDistribution;

    
    
};

#endif /* Edage_h */
