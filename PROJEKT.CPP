#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <map>
#include <string>
#include <unistd.h> 
#include"Game.h"
using namespace std;

// 0 - KOLKO
// 1 - KRZYZYK
void play(){
  bool loadPlayersFromFile = false;
  cout<<"do you want to load previous players? ['y'/'n'] \n";
  string temp;
  cin>>temp;
  if (temp == "y")loadPlayersFromFile = true;//
  int a[3] = {0, 0, 0};
  Human p1("human ", a); //tworzymy obiekt human
  Computer p2("computer ", a); // tworzymy obiekt computer
  Game g(p1, p2); // przekazujemyy je do konstruktora game
  if(loadPlayersFromFile){
    g.loadPlayers();//ta funkcja nadpisuje atrybuty stworzonych domyslnych graczy 
  }
  g.print();
  while (g.isGameOver() == -1)//dopoki gra sie nie skonczy
  {
    int temp;
    cout << "\nmake move: ";
    cin >> temp;
    while(g.makeMove(temp) != true){//dopoki gracz nie wpisze poprawnego ruchu
    cout << "\nmake move: ";
    cin >> temp;//wpisuje od nowa
    }
    g.print();
    //komputer proponuje ruch w funkcji p2.findComputerMove(g.getboard())
    //a my zaproponowany ruch dajemy jako argument do funkcji makeMove
    int move = p2.findComputerMove(g.getboard());
    g.makeMove(move);
    sleep(.4);
    g.print();
  }
}

int main()
{
  play();
}