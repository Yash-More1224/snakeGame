#include <cstdio>
#include <iostream>
#include "custom.h"
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int _kbhit(){
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt=oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
  tcsetattr(STDIN_FILENO,TCSANOW,&newt);

  oldf=fcntl(STDIN_FILENO,F_GETFL,0);
  fcntl(STDIN_FILENO,F_SETFL,oldf | O_NONBLOCK); // set it, for immediate return

  // getting the pressed key on the keyboard
  ch = getchar();

  // restore terminal settings:
  tcsetattr(STDIN_FILENO,TCSANOW ,&oldt );
  fcntl(STDIN_FILENO,F_SETFL,oldf);

  // if key is pressed:
  if(ch!=EOF){
    ungetc(ch,stdin); // put the character ch back to the input stream     
                      // so that it can be read by other fuctions
    return 1;
  }

  // if no key was pressed
  return 0;
}

char _getch(){
  struct termios oldt, newt;  
  char ch;

  tcgetattr(STDIN_FILENO,&oldt);
  newt=oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&newt);

  // safe to get the char, as the terminal setting have been changed!!
  ch=getchar();

  // restore the settings:
  tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    
  return ch;
}


