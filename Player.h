
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
