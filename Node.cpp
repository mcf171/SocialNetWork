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

Node::Node(){
	Init();
}

Node::Node(int num)
{
	this->number = num;
    Init();
}

void Node::Init(){
	currentStatus=initial;
    weight=0;
    influence=0;
	ap_node_S_gamma=0;
    hat_delta_sigma_p=0;
	deta_u=0;
    MIA = new Tree();
}

void Node::insertEdge(int targetPoint, Edge* edge)
{
	this->neighbourEdge[targetPoint]=edge;
}
//
//bool findNode(vector<Node> nodes, Node node)
//{
//    
//    bool exists = false;
//    
//    if(find(nodes.begin(), nodes.end(), node) != nodes.end())
//        exists = true;
//    
//    return exists;
//    
//}

Node findNode(map<int, Node> S, int key)
{
	if(S.count(key)>0)
	{
		return S[key];
	}
    
    return NULL;
    
}

bool findKey(map<int, Node> S, int key)
{
	if(S.count(key)>0)
	{
		return true;
	}
	return false;
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