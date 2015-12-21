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

using namespace std;

class Node{

public:
 
    vector<Node> neighbourNode;
    status currentStatus;
    double influence;
};

bool operator < (const Node& source, const Node& target)
{
    return source.influence < target.influence;
}

#endif /* Node_h */
