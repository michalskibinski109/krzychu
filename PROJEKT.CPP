#include <iostream>
#include <fstream> 
#include <vector> 
#include <sstream> 

using namespace std;

/*


polimorfizm - bedzie ciezko
wyjatki

try {
  // Block of code to try
  throw exception; // Throw an exception when a problem arise
}
catch () {
  // Block of code to handle errors
}


szablony

template <typename T>
T minimum(const T& lhs, const T& rhs)
{
    return lhs < rhs ? lhs : rhs;
}


stringi stringstreamy

  std::stringstream ss;

  ss << 100 << ' ' << 200;

  int foo,bar;
  ss >> foo >> bar;

  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';
*/


// 0 - KOLKO
// 1 - KRZYZYK
class Player{
  int win;
  int loses;
  int totalGames;
  public:
  string name;
  Player(string n, int gamesInfo[3]){
    name = n;
  }
  string print(){
    return name;
  }
};
class Human: public Player
{
private:
  int symbol;
public:
  Human(string n, int gamesInfo[3], int s):Player(n, gamesInfo){
    symbol = s;
  };

};
class Computer: public Player
{
private:
  int symbol;
public:
  Computer(string n, int gamesInfo[3], int s):Player(n, gamesInfo){
    symbol = s;
  };

};



class Game {
  private:
  int board[9]; 
  vector<int> history; // lista wybranych pol w kolejnych turach
  Human p1;
  Computer p2;
  public:
  int result; //0 -  czarne; 1-remis; 2 - biale; -1 - nie ma wyniku
  Game(Human human, Computer computer): p1(human), p2(computer) {
    result = -1;
    history = {};
    for (int i = 0; i < 9; i++)board[i] = -1;
    
  }
  void print(){
    system("cls");
    string symbols[9];
    for (int i = 0; i < 9; i++)
    {
      switch (board[i])
      {
      case -1: //pole puste
        symbols[i] = '-';break;
      case 0: //kolko
        symbols[i] = 'X';break;
      case 1: //krzyzyk
        symbols[i] = 'O';break;
      }
    }
    
    cout << "\n\n"<<p1.name<<" vs "<<p2.name<<"\n\n";
    cout << endl;
    cout << "  " << symbols[0] << "  |  " << symbols[1] << "  |  " << symbols[2] << endl;
    cout << "  " << symbols[3] << "  |  " << symbols[4] << "  |  " << symbols[5] << endl;
    cout << "  " << symbols[6] << "  |  " << symbols[7] << "  |  " << symbols[8] << endl;
  }
};

int main(){
    int a[3] = {1,2,3};
    Human p1("human ",a, 0);
    Computer p2("computer ",a , 0);
    Game g(p1, p2);
    g.print();
    //p1.print();
}
