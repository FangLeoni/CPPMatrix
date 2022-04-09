// Internal libraries

#include <iostream>
#include <ncurses.h>
#include <unordered_map>
#include <cstring>
#include <string>
#include <functional>
#include <vector>


struct Player {
  int x = 0;
  int y = 0;

  std::vector< std::vector< std::string > > gameMatrix;
  int gameXLength;
  int gameYLength;

  void keyInput(int newX, int newY, std::string drctName) {  
    int newXCords = newX + this->x;
    int newYCords = newY + this->y;

    bool posistiveOutOfBounds = newXCords >= this->gameXLength || newYCords >= this->gameYLength;

    bool negativeOutOfBounds = newXCords < 0 || newYCords < 0;

    bool isOutOfBounds = posistiveOutOfBounds || negativeOutOfBounds;

    mvprintw(10,0, "%d ; %d", this->x , this->y);
    mvprintw(11,0, "%d ; %d", newX , newY);
    mvprintw(12,0, "%d ; %d", newXCords, newYCords);

    if(isOutOfBounds) return;

    this->gameMatrix[this->y][this->x] = ".";

    this->x = newXCords;
    this->y = newYCords;

    this->gameMatrix[newYCords][newXCords] = "#";  

  }

  void movePlayer(int direction) { 
    
    std::unordered_map<int, std::function<void()> > my_map = {
        { KEY_UP , [&](){keyInput(0, -1, "UP");} },
        { KEY_DOWN, [&](){keyInput(0, 1, "DOWN");} },
        { KEY_LEFT, [&](){keyInput(-1, 0, "LEFT");} },
        { KEY_RIGHT, [&](){keyInput(1, 0, "RIGHT");} }
    };
    
    my_map[direction]();
  }

};

std::string generateStringMatrix(
    const std::vector< 
      std::vector< std::string > 
    > &matrix
) {
  std::string fullString;

  int matrixYLength = matrix.size();
  int matrixXLength = matrix[0].size();

  for (int i = 0; i < matrixYLength; i++)
     for (int j = 0; j < matrixXLength; j++) {
       if(j == 0 ) fullString += "|";
       if(j < matrixXLength - 1 ) {
        fullString += matrix[i][j] + "|";
        continue;
       }
       fullString += matrix[i][j] + "| \n";
     }
  
  return fullString;
}

int main() {

  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, true);

  std::vector< std::vector< std::string > > myMatrix = {
    {".", ".", "."},
    {".", ".", "."},
    {".", ".", "."}
  };


  Player player1 = Player();
  player1.gameMatrix = myMatrix;
  player1.gameYLength = myMatrix.size();
  player1.gameXLength = myMatrix[0].size();

  std::string stringMatrix = generateStringMatrix(player1.gameMatrix);

  mvprintw(0,0, stringMatrix.c_str());

  for (int ch = getch(); ch != 'q'; ch = getch()) {
    
    player1.movePlayer(ch);
    
    std::string stringMatrix = generateStringMatrix(player1.gameMatrix);

    mvprintw(0,0, stringMatrix.c_str());

    clrtoeol();
    refresh();
  }

  endwin();
}
