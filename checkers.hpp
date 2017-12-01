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

string board[18][18]; //[row][column]
int Bcount = 1;
int Rcount = 1;
int r =0;
int c =0;
int r1=0;
int c1=0;
bool legal = false;
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
int path[32];
int pindex = 0;
//graph for normal checkers
Graph g(32);
void buildGraph();
//graph for king checkers
Graph gk(32);
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
