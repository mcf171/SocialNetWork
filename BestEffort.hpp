//
//  BestEffort.h
//  SocialNetWork
//
//  Created by 王珏 on 15/12/22.
//  Copyright © 2015年 王珏. All rights reserved.
//

#ifndef BestEffort_h
#define BestEffort_h

#include <iostream>
#include <queue>
#include <vector>
#include "Query.h"

class Graph;
using namespace std;

class Node;
class BestEffort{
    
public:
    
    priority_queue<Node> L;
    priority_queue<Node> H;
    //priority_queue<Node*> L;
};

void getLocalGraph(Tree tree,double theta,vector<Node> &nodes);
void localGraphBased(Graph& g,double theta,Query q);
void neighborhoodBased(Graph& g);
double estInfUB(Node node, Graph g, double theta);

void bestEffortOffline(Graph g, double theta, BestEffort& bestEffort,Query q,algorithm chooseAlgorithm);
map<int, Node>* bestEffortOnline(Graph g ,Query q, double theta, BestEffort& bestEffort,algorithm chooseAlgorithm);

map<int, Node>* bestEffort(Graph g, Query q, double theta, algorithm chooseAlgorithm);

void precomputationBased(Graph& g);
void preprocessOnline(Graph&g, Query q);

void insertCandidates(priority_queue<Node> &L, priority_queue<Node> &H);
double calDetaUSR(map<int, Node>&V, double theta);
void adjustM(Node& oldNode, double new_inf, priority_queue<Node>& M);
bool findNodeInM(const Node & findNode,  priority_queue<Node> M);

double calPP(Edge edge, Query q);
double calPP(Node sourceNode,Node targetNode, Query q);

double prodChild(Tree* node,map<int, Node> S,Query q);
double calAP(Node& u, map<int, Node> S, Query &q);

double hat_delta_sigma(Node u,map<int, Node>S,Query q, algorithm choosAlgorithm);

double delta_sigma_v_S_gamma(Node v, map<int, Node> S_i, Query q, double theta, Graph g);
double sigma(map<int, Node> nodes, Graph g ,Query q);
double CalcMargin(Node u, Graph g, double theta, Query gamma, map<int, Node> S);

#endif /* BestEffort_h */
