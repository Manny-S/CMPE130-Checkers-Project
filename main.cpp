#include <iostream>
#include <list>
#include "checkers.hpp"
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

int main() {
    srand((int)time(NULL));
    int menu=0;
    
    while(menu!=3){
        cout<<"---CHECKERS MENU---"<<endl
        <<"1. Player VS Computer"<<endl
        <<"2. How to Play"<<endl
        <<"3. Exit"<<endl;
        
        cin>>menu;
        
        if(menu == 1){
            printboard();
            buildGraph();
            buildKingGraph();
            while(Bcount!=0||Rcount!=0){
                userinput();
                cpuMove();
                updateboard();
                count();
            }
        }
        if(menu == 2){
            cout << "Please visit the webpage below for more info:" << endl;
            cout << "https://www.itsyourturn.com/t_helptopic2030.html" << endl;
        }
    }
    cout << "GoodBye!" << endl;
    return 0;
}

void printboard(){
    board[0][0]=" ";
    board[2][0] = "1";
    board[4][0] = "2";
    board[6][0] = "3";
    board[8][0] = "4";
    board[10][0] = "5";
    board[12][0] = "6";
    board[14][0] = "7";
    board[16][0] = "8";
    
    for(int i = 1; i<18;i++){
        board[0][i] = " ";
        board[i][0] = " ";
        i++;
    }
    
    board[0][2] = "A";
    board[0][4] = "B";
    board[0][6] = "C";
    board[0][8] = "D";
    board[0][10] = "E";
    board[0][12] = "F";
    board[0][14] = "G";
    board[0][16] = "H";
    
    for(int i = 1;i<18;i++){
        for(int j = 1; j<18;j++){
            board[i][j] = "+";
            j++;
        }
        i++;
    }
    
    for(int i = 1;i<18;i++){
        for(int j = 2; j<18;j++){
            board[i][j] = "-";
            j++;
        }
        i++;
    }
    
    for(int i = 2;i<18;i++){
        for(int j = 1; j<18;j++){
            board[i][j] = "|";
            j++;
        }
        i++;
    }
    
    //Fills in whitespaces for rows 4-5 on board
    for(int i = 8;i<11;i++){
        for(int j = 2; j<18;j++){
            board[i][j] = " ";
            j++;
        }
        i++;
    }
    
    //Places black (B) pieces and whitespaces for rows 1-3 on board
    for(int i = 2;i<3;i++){
        for(int j=2;j<18;j++){
            board[i][j] = " ";
            board[i][j+2] = "b";
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 4; i<5; i++){
        for(int j = 4; j<18;j++){
            board[i][j] = " ";
            board[i][j-2] = "b";
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 6;i<7;i++){
        for(int j=2;j<18;j++){
            board[i][j] = " ";
            board[i][j+2] = "b";
            j++;
            j++;
            j++;
        }
    }
    
    //places red (R) pieces and white spaces for rows 6-8 on board
    for(int i = 12; i<13; i++){
        for(int j = 4; j<18;j++){
            board[i][j] = " ";
            board[i][j-2] = "r";    //testing kings in front (change back to "r" to test regular pieces in front)
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 14;i<15;i++){
        for(int j=2;j<18;j++){
            board[i][j] = " ";
            board[i][j+2] = "r";
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 16; i<17; i++){
        for(int j = 4; j<18;j++){
            board[i][j] = " ";
            board[i][j-2] = "r";
            j++;
            j++;
            j++;
        }
    }
//    board[10][4] = "b"; //test jump
//    board[10][8] = "B"; //test jump
    
    //Prints out board
    for(int i =0;i<18;i++){
        for(int j=0; j<18;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
}

void updateboard(){
    //Prints out board
    for(int i =0;i<18;i++){
        for(int j=0; j<18;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
}


 void userKingMoveCheck(){
 //checks if space is empty to move
 if(board[r1][c1]==" "){
 legal = true;
 }
 else{
 legal = false;
 cout<<"Illegal move. There's a piece there."<<endl;
 return;
 }
 
 if(r==r1&&c==c1){
 legal = false;
 cout<<"Entered the same coordinates. Enter different coordinates."<<endl;
 return;
 }
 else{
 legal = true;
 }
 
 if(r1==r){
 legal = false;
 cout<<"Illegal move. Can't move to side"<<endl;
 return;
 }
 
 if((r1==(r-2)&&c1==(c-2))||(r1==(r-2)&&c1==(c+2))||(r1==(r+2)&&c1==(c+2))||(r1==(r+2)&&c1==(c-2))){
 legal = true;
 }
 else{
 legal = false;
 cout<<"Illegal move."<<endl;
 }
 }
 
 void userKingKillCheck(){
 if((r1==r-4) && (c1==c-4)){
 if(board[r1+2][c1+2]=="b"||board[r1+2][c1+2]=="B"){
 legal = true;
 board[r1+2][c1+2] = " ";
 return;
 }
 else{
 legal = false;
 userKingMoveCheck();
 }
 }
 if((r1==r-4) && (c1==c+4)){
 if(board[r1+2][c1-2]=="b"||board[r1+2][c1-2]=="B"){
 legal = true;
 board[r1+2][c1-2] = " ";
 return;
 }
 else{
 legal = false;
 userKingMoveCheck();
 }
 }
 if((r1==r+4) && (c1==c+4)){
 if(board[r1-2][c1-2]=="b"||board[r1-2][c1-2]=="B"){
 legal = true;
 board[r1-2][c1-2] = " ";
 return;
 }
 else{
 legal = false;
 userKingMoveCheck();
 }
 }
 if((r1==r+4) && (c1==c-4)){
 if(board[r1-2][c1+2]=="b"||board[r1-2][c1+2]=="B"){
 legal = true;
 board[r1-2][c1+2] = " ";
 return;
 }
 else{
 legal = false;
 userKingMoveCheck();
 }
 }
 else{
 legal = false;
 userKingMoveCheck();
 }
 }
 
void userinput(){
    while(legal!=true){
        cout<<"Your turn"<<endl;
        cout<<"What piece would you like to move?"<<endl;
        c=columnInput();
        r=rowinput();
        
        cout<<"Where would you like to move it?"<<endl;
        c1=columnInput();
        r1=rowinput();
        
        if(board[r][c]=="R"){
            userKingKillCheck();
        }
        else{
            userkillcheck();
        }
    }
    
    board[r1][c1] = board[r][c];
    board[r][c] = " ";
    kingcheck();
    legal = false;
}

void userkillcheck(){
    if((r1==r-4) && (c1==c-4)){
        if(board[r1+2][c1+2]=="b"||board[r1+2][c1+2]=="B"){
            legal = true;
            board[r1+2][c1+2] = " ";
            return;
        }
        else{
            legal = false;
            usermovecheck();
        }
    }
    if((r1==r-4) && (c1==c+4)){
        if(board[r1+2][c1-2]=="b"||board[r1+2][c1-2]=="B"){
            legal = true;
            board[r1+2][c1-2] = " ";
            return;
        }
        else{
            legal = false;
            usermovecheck();
        }
    }
    else{
        legal = false;
        usermovecheck();
    }
}

void usermovecheck(){
    //checks if input is user checker piece
    if(board[r][c] == "r"||board[r][c]=="R"){
        legal = true;
    }
    else{
        legal = false;
        cout<<"Error. Choose your checker piece."<<endl;
        return;
    }
    if(r==r1&&c==c1){
        legal = false;
        cout<<"Entered the same coordinates. Enter different coordinates."<<endl;
        return;
    }
    else{
        legal = true;
    }
    
    //checks if space is empty to move
    if(board[r1][c1]==" "){
        legal = true;
    }
    else{
        legal = false;
        cout<<"Illegal move. There's a piece there."<<endl;
        return;
    }
    if(r1==r){
        legal = false;
        cout<<"Illegal move. Can't move to side"<<endl;
        return;
    }
    if(r1<r){
        legal = true;
    }
    else{
        legal = false;
        cout<<"Illegal move. Can't move backwards."<<endl;
        return;
    }
    if((r1==(r-2)&&c1==(c-2))||(r1==(r-2)&&c1==(c+2))){
        legal = true;
    }
    else{
        legal = false;
        cout<<"Illegal move."<<endl;
    }
}

//checks if piece has reached other side to become king
void kingcheck(){
    for(int i =2; i<17;i++){
        if(board[2][i] == "r"){
            board[2][i] = "R";
        }
        if(board[16][i] == "b"){
            board[16][i] = "B";
        }
    }
}

int columnInput(){
    string input;
    int column =0;
    cout<<"Enter column(a,b,c,...):"<<endl;
    cin>>input;
    
    if(input == "A"||input =="a"){
        column = 2;
    }
    if(input == "B"||input =="b"){
        column = 4;
    }
    if(input == "C"||input =="c"){
        column = 6;
    }
    
    if(input == "D"||input =="d"){
        column = 8;
    }
    
    if(input == "E"||input =="e"){
        column = 10;
    }
    
    if(input == "F"||input =="f"){
        column = 12;
    }
    
    if(input == "G"||input =="g"){
        column = 14;
    }
    
    if(input == "H"||input =="h"){
        column = 16;
    }
    return column;
}

int rowinput(){
    int row =0;
    int input;
    
    cout<<"Enter row(1,2,3,...):"<<endl;
    cin>>input;
    
    if(input == 1){
        row = 2;
    }
    if(input == 2){
        row = 4;
    }
    if(input == 3){
        row = 6;
    }
    if(input == 4){
        row = 8;
    }
    if(input == 5){
        row = 10;
    }
    if(input == 6){
        row = 12;
    }
    if(input == 7){
        row = 14;
    }
    if(input == 8){
        row = 16;
    }
    return row;
}
//counts the number of red and black pieces left
void count(){
    Bcount = 0;
    Rcount = 0;
    for(int i = 0; i<18;i++){
        for(int j =0;j<18;j++){
            if(board[i][j]=="b"||board[i][j]=="B"){
                Bcount++;
            }
            if(board[i][j]=="r"||board[i][j]=="R"){
                Rcount++;
            }
        }
    }
    Bcount--;// to take the count off the B labeling the column
    cout << "Red checkers left = " << Rcount << endl;
    cout << "Black checkers left = " << Bcount << endl;
    if (Bcount == 0) {
        cout << "You Win!" << endl;
    }
    else if (Rcount == 0){
        cout << "You Lose!" << endl;
    }
    else{
        //left blank
    }
}
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int> [V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}

// A BFS based function to check whether d is reachable from s using Dijkstra’s algorithm
bool Graph::isReachable(int s, int d)
{
    //set path to all zeros for new path
    fill(path, path+32, 0);
    pindex = 0;
    // are the nodes equal
    if (s == d){
        return true;
    }
    
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++){
        visited[i] = false;
    }
    
    // Create a queue for BFS
    list<int> queue;
    
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
    
    // ready to use to get all adjacent vertices of a vertex
    list<int>::iterator i;
    
    while (!queue.empty())
    {
        // Dequeue a vertex from queue and add to path
        s = queue.front();
        path[pindex] = queue.front();
        pindex++;
        queue.pop_front();
        
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            // If this adjacent node is the destination node, then return true and add end of path
            if (*i == d){
                path[pindex] = d;
                pindex++;
                return true;
            }
            
            //continue to do BFS
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    
    return false;
}
void buildGraph(){
    g.addEdge(0, 4);
    g.addEdge(0, 5);
    g.addEdge(1, 5);
    g.addEdge(1, 6);
    g.addEdge(2, 6);
    g.addEdge(2, 7);
    g.addEdge(3, 7);
    g.addEdge(4, 8);
    g.addEdge(5, 8);
    g.addEdge(5, 9);
    g.addEdge(6, 9);
    g.addEdge(6, 10);
    g.addEdge(7, 10);
    g.addEdge(7, 11);
    g.addEdge(8, 12);
    g.addEdge(8, 13);
    g.addEdge(9, 13);
    g.addEdge(9, 14);
    g.addEdge(10, 14);
    g.addEdge(10, 15);
    g.addEdge(11, 15);
    g.addEdge(12, 16);
    g.addEdge(13, 16);
    g.addEdge(13, 17);
    g.addEdge(14, 17);
    g.addEdge(14, 18);
    g.addEdge(15, 18);
    g.addEdge(15, 19);
    g.addEdge(16, 20);
    g.addEdge(16, 21);
    g.addEdge(17, 21);
    g.addEdge(17, 22);
    g.addEdge(18, 22);
    g.addEdge(18, 23);
    g.addEdge(19, 23);
    g.addEdge(20, 24);
    g.addEdge(21, 24);
    g.addEdge(21, 25);
    g.addEdge(22, 25);
    g.addEdge(22, 26);
    g.addEdge(23, 26);
    g.addEdge(23, 27);
    g.addEdge(24, 28);
    g.addEdge(24, 29);
    g.addEdge(25, 29);
    g.addEdge(25, 30);
    g.addEdge(26, 30);
    g.addEdge(26, 31);
    g.addEdge(27, 31);
}
void buildKingGraph(){
    gk.addEdge(0, 4); //pair
    gk.addEdge(4, 0);
    gk.addEdge(0, 5); //pair
    gk.addEdge(5, 0);
    gk.addEdge(1, 5); //pair
    gk.addEdge(5, 1);
    gk.addEdge(1, 6); //pair
    gk.addEdge(6, 1);
    gk.addEdge(2, 6); //pair
    gk.addEdge(6, 2);
    gk.addEdge(2, 7); //pair
    gk.addEdge(7, 2);
    gk.addEdge(3, 7); //pair
    gk.addEdge(7, 3);
    gk.addEdge(4, 8); //pair
    gk.addEdge(8, 4);
    gk.addEdge(5, 8); //pair
    gk.addEdge(8, 5);
    gk.addEdge(5, 9); //pair
    gk.addEdge(9, 5);
    gk.addEdge(6, 9); //pair
    gk.addEdge(9, 6);
    gk.addEdge(6, 10); //pair
    gk.addEdge(10, 6);
    gk.addEdge(7, 10); //pair
    gk.addEdge(10, 7);
    gk.addEdge(7, 11); //pair
    gk.addEdge(11, 7);
    gk.addEdge(8, 12); //pair
    gk.addEdge(12, 8);
    gk.addEdge(8, 13); //pair
    gk.addEdge(13, 8);
    gk.addEdge(9, 13); //pair
    gk.addEdge(13, 9);
    gk.addEdge(9, 14); //pair
    gk.addEdge(14, 9);
    gk.addEdge(10, 14); //pair
    gk.addEdge(14, 10);
    gk.addEdge(10, 15); //pair
    gk.addEdge(15, 10);
    gk.addEdge(11, 15); //pair
    gk.addEdge(15, 11);
    gk.addEdge(12, 16); //pair
    gk.addEdge(16, 12);
    gk.addEdge(13, 16); //pair
    gk.addEdge(16, 13);
    gk.addEdge(13, 17); //pair
    gk.addEdge(17, 13);
    gk.addEdge(14, 17); //pair
    gk.addEdge(17, 14);
    gk.addEdge(14, 18); //pair
    gk.addEdge(18, 14);
    gk.addEdge(15, 18); //pair
    gk.addEdge(18, 15);
    gk.addEdge(15, 19); //pair
    gk.addEdge(19, 15);
    gk.addEdge(16, 20); //pair
    gk.addEdge(20, 16);
    gk.addEdge(16, 21); //pair
    gk.addEdge(21, 16);
    gk.addEdge(17, 21); //pair
    gk.addEdge(21, 17);
    gk.addEdge(17, 22); //pair
    gk.addEdge(22, 17);
    gk.addEdge(18, 22); //pair
    gk.addEdge(22, 18);
    gk.addEdge(18, 23); //pair
    gk.addEdge(23, 18);
    gk.addEdge(19, 23); //pair
    gk.addEdge(23, 19);
    gk.addEdge(20, 24); //pair
    gk.addEdge(24, 20);
    gk.addEdge(21, 24); //pair
    gk.addEdge(24, 21);
    gk.addEdge(21, 25); //pair
    gk.addEdge(25, 21);
    gk.addEdge(22, 25); //pair
    gk.addEdge(25, 22);
    gk.addEdge(22, 26); //pair
    gk.addEdge(26, 22);
    gk.addEdge(23, 26); //pair
    gk.addEdge(26, 23);
    gk.addEdge(23, 27); //pair
    gk.addEdge(27, 23);
    gk.addEdge(24, 28); //pair
    gk.addEdge(28, 24);
    gk.addEdge(24, 29); //pair
    gk.addEdge(29, 24);
    gk.addEdge(25, 29); //pair
    gk.addEdge(29, 25);
    gk.addEdge(25, 30); //pair
    gk.addEdge(30, 25);
    gk.addEdge(26, 30); //pair
    gk.addEdge(30, 26);
    gk.addEdge(26, 31); //pair
    gk.addEdge(31, 26);
    gk.addEdge(27, 31); //pair
    gk.addEdge(31, 27);
}
int boardToGraph(int row, int column){
    int vertex = 0;
    if(row == 2 && column == 4){
        vertex = 0;
    }
    if(row == 2 && column == 8){
        vertex = 1;
    }
    if(row == 2 && column == 12){
        vertex = 2;
    }
    if(row == 2 && column == 16){
        vertex = 3;
    }
    if(row == 4 && column == 2){
        vertex = 4;
    }
    if(row == 4 && column == 6){
        vertex = 5;
    }
    if(row == 4 && column == 10){
        vertex = 6;
    }
    if(row == 4 && column == 14){
        vertex = 7;
    }
    if(row == 6 && column == 4){
        vertex = 8;
    }
    if(row == 6 && column == 8){
        vertex = 9;
    }
    if(row == 6 && column == 12){
        vertex = 10;
    }
    if(row == 6 && column == 16){
        vertex = 11;
    }
    if(row == 8 && column == 2){
        vertex = 12;
    }
    if(row == 8 && column == 6){
        vertex = 13;
    }
    if(row == 8 && column == 10){
        vertex = 14;
    }
    if(row == 8 && column == 14){
        vertex = 15;
    }
    if(row == 10 && column == 4){
        vertex = 16;
    }
    if(row == 10 && column == 8){
        vertex = 17;
    }
    if(row == 10 && column == 12){
        vertex = 18;
    }
    if(row == 10 && column == 16){
        vertex = 19;
    }
    if(row == 12 && column == 2){
        vertex = 20;
    }
    if(row == 12 && column == 6){
        vertex = 21;
    }
    if(row == 12 && column == 10){
        vertex = 22;
    }
    if(row == 12 && column == 14){
        vertex = 23;
    }
    if(row == 14 && column == 4){
        vertex = 24;
    }
    if(row == 14 && column == 8){
        vertex = 25;
    }
    if(row == 14 && column == 12){
        vertex = 26;
    }
    if(row == 14 && column == 16){
        vertex = 27;
    }
    if(row == 16 && column == 2){
        vertex = 28;
    }
    if(row == 16 && column == 6){
        vertex = 29;
    }
    if(row == 16 && column == 10){
        vertex = 30;
    }
    if(row == 16 && column == 14){
        vertex = 31;
    }
    return vertex;
}
int graphToRow(int vertex){
    int row = 0;
    if(vertex == 0 || vertex == 1 || vertex == 2 || vertex == 3){
        row = 2;
    }
    if(vertex == 4 || vertex == 5 || vertex == 6 || vertex == 7){
        row = 4;
    }
    if(vertex == 8 || vertex == 9 || vertex == 10 || vertex == 11){
        row = 6;
    }
    if(vertex == 12 || vertex == 13 || vertex == 14 || vertex == 15){
        row = 8;
    }
    if(vertex == 16 || vertex == 17 || vertex == 18 || vertex == 19){
        row = 10;
    }
    if(vertex == 20 || vertex == 21 || vertex == 22 || vertex == 23){
        row = 12;
    }
    if(vertex == 24 || vertex == 25 || vertex == 26 || vertex == 27){
        row = 14;
    }
    if(vertex == 28 || vertex == 29 || vertex == 30 || vertex == 31){
        row = 16;
    }
    return row;
}
int graphToColumn(int vertex){
    int column = 0;
    if(vertex == 4 || vertex == 12 || vertex == 20 || vertex == 28){
        column = 2;
    }
    if(vertex == 0 || vertex == 8 || vertex == 16 || vertex == 24){
        column = 4;
    }
    if(vertex == 5 || vertex == 13 || vertex == 21 || vertex == 29){
        column = 6;
    }
    if(vertex == 1 || vertex == 9 || vertex == 17 || vertex == 25){
        column = 8;
    }
    if(vertex == 6 || vertex == 14 || vertex == 22 || vertex == 30){
        column = 10;
    }
    if(vertex == 2 || vertex == 10 || vertex == 18 || vertex == 26){
        column = 12;
    }
    if(vertex == 7 || vertex == 15 || vertex == 23 || vertex == 31){
        column = 14;
    }
    if(vertex == 3 || vertex == 11 || vertex == 19 || vertex == 27){
        column = 16;
    }
    return column;
}
void cpuMove(){
    cout << "CPU is thinking..." << endl;
    int attempt = 0;
    bool moveFound = false;
    int method = 0;
    moveFound = killMove();
    if(moveFound){ attempt = 5000; }
    while (attempt < 5000) {
        method = rand()%3;
        if (method == 0) {
            moveFound = normalMove();
            if(moveFound == true){ break; }
        }
        if (method == 1) {
            moveFound = kingMove();
            if(moveFound == true){ break; }
        }
        if (method == 2) {
            moveFound = endMove();
            if(moveFound == true){ break; }
        }
        attempt++;
    }
    if(moveFound == true){
        cout << "CPU has made it's move." << endl;
    }
    else{
        cout << "CPU has decided to skip it's turn." << endl;
    }
}
bool normalMove(){
    //black checker variables
    int start = 0;
    int sRow = 0;
    int sColumn = 0;
    
    //red checker variables
    int end = 0;
    int eRow = 0;
    int eColumn = 0;
    
    //check every black checker with every red checker
    for (start = 31; start > 0; start--) {
        sRow = graphToRow(start);
        sColumn = graphToColumn(start);
        if (board[sRow][sColumn] == "b") {
            for (end = 0; end < 32; end++) {
                eRow = graphToRow(end);
                eColumn = graphToColumn(end);
                if (board[eRow][eColumn] == "r" || board[eRow][eColumn] == "R") {
                    //find the path if there is one
                    if (g.isReachable(start, end)) {
                        int next = path[1];
                        int nRow = graphToRow(next);
                        int nColumn = graphToColumn(next);
                        string place = board[nRow][nColumn];
                        if (" " == place) {
                            board[nRow][nColumn] = board[sRow][sColumn];
                            board[sRow][sColumn] = " ";
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool kingMove(){
    //black king checker variables
    int start = 0;
    int sRow = 0;
    int sColumn = 0;
    
    //red checker variables
    int end = 0;
    int eRow = 0;
    int eColumn = 0;
    
    //check every black king checker with every red checker
    for (start = 31; start > 0; start--) {
        sRow = graphToRow(start);
        sColumn = graphToColumn(start);
        if (board[sRow][sColumn] == "B") { //minor adjustment to work with kings
            for (end = 0; end < 32; end++) {
                eRow = graphToRow(end);
                eColumn = graphToColumn(end);
                if (board[eRow][eColumn] == "r" || board[eRow][eColumn] == "R") {
                    //find the path if there is one
                    if (g.isReachable(start, end)) {
                        int next = path[1];
                        int nRow = graphToRow(next);
                        int nColumn = graphToColumn(next);
                        string place = board[nRow][nColumn];
                        if (" " == place) {
                            board[nRow][nColumn] = board[sRow][sColumn];
                            board[sRow][sColumn] = " ";
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool endMove(){
    //black checker variables
    int start = 0;
    int sRow = 0;
    int sColumn = 0;
    
    //end of board variables
    int end = 0;
    
    //check every black checker with every end vertex
    for (start = 31; start > 0; start--) {
        sRow = graphToRow(start);
        sColumn = graphToColumn(start);
        if (board[sRow][sColumn] == "b") {
            for (end = 28; end < 32; end++) {
                //find the path if there is one
                if (g.isReachable(start, end)) {
                    int next = path[1];
                    int nRow = graphToRow(next);
                    int nColumn = graphToColumn(next);
                    string place = board[nRow][nColumn];
                    if (" " == place) {
                        board[nRow][nColumn] = board[sRow][sColumn];
                        board[sRow][sColumn] = " ";
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool killMove(){
    int think = 0;
    while (think < 5) {
        int attacker = rand()%32;
        int aRow = graphToRow(attacker);
        int aColumn = graphToColumn(attacker);
        //if checker is normal
        if (board[aRow][aColumn] == "b") {
            if(board[aRow+2][aColumn+2] == "r" || board[aRow+2][aColumn+2] == "R"){ //lower right
                if(board[aRow+4][aColumn+4] == " "){
                    board[aRow+4][aColumn+4] = board[aRow][aColumn];
                    board[aRow][aColumn] = " ";
                    board[aRow+2][aColumn+2] = " ";
                    return true;
                }
            }
            else if(board[aRow+2][aColumn-2] == "r" || board[aRow+2][aColumn-2] == "R"){ //lower left
                if(board[aRow+4][aColumn-4] == " "){
                    board[aRow+4][aColumn-4] = board[aRow][aColumn];
                    board[aRow][aColumn] = " ";
                    board[aRow+2][aColumn-2] = " ";
                    return true;
                }
            }
        }
        //if checker is king
        else if (board[aRow][aColumn] == "B"){
            if(board[aRow+2][aColumn+2] == "r" || board[aRow+2][aColumn+2] == "R"){ //lower right
                if(board[aRow+4][aColumn+4] == " "){
                    board[aRow+4][aColumn+4] = board[aRow][aColumn];
                    board[aRow][aColumn] = " ";
                    board[aRow+2][aColumn+2] = " ";
                    return true;
                }
            }
            else if(board[aRow+2][aColumn-2] == "r" || board[aRow+2][aColumn-2] == "R"){ //lower left
                if(board[aRow+4][aColumn-4] == " "){
                    board[aRow+4][aColumn-4] = board[aRow][aColumn];
                    board[aRow][aColumn] = " ";
                    board[aRow+2][aColumn-2] = " ";
                    return true;
                }
            }
            else if(board[aRow-2][aColumn+2] == "r" || board[aRow-2][aColumn+2] == "R"){ //upper right
                if(board[aRow-4][aColumn+4] == " "){
                    board[aRow-4][aColumn+4] = board[aRow][aColumn];
                    board[aRow][aColumn] = " ";
                    board[aRow-2][aColumn+2] = " ";
                    return true;
                }
            }
            else if(board[aRow-2][aColumn-2] == "r" || board[aRow-2][aColumn-2] == "R"){ //upper left
                if(board[aRow-4][aColumn-4] == " "){
                    board[aRow-4][aColumn-4] = board[aRow][aColumn];
                    board[aRow][aColumn] = " ";
                    board[aRow-2][aColumn-2] = " ";
                    return true;
                }
            }
        }
        think++;
    }
    return false;
}
