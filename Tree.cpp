//
//  Tree.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "Tree.hpp"
#include "Node.hpp"

Tree::Tree()
{
   node=NULL;
}

Tree::~Tree()
{
   

}

void Tree::getAllNode(vector<Node> &nodes,Node node)
{
    
    if (this->node->number != node.number) {
        
        nodes.push_back(*this->node);
    }
    for (auto treeNext : this->nextNode)
    {
        treeNext->getAllNode(nodes,node);
    }
}


Tree* findSeedsNodes(Tree* tree, Node* node){
    
    Tree* result = nullptr;
    vector<Tree*> nextNode = tree->nextNode;
    vector<Tree*>::iterator treeItero;
    bool exist = false;
    
    if(tree->node == nullptr){
        if(findKey(tree->seeds, node->number))
            result = tree;
        else
        {
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
        }
            
    }
    else{
        if(tree->node->number == node->number)
            result = tree;
        else
        {
            for (treeItero = nextNode.begin(); treeItero != nextNode.end(); treeItero++)
            {
                
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
        }
    }
    return result;
}


/*
 * 利用深度优先进行遍历树，查找节点Node在Tree中的位置
 * @param MIA，目前构建的MIA树
 * @param node 查询的node节点
 * @return Tree* 返回找到的位置
 */
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

