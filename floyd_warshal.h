#ifndef __FLOYD_W__
#define __FLOYD_W__
#include <fstream>
using namespace std;

class floyd_w{
	private:
		int** graph;
		int size;
	public:
		floyd_w(int** graph, int size);
		~floyd_w();
		int run();
		void print(); //testing
		void to_file(ofstream* out_file);
};
#endif