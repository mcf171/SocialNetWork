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

//void Tree::getAllNode(vector<Node> &nodes,Node node)
//{
//    
//    if (this->node->number != node.number) {
//        
//        nodes.push_back(*this->node);
//    }
//    for (auto treeNext : this->nextNode)
//    {
//        treeNext->getAllNode(nodes,node);
//    }
//}


bool findKey(map<int, Tree*> S, int key)
{
	map<int, Tree*>::iterator iter = S.find(key);
	if(iter!=S.end())
	{
		return true;
	}
	return false;
}

Tree* findSeedsNodes(Tree* tree, Node* node){
    
    Tree* result = nullptr;
    map<int, Tree*> nextNode = tree->nextNode;
    map<int,Tree*>::iterator treeItero;
    bool exist = false;
    
    if(tree->node == nullptr){
        if(findKey(tree->seeds, node->number))
            result = tree;
        else
        {
			if(findKey(nextNode,node->number))
				result = nextNode[node->number];
			else{
				for (treeItero = nextNode.begin(); treeItero != nextNode.end(); treeItero++) {
                
					Tree* tempNode = treeItero->second;

					result = findNode(tempNode,node);
             
				}
			}
        }
            
    }
    else{
        if(tree->node->number == node->number)
            result = tree;
        else
        {
           if(findKey(nextNode,node->number))
				result = nextNode[node->number];
			else{

				for (treeItero = nextNode.begin(); treeItero != nextNode.end(); treeItero++) 

					result = findNode(treeItero->second,node);

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
	map<int, Tree*> nextNode = tree->nextNode;
    map<int,Tree*>::iterator treeItero;
    bool exist = false;
    if(tree->node->number == node->number)
        result = tree;
    else{

		if(findKey(nextNode,node->number))
				result = nextNode[node->number];
		else{

			for (treeItero = nextNode.begin(); treeItero != nextNode.end(); treeItero++) 

				result = findNode(treeItero->second,node);

			}
		}
	
    return result;
}

