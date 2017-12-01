#ifndef checkers_hpp
#define checkers_hpp

#include <iostream>
#include <list>
using namespace std;

class Graph
{
    int V; // vertices
    list<int> *adj; // Pointer to an array containing adjacency lists
public:
    Graph(int V); // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    bool isReachable(int s, int d); // returns true if there is a path from s to d
};

extern int Bcount;
extern int Rcount;

int Redcount();
int Blackcount();
int rowinput();
int columnInput();
void userinput();
void printboard();
void updateboard();
void count();
void usermovecheck();
void userkillcheck();
void kingcheck();
void userKingMoveCheck();
void userKingKillCheck();

//graph variables and functions

//graph for normal checkers
void buildGraph();
//graph for king checkers
void buildKingGraph();
//helper functions for graph
int boardToGraph(int row, int column);
int graphToRow(int vertex);
int graphToColumn(int vertex);
//cpu movement functions
void cpuMove();
bool normalMove();
bool kingMove();
bool endMove();
bool killMove();



#endif /* checkers_hpp */
