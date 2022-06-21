
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