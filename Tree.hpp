//
//  Tree.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

#include <vector>

using namespace std;
class Node;

class Tree
{
public:
    Node* node;
    
    vector<Tree*> nextNode;

    
    ~Tree();
};

Tree* findNode(Tree* tree, Node* node);
#endif /* Tree_h */
