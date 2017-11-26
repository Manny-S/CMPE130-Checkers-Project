#include <iostream>
#include "checkers.hpp"
using namespace std;

string board[18][18];
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

int main() {
    int menu=0;
    
    while(menu!=3){
        cout<<""<<endl
        <<"1. 1 player"<<endl
        <<"2. 2 players"<<endl
        <<"3. Exit"<<endl;
        
        cin>>menu;
        
        if(menu == 1){
            printboard();
            while(Bcount!=0||Rcount!=0){
                userinput();
                updateboard();
                count();
            }
        }
        if(menu == 2){
            printboard();
            while(Bcount!=0||Rcount!=0){
                count();
            }
        }
    }
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
            board[i][j-2] = "R";    //testing kings in front (change back to "r" to test regular pieces in front)
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
    board[10][4] = "b"; //test jump
    board[10][8] = "B"; //test jump
    
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

/* working on it (won't allow king to jump piece)
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
 */
void userinput(){
    /* int r =0;
     int c =0;
     int r1=0;
     int c1=0;*/
    while(legal!=true){
        cout<<"Your turn"<<endl;
        cout<<"What piece would you like to move?"<<endl;
        c=columnInput();
        r=rowinput();
        
        cout<<"Where would you like to move it?"<<endl;
        c1=columnInput();
        r1=rowinput();
        
        if(board[r][c]=="R"){
            userKingMoveCheck();
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
        cout<<"Error. Choose your chess piece."<<endl;
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
        if(board[16][i]== "b"){
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
    cout<<Rcount<<Bcount;
}


