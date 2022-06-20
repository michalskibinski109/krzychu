#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <map>
#include <string>

using namespace std;

/*
wykorzystanie akcesorów

polimorfizm - bedzie ciezko

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
class Player
{
private:
public:
  int wins;
  int draws;
  int loses;
  int totalGames;
  string name;
  Player(string n, int gamesInfo[3])
  {
    // gamesInfo - wektor[3 x 1] : {wins, loses, totalgames}
    name = n;
    wins = gamesInfo[0];
    loses = gamesInfo[1];
    totalGames = gamesInfo[2];
    draws = totalGames - wins - loses;
  }
  void printInfo()
  {
    system("cls"); // czyszczenie okna konsoli
    cout << string(20, '-') << endl;
    cout << "player name: " << name << endl;
    cout << string(20, '=') << endl;
    cout << "totalGames: " << totalGames << endl;
    cout << "wins: " << wins << endl;
    cout << "loses: " << loses << endl;
    cout << "draws: " << draws << endl;
    cout << string(20, '-') << endl;
  }
};

class Human : public Player
{
private:
  int symbol;

public:
  Human(string n, int gamesInfo[3], int s) : Player(n, gamesInfo)
  {
    symbol = s;
  };
};

class Computer : public Player
{
private:
  int symbol;

public:
  Computer(string n, int gamesInfo[3], int s) : Player(n, gamesInfo)
  {
    symbol = s;
  };

  int computerMove(int board[])
  {
    int r = 0;
    while (board[r] != -1)
    {
      srand(time(NULL));

      int r = rand() % 9;
    }
    return r;
  }
};

class Game
{
private:
  int result;
  int *board;
  vector<int> history; // lista wybranych pol w kolejnych turach
  Human p1;
  Computer p2;

public:
  Game(Human human, Computer computer, int boardSize = 9) : p1(human), p2(computer)
  {
    result = -1;
    history = {};
    board = new int[boardSize];
    for (int i = 0; i < 9; i++)
      board[i] = -1;
  }

  int getboard(); // uzycie akcesora

  void print()
  {
    system("cls");
    string symbols[9];
    for (int i = 0; i < 9; i++)
    {
      switch (board[i])
      {
      case -1: // pole puste
        symbols[i] = '-';
        break;
      case 0: // kolko
        symbols[i] = 'O';
        break;
      case 1: // krzyzyk
        symbols[i] = 'X';
        break;
      }
    }
    cout << "\n\n"
         << p1.name << " vs " << p2.name << "\n\n";
    cout << endl;
    cout << "  " << symbols[0] << "  |  " << symbols[1] << "  |  " << symbols[2] << endl;
    cout << "  " << symbols[3] << "  |  " << symbols[4] << "  |  " << symbols[5] << endl;
    cout << "  " << symbols[6] << "  |  " << symbols[7] << "  |  " << symbols[8] << endl;
  }

  void savePlayers()
  {
    ofstream outFile;
    outFile.open("players.txt");
    stringstream ss;
    ss << p1.name << p1.wins << " " << p1.loses << " " << p1.totalGames << endl;
    ss << p2.name << p2.wins << " " << p2.loses << " " << p2.totalGames << endl;
    outFile << ss.rdbuf();
  }

  void loadPlayers()
  {
    ifstream inFile;
    inFile.open("players.txt");
    string name;
    int a, b, c;
    inFile >> name >> a >> b >> c;
    p1.draws = c - b - a;
    p1.name = name;
    p1.loses = a;
    p1.wins = b;
    p1.totalGames = c;
    inFile >> name >> a >> b >> c;
    p2.draws = c - b - a;
    p2.name = name;
    p2.loses = a;
    p2.wins = b;
    p2.totalGames = c;
  }

  int isGameOver()
  {
    // 1 -  czarne; 0-biale; 2 - remis; -1 - nie ma wyniku
    result = -1;
    // checking the win for Simple Rows and Simple Column
    for (int i = 0; i < 3; i++)
    {
      if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2])
        return board[i * 3];
      if (board[i] == board[3 + i] && board[i] == board[6 + i])
        return board[i];
    }
    if (board[0] == board[8] && board[0] == board[4])
      return board[0];
    if (board[6] == board[4] && board[2] == board[4])
      return board[6];
    if (history.size() == 9)
      return 2;
    return -1;
  }

  bool makeMove(int move)
  {
    int color = (history.size() % 2); // size zwraca dlugosc wektora
    try
    {
      board[move] = color;
      history.push_back(move);
    }
    catch (const out_of_range &oor)
    {
      cout << "typed invalid number" << endl;
      return false;
    }
    if (isGameOver() != -1)
    {
      switch (isGameOver())
      {
      case 0:
      {
        p1.wins++;
        p2.loses++;
      }
      break;
      case 1:
      {
        p2.wins++;
        p1.loses++;
      }
      break;
      case 2:
      {
        p1.draws++;
        p2.draws++;
      }
      break;
      }
      return true;
    }
  };

  int main()
  {
    int a[3] = {1, 2, 3};
    Human p1("human ", a, 0);
    Computer p2("computer ", a, 0);
    Game g(p1, p2);
    // p1.saveToFile();
    //  int temp = 0;
    //  while (g.isGameOver() == -1)
    //  {
    //    cout << "make move: ";
    //    cin >> temp;
    //    g.makeMove(temp);
    //    g.print();
    //  }
    //  p1.printInfo();
  }
