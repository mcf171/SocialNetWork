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
#include "Node.hpp";
#include "Edge.hpp";
#include "Tree.hpp";

using namespace std;

class Node;
class Tree;
class Edge;
class Graph{
    
public:
    vector<Node> nodes;
	vector<Edge> edges;
	Node findNode(int number);
    Edge findeEdgeFromTwoNode(Node sourceNode, Node targetNode);
};

double getLocalDistance(Tree* startNode, double theta);

void Dijkstra(Node& startNode);

void calculateGraph(Graph& g);

double hat_delta_p_u(Tree* tree);

//double delta_sigma_v_S_gama(Tree* tree,vector<Node> S_i, vector<double> gamma);

double delta_sigma_v_S_gamma(Node v, vector<Node> S_i, double* gamma);

double sigma(vector<Node> nodes, Graph g);

#endif /* Graph_h */
