//
//  Edge.cpp
//  Merge
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "Edge.hpp"
#include "Node.hpp"

Edge::~Edge(){
   
}

Edge::Edge(int idnum, Node* source, Node* target, double* realdistribution)
{
	this->id=idnum;
	this->targetNode = target;
	this->sourceNode = source;
	this->sourceNodeId = source->number;
	this->targetNodeId = target->number;
	this->realDistribution = realdistribution;
	source->insertEdge(this->targetNodeId, this);

	this->weight=0;
    this->distance=INFMAX;
    this->isVisited=false;
}

bool Edge::operator == (const Edge& target)
{
    return this->targetNode->number == target.targetNode->number && this->sourceNode->number == target.sourceNode->number;
}

bool findEdge(vector<Edge> edges, Edge edge)
{
    
    bool exists = false;
    
    if(find(edges.begin(), edges.end(), edge) != edges.end())
        exists = true;
    
    return exists;
    
}