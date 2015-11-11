/*
Main Program
David Cmar
November, 2015
**************
Call algorithm methods, handle file descriptors, handle timing
*/
#include "dijkstra.h"
#include "floyd_warshal.h"
#include "header.h"
#include <string>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>
#include <iomanip>
using namespace std;

int main (int argc, char* argv[])
{
	if (argc != 2)
	{
		cout<<"Include one file containing one or more adjacency matrix as an argument.\n";
		return 1;
	}
	/* file descriptors */
	ifstream in_file;
	ofstream out_file_dij;
	ofstream out_file_floyd;
	ofstream out_file_times;

	in_file.open(argv[1]); // open input file descriptor
	if (in_file.is_open())
	{
		string line;
		/* open output file descriptors */
		out_file_times.open("time_comparison");
		out_file_dij.open("dijkstra_paths");
		out_file_floyd.open("floyd_paths");

		out_file_times<<"Matrix Size\t\tDijkstra\t\tFloyd-Warshall\n";
		while (getline(in_file,line))
		{
			/* populate adjacency matrix */
			int size = atoi(line.c_str());
			/* init adjacency matrix */
			int** matrix = new int*[size];
			for (int i = 0; i<size; i++)
				matrix[i] = new int[size];
			/* parse file, populate adjacency matrix */
			for (int i=0; i<size; i++)
			{
				int j=0;
				string element;
				getline(in_file,line);
				for (int k=0; k<line.size(); k++)
				{
					if (line[k] == ' ')
					{
						matrix[i][j] = atoi(element.c_str());
						element.clear();
						j++;
					}
					else
						element.push_back(line[k]);
				}
			}

			/* testing *//*
			for (int i=0; i<size; i++)
			{
				for (int j=0; j<size; j++)
					cout<<matrix[i][j]<<"\t";
				cout<<"\n";
			}
			cout<<"\n\n";
			/* end testing */

			/* timing structures */
			struct timespec start_time, stop_time;
			double elapse_time;
			/* test dijkstra */
			class dijkstra* dij = new dijkstra(size);
			if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time) == 0)
			{	
				/* run dijkstra for each vertex */
				for (int i=0; i<size; i++)
				{
					dij->run(i,matrix);
				}
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);
				elapse_time = stop_time.tv_sec - start_time.tv_sec;
				elapse_time += ((stop_time.tv_nsec/1E9) - (start_time.tv_nsec/1E9));
//				cout<<"Dijkstra time: "<<elapse_time<<"\n"; //testing
//				dij->print(); //testing
				dij->to_file(&out_file_dij); // write minimized graph to file
				out_file_times<<size<<"\t\t\t"<<setprecision(10)<<elapse_time<<"\t\t";
				dij->~dijkstra();
			}
			else
			{
				cout<<"ERROR: Clock failed. Fatal error at matrix size="<<size<<"\n";
				return 1;
			}

			/* test floyd-warshal */
			class floyd_w* fl_w = new floyd_w(matrix, size);
			if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time) == 0)
			{
				fl_w->run();
				clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);
				elapse_time = stop_time.tv_sec - start_time.tv_sec;
				elapse_time += ((stop_time.tv_nsec/1E9) - (start_time.tv_nsec/1E9));
//				cout<<"Floyd-Warshal time: "<<elapse_time<<"\n"; //testing
//				fl_w->print(); //testing
				fl_w->to_file(&out_file_floyd);
				out_file_times<<setprecision(10)<<elapse_time<<"\n";
				fl_w->~floyd_w();
			}
			else
			{
				cout<<"ERROR: Clock failed. Fatal error at matrix size="<<size<<"\n";
				return 1;
			}
		}
		/* close output file descriptors */
		out_file_times.close();
		out_file_dij.close();
		out_file_floyd.close();
	}
	return 0;
}
