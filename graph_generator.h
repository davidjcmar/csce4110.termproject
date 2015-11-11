/*
Graph Generator Header
David Cmar
November, 2015
*/
#ifndef __header__
#define __header__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class generator{
    private:
        int** graph; // representation of graph as adjacency matrix
        int size; // number of vertices

    public:
        generator(int);
        ~generator();
        void populate(int);
        void to_file(ofstream*);
        void print();
};
#endif