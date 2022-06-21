#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <time.h>
#include <map>
#include <string>
#include <unistd.h> 

using namespace std;

/*
polimorfizm - bedzie ciezko

szablony

template <typename T>
T minimum(const T& lhs, const T& rhs)
{
    return lhs < rhs ? lhs : rhs;
}
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
  Player(string n, int gamesInfo[3]) // nigdy nie powstanie obiekt tej klasy w naszym programie
  {
    //konstruktor jest wywolywany przy tworzeniu obiektu klasy
    // gamesInfo - wektor[3 x 1] : {wins, loses, totalgames}
    name = n; //atrybut obiektu klasy
    wins = gamesInfo[0];
    loses = gamesInfo[1];
    totalGames = gamesInfo[2];
    draws = totalGames - (wins + loses);
  }
  void printInfo() // wyswietlanie informacji
  {
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

class Human : public Player //human dziedziczy po player
{

public:
  // konstruktor klasy ktora dziedziczy wywoluje konstruktor rodzica
  Human(string n, int gamesInfo[3]) : Player(n, gamesInfo)
  {
    // nic tu sie nie dzieje
  };
};

class Computer : public Player // dziedziczy player
{
public:
  Computer(string n, int gamesInfo[3]) : Player(n, gamesInfo)
  {
    //pusty konstruktor 
  };

  int findComputerMove(int board[])// funkcja zwraca ruch ktory komputer proponuje
  {
    int r = 0;
    while (board[r] != -1)
    {
      srand(time(NULL));
      r = rand() % 9;
      }
    return r;// to jest ruch ktory komputer chce zagrac [nierownoznaczne z zagraniem go]
  }
};

class Game
{
private: // atrybuty prywatne sa dostepne tylko wewnatrz tej klasy
  int result;
  int *board; //prywatne wiec tworzymy
  vector<int> history; // uzycie kontenera STL jakim jest wektor
  Human p1;
  Computer p2;

public:
//do konstruktora podajemy gotowe juz obiekty computer i human
//p1 bedzie przechopwywal odebrany obiekt human
//p2 bedzie przechopwywal odebrany obiekt computer
  Game(Human human, Computer computer, int boardSize = 9) : p1(human), p2(computer)
  {
    history = {};//zapisujemy kolejne ruchy 
    //jezeli ilosc ruchow jest parzysta to znaczy ze ruch krzyzyk
    board = new int[boardSize];//dynamiczna alokacja pamieci zarzadzanie pamiecia
    for (int i = 0; i < 9; i++)
      board[i] = -1;// budujemy board[1 x 9] i wszedzize - 1czyli puste polaa
  }

  int *getboard(){ 
    //uzycie akcesora
    return board; //nie mozna by poprostu tego zarzadac bo jest prywatne
  }
  void print()//wyswietla board
  {
    system("cls");//czysci konsole
    string symbols[9];//symbols beda zawieraky konwersje liczb na symbole 1 - o i 0 - x
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
    cout << endl;
    cout << "  " << 0 << "  |  " << 1 << "  |  " << 2 << endl;
    cout << "  " << 3 << "  |  " << 4 << "  |  " << 5 << endl;
    cout << "  " << 6 << "  |  " << 7 << "  |  " << 8 << endl;
    cout << "\n\n"
         << p1.name << " vs " << p2.name << "\n\n";
    cout << endl;
    cout << "  " << symbols[0] << "  |  " << symbols[1] << "  |  " << symbols[2] << endl;
    cout << "  " << symbols[3] << "  |  " << symbols[4] << "  |  " << symbols[5] << endl;
    cout << "  " << symbols[6] << "  |  " << symbols[7] << "  |  " << symbols[8] << endl;
  }

  void savePlayers()
  {
    //zapisuje graczy do pliku
    ofstream outFile;
    outFile.open("players.txt");
    stringstream ss; // uzycie stringstreama
    //stringstream dziala jak cout tylko zamiast wyswietlac to zapisuje

    ss << p1.name << " " << p1.wins << " " << p1.loses << " " << p1.totalGames << endl;
    ss << p2.name << " " << p2.wins << " " << p2.loses << " " << p2.totalGames << endl;
    outFile << ss.rdbuf();// wrzucamy do pliku rdbuff - zwraca zawartosc ss gdyby nie bylo zapisali bysmy adres w pamieci naszego ss
  }

  void loadPlayers()
  {
    //odczytuje graczy z pliku
    ifstream inFile;
    inFile.open("players.txt");
    string name;
    int a, b, c;
    inFile >> name >> a >> b >> c;//odczytujemy po spacji kolejne atrybuty
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
    //sprawdza czy gra skonczona 

    // zwraca 1 -  krzyzyk; 0-kolko; 2 - remis; -1 - nie ma wyniku
    for (int i = 0; i < 3; i++)// sprawdzamy pion i poziom
    {
      if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2])
        return board[i * 3];
      if (board[i] == board[3 + i] && board[i] == board[6 + i])
        return board[i];
    }
    //sprawdzamy skos
    if (board[0] == board[8] && board[0] == board[4])
      return board[0];
    if (board[6] == board[4] && board[2] == board[4])
      return board[6];
    if (history.size() == 9)//jesli wszystie pola sa zapelnione
      return 2;//zwroc remis
    return -1;//jesli nic z powyzszych zwroc gra sie nie skonczyla
  }

  bool makeMove(int move)
  {
    //zrob ruch
    //symbol zawiera 0 jesli kolko na ruchu
    //1 jesli krzyzyk
    int symbol = (history.size() % 2); // size zwraca dlugosc wektora
    try
    {
      if(board[move] == -1)
      {
      board[move] = symbol;
      history.push_back(move);
      }
      else{
        cout<<"invalid square\n";
        return false;
      }
    }
    catch (const out_of_range &oor)//jesli wyszedles poza skale planszy zwroci wyjatek
    {
      cout << "typed invalid number" << endl;
      return false;
    }
    if(isGameOver() != -1){//jesli gra sie skonczyla
      p1.totalGames++;//do playerow dodajemy statystyki
      p2.totalGames++;
      system("cls");
      switch (isGameOver())
      {
      case 0://wygralo kolko
      {
        cout<<"you won";
        p1.wins++;
        p2.loses++;
      }
      break;
      case 1:
      {
        cout<<"you lost";
        p2.wins++;
        p1.loses++;
      }
      break;
      case 2:
      {
        cout<<"draw";
        p1.draws++;
        p2.draws++;
      }
      break;
      }
      //tutaj jest zawarty interfejs po skonczonej grze
      p1.printInfo();//wyswietlamy informacje o graczach to jest funkcja rodzica
      p2.printInfo();
      string temp;
      cout<<"type s if you want save players status to file or any letter to play again\n";
      cin >> temp;
      if (temp == "s"){
        cout<<"saving . . . ";
        sleep(.5);
        savePlayers();//jesli gracz chce zapisac stastystyki do pliku to zapisuej
        return true;
      }
      history.clear();
      for (int i = 0; i < 9; i++)
        board[i] = -1;
        return false;
      print();
      //to do zwalnianie pamieci
  }
  return true;
  }
};

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