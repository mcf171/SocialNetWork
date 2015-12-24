
#include "Load.hpp"

using namespace std;


void LoadGraphData(int* nodedata, int* edgedata, double* propdata){
	ifstream fnode (NODE_PATH);
	ifstream fedge (EDGE_PATH);
	ifstream fprop (PROP_PATH);

	//int* nodedata = new int[NNODE];

	for (int i = 0; i < NNODE; i++)
	{
		fnode>>nodedata[i];
		cout<<nodedata[i]<<endl;
	}


	//int* edgedata = new int[NEDGE*2];

	for (int i = 0; i < NEDGE; i++)
	{
		fedge>>edgedata[i*2]>>edgedata[i*2+1];
		cout<<edgedata[i*2]<<endl;
	}


	//double* propdata = new double[NEDGE*DIM];

	for (int i = 0; i < NEDGE; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			fprop>>propdata[i*DIM+j];
		}
		cout<<propdata[i*DIM]<<endl;
	}


}

void LoadSampleData(double* sampledata){
	ifstream fsample (SAMPLE_PATH);
	string value;

	//double* sampledata = new double[NSAMPLE*DIM];

	for (int i = 0; i < NSAMPLE; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			fsample>>sampledata[i*DIM+j];
		}
		cout<<sampledata[i*DIM]<<endl;
	}


	//for (int i = 0; i < NSAMPLE; i++)
	//{
	//	for (int j = 0; j < DIM-1; j++)
	//	{
	//		getline(fsample, value, ',')>>sampledata[i*DIM+j];
	//	}
	//	fsample>>sampledata[i*DIM+DIM-1];
	//	cout<<sampledata[i*DIM+DIM-1]<<endl;
	//}
}


void loadTest(){
	int* nodedata = new int[NNODE];
	int* edgedata = new int[NEDGE*2];
	double* propdata = new double[NEDGE*DIM];
	LoadGraphData(nodedata,edgedata,propdata);


	//double* sampledata = new double[NSAMPLE*DIM];
	//LoadSampleData(sampledata);
}
