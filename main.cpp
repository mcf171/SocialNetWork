//
//  main.cpp
//  SocialNetWork
//
//  Created by 王珏 on 15/12/21.
//  Copyright © 2015年 王珏. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include "Edge.h"
#include "BestEffort.h"
#include "TopicSample.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string> 
#include <fstream>
#include <sstream>


using namespace std;

void testEstInfUB();

void testFindNode();

void testpriorityQueue();


void LoadData(){
	int nfnode = 10;
	int nfedge = 35;
	int nfsample = 200;
	int d=3;
	ifstream fnode ("D:/workspace_cpp/SocialNetWork/nodetest.txt");
	ifstream fedge ("D:/workspace_cpp/SocialNetWork/edgetest.txt");
	ifstream fprop ("D:/workspace_cpp/SocialNetWork/proptest.txt");
	ifstream fsample ("D:/workspace_cpp/SocialNetWork/m.csv");
	string value;

	double* sampledata = new double[nfsample*d];

	for (int i = 0; i < nfsample; i++)
	{
		for (int j = 0; j < d-1; j++)
		{
			getline(fsample, value, ',')>>sampledata[i*d+j];
		}
		fsample>>sampledata[i*d+d-1];
		//cout<<sampledata[i*d+d-1]<<endl;
	}


	double* nodedata = new double[nfedge];

	for (int i = 0; i < nfnode; i++)
	{
		fnode>>nodedata[i];
		//cout<<nodedata[i]<<endl;
	}


	double* edgedata = new double[nfedge*2];

	for (int i = 0; i < nfedge; i++)
	{
		fedge>>edgedata[i*2]>>edgedata[i*2+1];
		//cout<<edgedata[i*2]<<endl;
	}


	double* propdata = new double[nfedge*d];

	for (int i = 0; i < nfedge; i++)
	{
		for (int j = 0; j < d; j++)
		{
			fprop>>propdata[i*d+j];
		}
		//cout<<propdata[i*d]<<endl;
	}


}

int main(int argc, const char * argv[]) {
    // insert code here...

    //testpriorityQueue();
	LoadData();

    return 0;
}


