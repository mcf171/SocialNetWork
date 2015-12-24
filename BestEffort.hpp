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
void bestEffortOnline(Graph g ,Query q, double theta,algorithm chooseAlgorithm);

vector<Node> bestEffort(Graph g, Query q, double theta, algorithm chooseAlgorithm);

void precomputationBased(Graph& g);
void preprocessOnline(Graph&g, Query q);

void insertCandidates(priority_queue<Node> &L, priority_queue<Node> &H);
double calDetaUSR(vector<Node>&V, double theta);
void adjustM(Node& oldNode, double new_inf, priority_queue<Node>& M);
bool findNodeInM(const Node & findNode,  priority_queue<Node> M);

double calPP(Node w, Node v);
double prodChild(Tree* node,vector<Node>S);
double calAP(Node& u, vector<Node> S, Query &q);

double hat_delta_theta(Node u,vector<Node>S,Query q);

void updateAP();
double CalcMargin(Node u, Graph g, double theta, Query gamma, vector<Node> S);

#endif /* BestEffort_h */
