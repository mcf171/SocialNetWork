//
//  Node.cpp
//  Merge
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "Node.hpp"
#include "Tree.hpp"

Node::~Node(){

}

bool findNode(vector<Node> nodes, Node node)
{
    
    bool exists = false;
    
    if(find(nodes.begin(), nodes.end(), node) != nodes.end())
        exists = true;
    
    return exists;
    
}

bool findInt(vector<int> nodes, int nodeid)
{
    
    bool exists = false;
    
    if(find(nodes.begin(), nodes.end(), nodeid) != nodes.end())
        exists = true;
    
    return exists;
    
}


vector<Node>::const_iterator findNodeIter(vector<Node> nodes, Node node)
{

    vector<Node>::const_iterator result = find(nodes.begin(), nodes.end(), node);
    
    return result;
    
}

vector<int>::const_iterator findIntIter(vector<int> nodes, int nodeid)
{

    vector<int>::const_iterator result = find(nodes.begin(), nodes.end(), nodeid);
    
    return result;
    
}