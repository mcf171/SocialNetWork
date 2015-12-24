//
//  Graph.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/23.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include "Graph.hpp"
#include <iostream>

#include "Node.hpp"
#include "Tree.hpp"
#include "Edge.hpp"
using namespace std;

Edge Graph::findeEdgeFromTwoNode(Node sourceNode, Node targetNode)
{
    
    Edge edge;
    edge.sourceNode = &sourceNode;
    edge.targetNode = &targetNode;
    vector<Edge>::iterator iter;
    iter = find(this->edges.begin(), this->edges.end(), edge);
    if( iter != (this->edges.end()))
        edge = *iter;
    
    return edge;
}

Node Graph::findNode(int number)
{
    Node node;
    node.number = number;
    vector<Node>::iterator iter;
    iter = find(nodes.begin(), nodes.end(), node);
    if( iter != nodes.end())
        node = *iter;

    return node;
}

double sigma(vector<Node> nodes, Graph g)
{
	//TODO
    return 0;
}

double getLocalDistance(Tree* tree, double theta)
{
    double distance = 0;
    if(tree->node->influence < theta)
        distance +=tree->node->influence;
    vector<Tree*>::iterator nextNodeIter;
    
    for ( nextNodeIter = tree->nextNode.begin(); nextNodeIter != tree->nextNode.end(); nextNodeIter++) {
        
        distance += getLocalDistance(*nextNodeIter, theta);
    }
    tree->node->hat_gamma_p = distance;
    
    return distance;
}

double delta_sigma_v_S_gamma(Node v, vector<Node> S_i, double* gamma)
{
	//TODO
    return 1;
}

void calculateGraph(Graph& g)
{
    vector<Node>::iterator nodeItera;
    for (nodeItera = g.nodes.begin(); nodeItera != g.nodes.end(); nodeItera++) {
        
        double distance = hat_delta_p_u((*nodeItera).MIA);
        (*nodeItera).influence = distance - 1;
        cout<<"the weight of "<<(*nodeItera).number<<" is :"<<distance<<endl;
    }
}

double hat_delta_p_u(Tree* tree)
{

    double distance = tree->node->influence;
    vector<Tree*>::iterator nextNodeIter;
    
    for ( nextNodeIter = tree->nextNode.begin(); nextNodeIter != tree->nextNode.end(); nextNodeIter++) {
        
        distance += hat_delta_p_u(*nextNodeIter);
    }
    
    return distance;
}

void Dijkstra(Node& startNode)
{
    vector<Node> S;
    S.push_back(startNode);
    priority_queue<Edge*,vector<Edge*>,EdgeCompare> edges,temp;
    vector<Edge*>::iterator iterEdge;
    for(iterEdge = startNode.neighbourEdge.begin(); iterEdge != startNode.neighbourEdge.end(); iterEdge++)
        edges.push(*iterEdge);
    
    Tree* MIA = new Tree();
    
    MIA->node = &startNode;
    MIA->node->influence = 1;
    
    while (!edges.empty())
    {
        
        Edge* edge = edges.top();
        edges.pop();
        if(!findNode(S, *(edge)->targetNode) || !findNode(S, *(edge)->sourceNode)){
            Tree* sourceNode = findNode(MIA,edge->sourceNode);
            Tree* treeNext = new Tree();
            Node* targetNode = new Node();
            targetNode->neighbourEdge = edge->targetNode->neighbourEdge;
            targetNode->number = edge->targetNode->number;
            targetNode->currentStatus = initial;
            treeNext->node = targetNode;
            treeNext->node->weight = edge->weight;
            //treeNext->node->realTopicDistribute = edge->realDistribution;
            treeNext->node->influence = edge->distance*sourceNode->node->influence;
            sourceNode->nextNode.push_back(treeNext);
            
            sourceNode->node->dijkstraEdge.push_back(edge);
            S.push_back(*edge->targetNode);
            for(iterEdge = edge->targetNode->neighbourEdge.begin(); iterEdge != edge->targetNode->neighbourEdge.end(); iterEdge ++)
            {
                if(!findNode(S, *(*iterEdge)->targetNode) || !findNode(S, *(*iterEdge)->sourceNode)){
                    (*iterEdge)->distance = (*iterEdge)->distance*sourceNode->node->influence;
                    edges.push(*iterEdge);
                }
            }
            /*
            long size = edges.size();
            temp = edges;
            for(int i = 0 ; i < size; i ++)
            {
                Edge* edge = temp.top();
                cout<<edge->sourceNode->number<<" "<<edge->targetNode->number<<" "<<edge->weight<<endl;
                temp.pop();
            }
            cout<<"------"<<endl;
             */
            
        }
    }
    
    startNode.MIA = MIA;
    
};