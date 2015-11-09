/*
Graph Generator
David Cmar
November, 2015
***************
Generate complete, directed graphs as adjacency matrices.
*/

#include "graph_generator.h"
#define MAX 1000    // maximum vertices
#define MIN 50      // minimun vertices
#define COUNT 30    // number of graphs being generated
using namespace std;

int main (void)
{
    srand(time(NULL));
    ofstream out_file;
    out_file.open("graphs");
    int factor = int(MAX/COUNT); // set multiplicative factor of i
    /* generate graphs */
    for (int i=0; i<30; i++)
    {
        int input = ((i*factor) + MIN); // set number of vertices
        //cout<<input<<"\n"; //testing
        generator* gen; 
        gen = new generator(input);
        gen->to_file(&out_file);
        //gen->print(); //testing
        gen->~generator();
    }
    out_file.close();
}