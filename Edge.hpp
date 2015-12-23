//
//  Edage.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Edage_h
#define Edage_h


#include <vector>

class Node;

using namespace std;

class Edge{
    
public:
    
    Node* targetNode;
    //topic分布
    vector<double> realDistribution;
    Node* sourceNode;
    
    double weight;
    double distance;
    ~Edge();
    bool operator == (const Edge& target)
    {
        return this->targetNode == target.targetNode;
    }
    
    bool operator != (const Edge& target)
    {
        return this->targetNode != target.targetNode;
    }
    bool operator < ( const Edge& target)
    {
        return this->distance > target.distance;
    }
    
    bool smallerThan(const Edge* edge)const
    {
        return this->distance < edge->distance;
    }

};

class EdgeCompare{
public:
    EdgeCompare(){}
    bool operator()(const Edge* source, const Edge* target)
    {
        return source->smallerThan(target);
    }
};
bool findEdge(vector<Edge> edges, Edge edge);



#endif /* Edage_h */
