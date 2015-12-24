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