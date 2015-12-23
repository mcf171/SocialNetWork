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

#include <queue>

using namespace std;

class Node;

class Graph{
    
public:
    
    vector<Node> nodes;
    
};

void Dijkstra(Graph g,Node& startNode);
#endif /* Graph_h */
