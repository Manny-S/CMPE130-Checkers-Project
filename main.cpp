#include <iostream>
#include "checkers.hpp"
using namespace std;

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


