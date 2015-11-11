/*
Generator Class Methods
David Cmar
November, 2015
*/
#include "graph_generator.h"
using namespace std;

/* constructor */
generator::generator(int size_in)
{
    size=size_in; // set number of vertices
    graph = new int* [size]; // init graph 
    for (int i=0; i<size; i++) // init each vector in matrix
        graph[i] = new int[size]; 

    populate(size);
}
/* destructor */
generator::~generator()
{
    for (int i=0; i<size; i++) //delete each vector in matrix
        delete graph[i];
    delete graph;
}
/* populate matrix with random integers from 1 to 100 */
void generator::populate(int size)
{
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            if (i==j) // set path to self as 0
                graph[i][j] = 0;
            else // set path edge to random int
                graph[i][j] = (rand() % 100) + 1;
        }
    }
}
/*  print matrix
        for testing
*/
void generator::print()
{
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
            cout<<graph[i][j]<<"\t";
        cout<<"\n";
    }

}
/*  output matrix to file in form:
        size
        [1st row]
        [2nd row]
        ...
        [nth row]
*/
void generator::to_file(ofstream* out_file)
{
    *out_file << size<<"\n"; // output number of vertices
    for (int i=0; i<size; i++) 
    {
        for (int j=0; j<size; j++)
            *out_file << graph[i][j]<<" "; 
        *out_file << "\n";
    }
}