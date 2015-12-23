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
class Tree;

class Graph{
    
public:
    
    vector<Node> nodes;
    
};

void Dijkstra(Node& startNode);

void calculateGraph(Graph& g);

double hat_delta_p_u(Tree* tree);

double delta_sigma_v_S_gama(Tree* tree,vector<Node> S_i, vector<double> gamma);

#endif /* Graph_h */
