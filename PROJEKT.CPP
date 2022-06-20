#include <iostream>
#include <fstream> 
#include <vector> 
#include <sstream> 

using namespace std;


/*
operatory
							Common operators
assignment | increment | arithmetic |  logical | comparison | member | other
		   | decrement |            |		   |		    | access |
-----------------------------------------------------------------------------                            
  a = b    |    ++a    |     +a	    |	 !a	   |   a == b   |  a[b]  | a(...)
  a += b   |	--a	   |     -a		|  a && b  |   a != b   |   *a   |  a, b
  a -= b   |	a++	   |   a + b	|  a || b  |   a < b    |   &a   |  ? :
  a *= b   |	a--	   |   a - b	|	       |   a > b    |  a->b  |
  a /= b   |		   |   a * b	|	       |   a <= b	|  a.b   |
  a %= b   |		   |   a / b	|		   |   a >= b	|  a->*b |
  a &= b   |		   |   a % b	|		   |   a <=> b	|  a.*b  |


zarzadzanie pamiecia
  int size;

  std::cin >> size;

  int *array = new int[size];

  delete [] array;
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

kontenery stl

int main() {

  // initialize a vector of int type
  vector<int> numbers = {1, 100, 10, 70, 100};

  // print the vector
  cout << "Numbers are: ";
  for(auto &num: numbers) {
    cout << num << ", ";
  }

  return 0;
}

stringi stringstreamy

  std::stringstream ss;

  ss << 100 << ' ' << 200;

  int foo,bar;
  ss >> foo >> bar;

  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';
*/



// Example in a game we have multiple entities so we put commom functionality and variables in base class Entity and Create Sub Classes Of the base class
class Player{
  private:
  int sign; //0 - kolko 1 - krzyzyk
  int win;
  int loses;
  string name;
  int totalGames;
  Player(string name, int gamesInfo[]){
    name = name  
    
  }
};
class Game {
protected:
  int i;
  Player player[2];
public:
  Game(int x) {
     i = x;}
};


class Board: public Game {
  int j;
public:
  // derived uses x; y is passed along to base.
  Board(int x, int y): Game(y)
     { j = x; cout << "Constructing derived\n"; }

  void show() { cout << i << " " << j << "\n"; }
};
int main(){
    cout<<"";

    return(0);
}
