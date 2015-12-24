//
//  Tree.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "Tree.hpp"
#include "Node.hpp"

Tree::~Tree()
{
   

}

void Tree::getAllNode(vector<Node> &nodes)
{
    
    nodes.push_back(*this->node);
    
    for (auto treeNext : this->nextNode)
    {
        treeNext->getAllNode(nodes);
    }
    
}

Tree* findNode(Tree* tree, Node* node){
    
    Tree* result = nullptr;
    vector<Tree*> nextNode = tree->nextNode;
    vector<Tree*>::iterator treeItero;
    bool exist = false;
    if(tree->node->number == node->number)
        result = tree;
    else
        for (treeItero = nextNode.begin(); treeItero != nextNode.end(); treeItero++) {
            
            if(exist)
                break;
            
            Tree* tempNode = *treeItero;

            if(tempNode->node == node)
            {
                result = tempNode;
                
            }else{
                
                result = findNode(tempNode,node);
                
            }
            if (result != nullptr) {
                exist = true;
                break;
            }
            
        }
    return result;
}

