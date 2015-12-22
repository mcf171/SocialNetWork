//
//  Node.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <vector>
#include "ConstantFile.h"
#include "Edge.h"

using namespace std;

class Node{

public:
 
    //Node 所有邻居
    vector<Edge> neighbourEdge;
    //Node 当前状态
    status currentStatus;
    //Node的影响力
    double influence;
    //Node在图中的序号
    int index;
    
};

bool operator < (const Node& source, const Node& target)
{
    return source.influence < target.influence;
}

bool operator == (const Node& source, const Node& target)
{
    return source.index == target.index;
}


bool findNode(vector<Node> nodes, Node node)
{
    
    bool exists = false;
    
    if(find(nodes.begin(), nodes.end(), node) != nodes.end())
        exists = true;
    
    return exists;
    
}

#endif /* Node_h */
