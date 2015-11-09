#include "header.h"
#include "floyd_warshal.h"
using namespace std;

floyd_w::floyd_w(int** graph_init, int size_init)
{
	/* init structures */
	size = size_init;
	graph = new int*[size];
	for (int i=0; i<size; i++)
		graph[i] = new int[size];
	/* populate structures */
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
			graph[i][j] = graph_init[i][j];
	}
}

floyd_w::~floyd_w()
{
	for (int i=0; i<size; i++)
		delete graph[i];
	delete graph;
}

int floyd_w::run()
{
	for (int k=0; k<size; k++)
	{
		for (int i=0; i<size; i++)
		{
			for (int j=0; j<size; j++)
			{
				if (graph[i][k] + graph[k][j] < graph[i][j])
					graph[i][j] = graph[i][k] + graph[k][j];

			}
		}
	}
}

void floyd_w::print()
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
			cout<<graph[i][j]<<"\t";
		cout<<"\n";
	}
}

void floyd_w::to_file(ofstream* out_file)
{
	*out_file<<size<<"\n";
	for(int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
			*out_file<<graph[i][j]<<" ";
		*out_file<<"\n";
	}
}