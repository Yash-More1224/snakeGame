#include <csignal>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include "custom.h"
#include <random>
#include <system_error>
#include <unistd.h>
#include <vector>
using namespace std;

// process/requirements:
// funcs:
// 1. to initialise variables,
// 2. to create the board: 
// 3. to update the game state after a key has been pressed:
          // check collision with wall or tail or food,
// 4. (optional) to return difficulty level of the game, entered by user 
// 5. to take and handle user input
// 6. main fn

// global variables:
bool gameOver;
// head coordinates of snake:
int x,y;
// fruit coordinates:
int fruitX, fruitY;
// body coordinates of snake:
vector<int>arrX;
vector<int>arrY;
// dimentions of board:
int height, width;
int score;
string name;
int snakeTailLength=0;
bool safePlace=true;
enum dir {
  STOP=0,UP,DOWN,LEFT,RIGHT
}direction=RIGHT;

void initiateVaiables(){
  height=15;
  width=30;
  x=width/2;
  y=height/2;
  fruitX=rand()%width;
  fruitY=rand()%height;
  gameOver=false;
  score=0;
}

void setBoard(string name){
  system("clear");
  cout<<"Player Name: "<<name<<"\t\t\t"<<"Score: "<<score<<endl;
  for (int i=0;i<width;i++){
    cout<<"-";
  }  
  cout<<endl;
  for (int i=0;i<height-2;i++){
    for (int j=0;j<width;j++){
      if (j==0 or j==width-1) {
        cout<<"|";
      } else if (i==y and j==x) {
        cout<<"0"; // head of the snake
      } else if (i==fruitY and j==fruitX) {
        cout<<"#";
      } else {
        bool putChar=false;
        for (int k=0;k<snakeTailLength;k++){
          if (i==arrY[k] and j==arrX[k]){
            cout<<"O";
            putChar=true;
            break;
          }
        }
        if (!putChar) cout<<" ";
      } 
    } cout<<endl;
  }

  for (int i=0;i<width;i++){
    cout<<"-";
  }  
  return;  
}


void updateBoard(){
  if (snakeTailLength>=2){
    for (int i=snakeTailLength-1;i>0;i--){
      arrX[i]=arrX[i-1];
      arrY[i]=arrY[i-1];
    }
  }
  switch (direction) {
    case UP:
      y++;
      break;
    case DOWN:
      y--;
      break;
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    default:
      break;
  }

  // check if snake crashed into wall:
  if (x>width-1 or x<=0 or y>=height-2 or y<-1){
    gameOver=true;
  }
  
  // srand(time(0));
  // if fruit is eaten:
  if(x==fruitX and y==fruitY){
    // while(!safePlace){
      fruitX=rand()%width-1;
      fruitY=rand()%height-1;
      // safePlace=true;
      // if(x==fruitX and y==fruitY) safePlace=false;
      // for (int k=0;k<snakeTailLength;k++){
        // if(arrX[k]==fruitX and arrY[k]==fruitY) safePlace=false;
      // }
    // }
    score++;
    arrX.push_back(x);
    arrY.push_back(y);
    // if (snakeTailLength==0)snakeTailLength+=2;
    snakeTailLength++;
  }
  if (snakeTailLength>=1){
    arrX[0]=x;
    arrY[0]=y;
  }
}

void takeUsrInput(){
  if (_kbhit()){
    switch (_getch()) {
      case 's':
        direction=UP;
        break;
      case 'w':
        direction=DOWN;
        break;
      case 'a':
        direction=LEFT;
        break;
      case 'd':
        direction=RIGHT;
        break;
      case 'x':
        gameOver=true;
        break;
      default:
        break;
    }
  }
}

int main(){
  cout<<"Enter Player name: ";
  cin>>name;
  initiateVaiables();
  while (!gameOver){
    setBoard(name);
    updateBoard();
    takeUsrInput();
      usleep(320000);
  }
  cout<<endl;
  cout<<"GAME OVER!!\n"<<name<<"\'s score is: "<<score<<endl;
  return 0;
}

