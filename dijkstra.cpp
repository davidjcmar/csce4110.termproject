#include "header.h"
#include "dijkstra.h"
#include <unistd.h>
using namespace std;

id_val_pair::id_val_pair(int id_init, int val_init)
{
	id = id_init;
	value = val_init;
}
dijkstra::dijkstra(int size_init)
{
	/* init structures */
	size = size_init;
	graph = new int*[size];
	for (int i=0; i<size; i++)
		graph[i] = new int[size];
//	queue = new int[size];
	prev = new int*[size];
	for (int i=0; i<size; i++)
		prev[i] = new int[size];
	/* populate structures */
	for (int i=0; i<size; i++)
		for (int j=0; j<size; j++)
			graph[i][j] = GRAPH_MAX;
/*	for (int i=0; i<size; i++)
		queue[i] = -1;*/
	for (int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			prev[i][j] = -1;
}

dijkstra::~dijkstra()
{
	for (int i=0; i<size; i++)
		delete graph[i];
	delete graph;
}

void dijkstra::run(int start, int** matrix)
{
	class id_val_pair* v;
	for (int i=0; i<size; i++)
	{	
		v= new id_val_pair(i,matrix[start][i]);
		q.push(*v);
		delete v;
	}
	/* testing *//*
	cout<<"size: "<<q.size()<<"\n";
	while (!q.empty())
	{
		cout<<q.top().id<<" "<<q.top().value<<"\t";
		q.pop();
	}
	cout<<"\n";
	/* end testing */
	while (!q.empty())
	{
		class id_val_pair u = q.top(); // yoooooo
		q.pop(); // yoooooo
        //class id_val_pair u = q.front();
        //q.pop();

		for (int i=0; i<size; i++)
		{
//			cout<<"u: "<<u.value<<" current: "<<matrix[start][u.id]<<"\n"; //testing
			if (matrix[start][u.id] + matrix[u.id][i] < graph[start][i])
			{
				graph[start][i] = matrix[start][u.id] + matrix[u.id][i];
				prev[start][i] = u.id;
			}

		}
	}
	/* testing *//*
	for (int i=0; i<size; i++)
	{	
		for (int j=0; j<size; j++)
		{
			cout<<graph[i][j]<<"\t";
		}
		cout<<"\n";
	}
	cout<<"\n";
	/* end testing */

}

void dijkstra::print()
{
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
			cout<<graph[i][j]<<"\t";
		cout<<"\n";
	}
}

void dijkstra::to_file(ofstream* out_file)
{
	*out_file<<size<<"\n";
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
			*out_file<<graph[i][j]<<" ";
		*out_file<<"\n";
	}
}