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
#include<map>
#include <queue>
#include "Node.hpp"
#include "Edge.hpp"
#include "Tree.hpp"

using namespace std;

class Node;
class Tree;
class Edge;
class Query;

class Graph{
    
public:
    
	void Load();

    //保存社交网络中所有的用户
    //vector<Node> nodes;
	map<int, Node> nodes;
    
    //保存社交网络中所有的边
	vector<Edge> edges;
    
    //从图中根据number找到用户
	Node findNode(int number);
    
    void changeGraph(Query q);
    
    //从图中根据两个用户找到边
   // Edge findeEdgeFromTwoNode(Node sourceNode, Node targetNode);
};

double getLocalDistance(Tree* startNode, double theta);

Tree* Dijkstra(Node startNode,Tree* MIA,double theta);

Tree* Dijkstra(Tree* MIA,map<int, Node> seeds,double theta);

void calculateGraph(Graph* g);

double hat_delta_p_u(Tree* tree);



//double delta_sigma_v_S_gama(Tree* tree,vector<Node> S_i, vector<double> gamma);





#endif /* Graph_h */
