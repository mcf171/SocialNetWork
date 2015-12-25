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
#include <map>

using namespace std;
class Node;

class Tree
{
public:
	Tree();

    Node* node;
    
    map<int, Node> seeds;
    
    vector<Tree*> nextNode;
    
    void getAllNode(vector<Node> &nodes,Node node);
    ~Tree();
};
Tree* findSeedsNodes(Tree* tree, Node* node);
Tree* findNode(Tree* tree, Node* node);
#endif /* Tree_h */
