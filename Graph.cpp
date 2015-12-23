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

void calculateGraph(Graph& g)
{
    vector<Node>::iterator nodeItera;
    for (nodeItera = g.nodes.begin(); nodeItera != g.nodes.end(); nodeItera++) {
        
        double totalInfluence = hat_delta_p_u((*nodeItera).MIA,1);
        (*nodeItera).influence = totalInfluence - 1;
        cout<<"the influence of "<<(*nodeItera).number<<" is :"<<totalInfluence<<endl;
    }
}

double hat_delta_p_u(Tree* tree, double preValue)
{

    double influence = tree->node->influence * preValue;
    vector<Tree*>::iterator nextNodeIter;
    
    for ( nextNodeIter = tree->nextNode.begin(); nextNodeIter != tree->nextNode.end(); nextNodeIter++) {
        
        influence += hat_delta_p_u(*nextNodeIter,tree->node->influence);
    }
    
    return influence;
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
            treeNext->node->influence = edge->distance;
            sourceNode->nextNode.push_back(treeNext);
            
            sourceNode->node->dijkstraEdge.push_back(edge);
            S.push_back(*edge->targetNode);
            for(iterEdge = edge->targetNode->neighbourEdge.begin(); iterEdge != edge->targetNode->neighbourEdge.end(); iterEdge ++)
            {
                if(!findNode(S, *(*iterEdge)->targetNode) || !findNode(S, *(*iterEdge)->sourceNode))
                    edges.push(*iterEdge);
            }
            /*
            long size = edges.size();
            temp = edges;
            for(int i = 0 ; i < size; i ++)
            {
                Edge* edge = temp.top();
                cout<<edge->sourceNode->number<<" "<<edge->targetNode->number<<" "<<edge->distance<<endl;
                temp.pop();
            }
            cout<<"------"<<endl;
             */
            
        }
    }
    
    startNode.MIA = MIA;
    
};