//
//  Graph.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <vector>
#include "Node.h"
#include "Tree.h"
#include <queue>

using namespace std;

class Graph{

public:

    vector<Node*> nodes;
    
};

void Dijkstra(Graph g,Node* startNode)
{
    vector<Node*> S;
    S.push_back(startNode);
    vector<Node*> U;
    vector<Node*>::iterator iter;
    for(iter = g.nodes.begin(); iter != g.nodes.end(); iter++)
        if (*iter != startNode) {
            U.push_back(*iter);
        }
    
    priority_queue<Edge*> edge;
    vector<Edge*>::iterator iterEdge;
    for(iterEdge = startNode->neighbourEdge.begin(); iterEdge != startNode->neighbourEdge.end(); iterEdge++)
        edge.push(*iterEdge);
    
};

#endif /* Graph_h */
