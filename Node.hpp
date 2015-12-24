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
#include <iostream>
#include "ConstantFile.h"

using namespace std;

class Edge;
class Tree;

class Node{
    
public:
    vector<Edge*> neighbourEdge;
    vector<Edge*> dijkstraEdge;
    
    Tree* MIA;
    //vector<double> realTopicDistribute;
    ~Node();
    status currentStatus;
    //Node的影响力
    double weight;
    double influence;
    
    double hat_gamma_p;
    //Node在图中的序号
    int number;
	double deta_u;
    bool operator < (const Node &target) const{
        
        return this->influence < target.influence;
    }
    
    bool operator == (const Node& target)
    {
        return this->number == target.number;
    }
    bool operator == (Node* target)
    {
        return this->number == target->number;
    }
    bool operator != (const Node& target)
    {
        return this->number != target.number;
    }
    
    bool operator < ( Node* target) const
    {
        
        
        return this->influence < target->influence;
    }
    
    bool operator <=(const Node& target) const
    {
        return this->influence <= target.influence;
    }
};

bool findNode(vector<Node> nodes, Node node);

vector<Node>::const_iterator findNodeIter(vector<Node> nodes, Node node);


vector<int>::const_iterator findIntIter(vector<int> nodes, int nodeid);

#endif /* Node_h */