void testEstInfUB()
{
    
    Node node1;
    node1.index = 1;
    Node node2;
    node2.index = 2;
    Node node3;
    node3.index = 3;
    Node node4;
    node4.index = 4;
    Node node5;
    node5.index = 5;
    Node node6;
    node6.index = 6;
    Node node7;
    node7.index = 7;
    Node node8;
    node8.index = 8;
    
    Edge edgeU1U3;
    edgeU1U3.targetNode = &node3;
    edgeU1U3.realDistribution.push_back(0.4);
    edgeU1U3.realDistribution.push_back(0.8);
    edgeU1U3.realDistribution.push_back(0.3);
    
    Edge edgeU3U1;
    edgeU3U1.targetNode = &node1;
    edgeU3U1.realDistribution.push_back(0.4);
    edgeU3U1.realDistribution.push_back(0.8);
    edgeU3U1.realDistribution.push_back(0.3);
    
    Edge edgeU1U2;
    edgeU1U2.targetNode = &node2;
    edgeU1U2.realDistribution.push_back(0.7);
    edgeU1U2.realDistribution.push_back(0.3);
    edgeU1U2.realDistribution.push_back(0.0);
    
    Edge edgeU2U1;
    edgeU2U1.targetNode = &node1;
    edgeU2U1.realDistribution.push_back(0.7);
    edgeU2U1.realDistribution.push_back(0.3);
    edgeU2U1.realDistribution.push_back(0.0);
    
    Edge edgeU1U5;
    edgeU1U5.targetNode = &node5;
    edgeU1U5.realDistribution.push_back(0.6);
    edgeU1U5.realDistribution.push_back(0.0);
    edgeU1U5.realDistribution.push_back(0.5);
    
    Edge edgeU5U1;
    edgeU5U1.targetNode = &node1;
    edgeU5U1.realDistribution.push_back(0.6);
    edgeU5U1.realDistribution.push_back(0.0);
    edgeU5U1.realDistribution.push_back(0.5);
    
    Edge edgeU2U3;
    edgeU2U3.targetNode = &node3;
    edgeU2U3.realDistribution.push_back(0.6);
    edgeU2U3.realDistribution.push_back(0.7);
    edgeU2U3.realDistribution.push_back(0.5);
    
    Edge edgeU3U2;
    edgeU3U2.targetNode = &node2;
    edgeU3U2.realDistribution.push_back(0.6);
    edgeU3U2.realDistribution.push_back(0.7);
    edgeU3U2.realDistribution.push_back(0.5);
    
    Edge edgeU2U6;
    edgeU2U6.targetNode = &node6;
    edgeU2U6.realDistribution.push_back(0.5);
    edgeU2U6.realDistribution.push_back(0.1);
    edgeU2U6.realDistribution.push_back(0.3);
    
    Edge edgeU6U2;
    edgeU6U2.targetNode = &node2;
    edgeU6U2.realDistribution.push_back(0.5);
    edgeU6U2.realDistribution.push_back(0.1);
    edgeU6U2.realDistribution.push_back(0.3);
    
    Edge edgeU2U7;
    edgeU2U7.targetNode = &node7;
    edgeU2U7.realDistribution.push_back(0.8);
    edgeU2U7.realDistribution.push_back(0.0);
    edgeU2U7.realDistribution.push_back(0.4);
    
    Edge edgeU7U2;
    edgeU7U2.targetNode = &node2;
    edgeU7U2.realDistribution.push_back(0.8);
    edgeU7U2.realDistribution.push_back(0.0);
    edgeU7U2.realDistribution.push_back(0.4);
    
    Edge edgeU3U4;
    edgeU3U4.targetNode = &node4;
    edgeU3U4.realDistribution.push_back(0.1);
    edgeU3U4.realDistribution.push_back(0.4);
    edgeU3U4.realDistribution.push_back(0.3);
    
    Edge edgeU4U3;
    edgeU4U3.targetNode = &node3;
    edgeU4U3.realDistribution.push_back(0.1);
    edgeU4U3.realDistribution.push_back(0.4);
    edgeU4U3.realDistribution.push_back(0.3);
    
    Edge edgeU4U5;
    edgeU4U5.targetNode = &node5;
    edgeU4U5.realDistribution.push_back(0.0);
    edgeU4U5.realDistribution.push_back(0.5);
    edgeU4U5.realDistribution.push_back(0.6);
    
    Edge edgeU5U4;
    edgeU5U4.targetNode = &node4;
    edgeU5U4.realDistribution.push_back(0.0);
    edgeU5U4.realDistribution.push_back(0.5);
    edgeU5U4.realDistribution.push_back(0.6);
    
    Edge edgeU4U8;
    edgeU4U8.targetNode = &node8;
    edgeU4U8.realDistribution.push_back(0.0);
    edgeU4U8.realDistribution.push_back(0.0);
    edgeU4U8.realDistribution.push_back(0.7);
    
    Edge edgeU8U4;
    edgeU8U4.targetNode = &node4;
    edgeU8U4.realDistribution.push_back(0.0);
    edgeU8U4.realDistribution.push_back(0.0);
    edgeU8U4.realDistribution.push_back(0.7);
    
    Edge edgeU6U7;
    edgeU6U7.targetNode = &node7;
    edgeU6U7.realDistribution.push_back(0.6);
    edgeU6U7.realDistribution.push_back(0.0);
    edgeU6U7.realDistribution.push_back(0.2);
    
    Edge edgeU7U6;
    edgeU7U6.targetNode = &node6;
    edgeU7U6.realDistribution.push_back(0.6);
    edgeU7U6.realDistribution.push_back(0.0);
    edgeU7U6.realDistribution.push_back(0.2);
    
    Edge edgeU7U8;
    edgeU7U8.targetNode = &node8;
    edgeU7U8.realDistribution.push_back(0.1);
    edgeU7U8.realDistribution.push_back(0.0);
    edgeU7U8.realDistribution.push_back(0.8);
    
    Edge edgeU8U7;
    edgeU8U7.targetNode = &node7;
    edgeU8U7.realDistribution.push_back(0.1);
    edgeU8U7.realDistribution.push_back(0.0);
    edgeU8U7.realDistribution.push_back(0.8);
     

    node1.neighbourEdge.push_back(&edgeU1U3);
    node1.neighbourEdge.push_back(&edgeU1U2);
    node1.neighbourEdge.push_back(&edgeU1U5);
   
    node2.neighbourEdge.push_back(&edgeU2U1);
    node2.neighbourEdge.push_back(&edgeU2U3);
    node2.neighbourEdge.push_back(&edgeU2U6);
    node2.neighbourEdge.push_back(&edgeU2U7);
    
    node3.neighbourEdge.push_back(&edgeU3U1);
    node3.neighbourEdge.push_back(&edgeU3U2);
    node3.neighbourEdge.push_back(&edgeU3U4);
    
    node4.neighbourEdge.push_back(&edgeU4U3);
    node4.neighbourEdge.push_back(&edgeU4U5);
    node4.neighbourEdge.push_back(&edgeU4U8);
    
    node5.neighbourEdge.push_back(&edgeU5U1);
    node5.neighbourEdge.push_back(&edgeU5U4);
    
    node6.neighbourEdge.push_back(&edgeU6U2);
    node6.neighbourEdge.push_back(&edgeU6U7);
    
    node7.neighbourEdge.push_back(&edgeU7U2);
    node7.neighbourEdge.push_back(&edgeU7U6);
    node7.neighbourEdge.push_back(&edgeU7U8);
    
    node8.neighbourEdge.push_back(&edgeU8U4);
    node8.neighbourEdge.push_back(&edgeU8U7);

    Graph g;
    g.nodes.push_back(&node1);
    g.nodes.push_back(&node2);
    g.nodes.push_back(&node3);
    g.nodes.push_back(&node4);
    g.nodes.push_back(&node5);
    g.nodes.push_back(&node6);
    g.nodes.push_back(&node7);
    g.nodes.push_back(&node8);
    
}

void testFindNode()
{
    vector<Node> nodes;
    Node node1;
    node1.index = 1;
    node1.influence = 5;
    Node node2;
    node2.index = 2;
    node2.influence = 4;
    
    nodes.push_back(node1);
    nodes.push_back(node2);
    
    Node node3;
    node3.index = 3;
    node3.influence = 7;
    bool exist = findNode(nodes, node3);
    
    cout<<exist<<endl;
    
    node3.index = 1;
    exist = findNode(nodes, node3);
    
    cout<<exist<<endl;
}

void testpriorityQueue()
{
    
    Node node1;
    node1.index = 1;
    node1.influence = 5;
    Node node2;
    node2.index = 2;
    node2.influence = 4;
    Node node3;
    node3.index = 3;
    node3.influence = 7;
    
    BestEffort bestEffort;
    
    bestEffort.L.push(&node1);
    bestEffort.L.push(&node2);
    bestEffort.L.push(&node3);
    
    while (!bestEffort.L.empty()) {
        Node* temp =bestEffort.L.top();
        cout<< temp->influence<< ' ';
        bestEffort.L.pop();
    }
    
}
