#include<iostream>
#include<ncurses.h>
#include "snake.h"

int main(){
   	Snake snake;
   	snake.startm();
	snake.init();
    snake.play();
   	getch(); // 콘솔 입력 함수 

   	endwin(); // curses모드 종료  -> 사용하지 않았을 시, 텍스트 모드 이상이 발생할 수 있음
   
    
   return 0;
}
