#ifndef __DIJKSTRA__
#define __DIJKSTRA__
#include <vector>
#include <queue>
#include <functional>
#include <fstream>
#define GRAPH_MAX 101 // maximum value in graph + 1
using namespace std;

/* id value pair for priority queue */
class id_val_pair{
	public:
		int id;
		int value;
		id_val_pair(int, int);
};
/* comparator for values in id_val_pair */
struct compare_val{
	bool operator()(id_val_pair const &v1, id_val_pair const &v2)
	{
		/* return true if value1 ordered after value2 */
		return v1.value > v2.value;
	}
};
class dijkstra{
	private:
		int** graph;
		int** prev;
		int size;
		//priority_queue<int, vector<int>, greater<int> >q;
		priority_queue<id_val_pair, vector<id_val_pair>, compare_val >q;
	public:
		dijkstra(int size);
		~dijkstra();
		void run(int start, int** matrix);
		void print(); //testing
		void to_file(ofstream* out_file);
};

#endif