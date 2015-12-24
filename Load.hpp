#ifndef Load_h
#define Load_h

#define NNODE 10
#define NEDGE 35
#define NSAMPLE 500
#define DIM 3

#define NODE_PATH "../SocialNetWorkGit/data/paper_nodetest.txt"
#define EDGE_PATH "../SocialNetWorkGit/data/paper_edgetest.txt"
#define PROP_PATH "../SocialNetWorkGit/data/paper_proptest.txt"
#define SAMPLE_PATH "../SocialNetWorkGit/data/samples.txt"

#define INFMAX 100000000

#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string> 
#include <fstream>
#include <sstream>

using namespace std;


void LoadGraphData(int* nodedata, int* edgedata, double* propdata);

void LoadSampleData(double* sampledata);

void loadTest();

#endif