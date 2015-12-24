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
    int id;
	int sourceNodeId;
	int targetNodeId;
	Node* sourceNode;
    Node* targetNode;
    //topic分布
    double* realDistribution;
    
    
    double weight;
    double distance;
    bool isVisited;

	Edge(int idnum, Node* source, Node* target, double* realdistribution);

    ~Edge();
    /*
    bool operator == (const Edge& target)
    {
        return this->targetNode == target.targetNode;
    }
    */
    bool operator != (const Edge& target)
    {
        return this->targetNode != target.targetNode;
    }
    
    bool operator == (const Edge& target);
    
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
