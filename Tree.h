//
//  Tree.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Tree_h
#define Tree_h
#include "Node.h"
#include <vector>

class Tree
{
    Node* node;
    
    vector<Node*> nextNode;
};

#endif /* Tree_h */
