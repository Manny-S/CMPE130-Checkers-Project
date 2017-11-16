#include <iostream>
using namespace std;

int main() {
    char board[18][18];
    board[0][0]=' ';
    board[2][0] = '1';
    board[4][0] = '2';
    board[6][0] = '3';
    board[8][0] = '4';
    board[10][0] = '5';
    board[12][0] = '6';
    board[14][0] = '7';
    board[16][0] = '8';
    
    for(int i = 1; i<18;i++){
        board[0][i] = ' ';
        board[i][0] = ' ';
        i++;
    }
    
    
    board[0][2] = 'A';
    board[0][4] = 'B';
    board[0][6] = 'C';
    board[0][8] = 'D';
    board[0][10] = 'E';
    board[0][12] = 'F';
    board[0][14] = 'G';
    board[0][16] = 'H';
    
    for(int i = 1;i<18;i++){
        for(int j = 1; j<18;j++){
            board[i][j] = '+';
            j++;
        }
        i++;
    }
    
    for(int i = 1;i<18;i++){
        for(int j = 2; j<18;j++){
            board[i][j] = '-';
            j++;
        }
        i++;
    }
    
    for(int i = 2;i<18;i++){
        for(int j = 1; j<18;j++){
            board[i][j] = '|';
            j++;
        }
        i++;
    }
    
    //Fills in whitespaces for rows 4-5 on board
    for(int i = 8;i<11;i++){
        for(int j = 2; j<18;j++){
            board[i][j] = ' ';
            j++;
        }
        i++;
    }
    
    //Places black (B) pieces and whitespaces for rows 1-3 on board
    for(int i = 2;i<3;i++){
        for(int j=2;j<18;j++){
            board[i][j] = ' ';
            board[i][j+2] = 'b';
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 4; i<5; i++){
        for(int j = 4; j<18;j++){
            board[i][j] = ' ';
            board[i][j-2] = 'b';
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 6;i<7;i++){
        for(int j=2;j<18;j++){
            board[i][j] = ' ';
            board[i][j+2] = 'b';
            j++;
            j++;
            j++;
        }
    }
    
    //places red (R) pieces and white spaces for rows 6-8 on board
    for(int i = 12; i<13; i++){
        for(int j = 4; j<18;j++){
            board[i][j] = ' ';
            board[i][j-2] = 'r';
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 14;i<15;i++){
        for(int j=2;j<18;j++){
            board[i][j] = ' ';
            board[i][j+2] = 'r';
            j++;
            j++;
            j++;
        }
    }
    
    for(int i = 16; i<17; i++){
        for(int j = 4; j<18;j++){
            board[i][j] = ' ';
            board[i][j-2] = 'r';
            j++;
            j++;
            j++;
        }
    }
    
    //Prints out board
    for(int i =0;i<18;i++){
        for(int j=0; j<18;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    
    return 0;
}
