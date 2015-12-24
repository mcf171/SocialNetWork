#ifndef Load_h
#define Load_h



#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <string> 
#include <fstream>
#include <sstream>
#include "ConstantFile.h"

using namespace std;


void LoadGraphData(int* nodedata, int* edgedata, double* propdata);

void LoadSampleData(double* sampledata);

void loadTest();

#endif