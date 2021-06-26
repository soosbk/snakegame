#include "snake.h"
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#define MAPS "map" 


enum BLOCKS{
    NONE,
    EMPTY,
    WALL,
    IMMUNE_WALL,
    HEAD,
    BODY,
    GROWTH,
    POISON,
    GATE,
};

int tmp='d'; //이전 방향을 저장하는 전역 변수
int MAP[NLINE][NCOL]={
                                    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}
                                };


Snake::Snake(){
    v[0].x = 3; v[0].y = 5;
    v[1].x = 4; v[1].y = 5;
    v[2].x = 5; v[2].y = 5;

    dir = 'd';

    growth.x = -1; growth.y = -1;
    poison.x = -1; poison.y = -1;
    gate2.x=-1; gate2.y=-1;
    gate1.x=-1; gate1.y=-1;
    
    isPoison = false;
    isGrowth = false;
}

void Snake::init(int count){
    initscr();  
    noecho(); 
     
    colorInit();
    
    
    resize_term(300, 300);
    border('I', 'I', ' ', ' ', ' ', ' ', ' ', ' ');
    
    
    mapWin = newwin(NLINE+100, NCOL+200, 2, 2);
    
    //scoreWin = newwin(20,20,2,2);
    createScore();
    createMission();
    setMap(count);
    createMap();
    
    //wrefresh(main_map);
}

void Snake::setDefault(){
	v[0].x = 3; v[0].y = 5;
    v[1].x = 4; v[1].y = 5;
    v[2].x = 5; v[2].y = 5;

    dir = 'd';

    growth.x = -1; growth.y = -1;
    poison.x = -1; poison.y = -1;
    gate2.x=-1; gate2.y=-1;
    gate1.x=-1; gate1.y=-1;


    isPoison = false;
    isGrowth = false;
    len=3;
    game=true;
    tmp='d';
    score[0]=len;
    score[1]=0;
    score[2]=0;
    score[3]=0;

    mission[0]=false;
    mission[1]=false;
    mission[2]=false;
    mission[3]=false;

    continued=true;

}

void Snake::colorInit(){
    start_color();
    init_pair(EMPTY, COLOR_BLACK, COLOR_BLACK);
    init_pair(WALL, COLOR_BLUE, COLOR_BLUE);
    init_pair(IMMUNE_WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(HEAD, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(BODY, COLOR_CYAN, COLOR_CYAN);
    init_pair(GROWTH, COLOR_GREEN, COLOR_GREEN);
    init_pair(POISON, COLOR_RED, COLOR_RED);
    init_pair(GATE,COLOR_MAGENTA,COLOR_MAGENTA);

}

void Snake::startm(){
	initscr();  
    noecho(); 
     
    colorInit();
    
    
    resize_term(300, 300);
    border('I', 'I', '-', '-', '-', '-', '-', '-');
    
	startWin = newwin(NLINE+100, NCOL+200, 2, 2);
    srand(time(NULL));
	for(int i=15;i<40;i++){    //0-35
        for(int j=32;j<130;j++){ //50-104
            if(i==15){
                wattron(startWin, COLOR_PAIR(IMMUNE_WALL));
                mvwprintw(startWin, i, j, " ");
                wattroff(startWin, COLOR_PAIR(IMMUNE_WALL));
            }
            else if (i==15||i==39||j==32||j==129)
            {
                wattron(startWin, COLOR_PAIR(HEAD));
                mvwprintw(startWin, i, j, " ");
                wattroff(startWin, COLOR_PAIR(HEAD));
            }
        }
    }
	mvwprintw(startWin,15,39,"Hi, player");
    mvwprintw(startWin,20,39,"1. press ");
    mvwprintw(startWin,21,39,"   w: up");
    mvwprintw(startWin,22,39,"   a: left");
    mvwprintw(startWin,23,39,"   s: down");
    mvwprintw(startWin,24,39,"   d: right");
    mvwprintw(startWin,26,39,"2. round is 4 ");
    
    mvwprintw(startWin,28,39,"3. You can select Map Random Mode or Map Sequential Mode");
	mvwprintw(startWin,30,39,"If you random Map mode, Press r!");
	mvwprintw(startWin,31,39,"If you Sequential mode, Press 'n'!");
    mvwprintw(startWin,33,39,"Have a nice day:)");
	wrefresh(startWin);
	char c=0x00;
	while (true){
		

		c=std::cin.get();
		if (c == 'r'){
			
			random=true;
            int pic=rand()%23;
			for(int i=0;i<4;i++) mapMode[i]=mapMode_save[pic][i];
			
			

			break;
		}
  		else if (c=='n')  {
            random=false;
  			for(int i=0;i<4;i++) mapMode[i]=mapMode_save[0][i];
            break;
		}
  		else continue;
  	}
}


void Snake::createScore(){
	for(int i=0;i<NLINE-5;i++){    //0-35
    	for(int j=NCOL+20;j<NCOL+55;j++){ //50-104
    		if(i==0){
    			wattron(mapWin, COLOR_PAIR(IMMUNE_WALL));
    		    mvwprintw(mapWin, i, j, " ");
	            wattroff(mapWin, COLOR_PAIR(IMMUNE_WALL));
    		}
    		else if (i==0||i==NLINE-6||j==NCOL+20||j==NCOL+54)
    		{
    			wattron(mapWin, COLOR_PAIR(POISON));
    		    mvwprintw(mapWin, i, j, " ");
	            wattroff(mapWin, COLOR_PAIR(POISON));
	        }
    	}
    }
    mvwprintw(mapWin,0,71,"Score Board");
    mvwprintw(mapWin,3,63,"BODY");
    mvwprintw(mapWin,6,63,"GROWTH");
    mvwprintw(mapWin,9,63,"POISON");
    mvwprintw(mapWin,12,63,"Gate");
}

void Snake::setScore(){
	mvwprintw(mapWin,3,83,to_string(len).c_str());
	mvwprintw(mapWin,3,85," / ");
	mvwprintw(mapWin,3,87,to_string(score[0]).c_str());
    mvwprintw(mapWin,6,83,to_string(score[1]).c_str());
    mvwprintw(mapWin,9,83,to_string(score[2]).c_str());
    mvwprintw(mapWin,12,83,to_string(score[3]).c_str());
    wrefresh(mapWin);
    
}

void Snake::createMission(){
	for(int i=NLINE+3;i<NLINE+20;i++){    //50-85
    	for(int j=NCOL+20;j<NCOL+55;j++){ //50-104
    		if(i==NLINE+3){
    			wattron(mapWin, COLOR_PAIR(IMMUNE_WALL));
    		    mvwprintw(mapWin, i, j, " ");
	            wattroff(mapWin, COLOR_PAIR(IMMUNE_WALL));
    		}
    		else if (i==NLINE+3||i==NLINE+19||j==NCOL+20||j==NCOL+54)
    		{
    			wattron(mapWin, COLOR_PAIR(BODY));
    		    mvwprintw(mapWin, i, j, " ");
	            wattroff(mapWin, COLOR_PAIR(BODY));
	        }
    	}
    }
    mvwprintw(mapWin,NLINE+3,71,"Mission Board");
    mvwprintw(mapWin,NLINE+6,63,"Max Body: 7");
    mvwprintw(mapWin,NLINE+9,63,"Growth: 5");
    mvwprintw(mapWin,NLINE+12,63,"Poison: 2");
    mvwprintw(mapWin,NLINE+15,63,"Gate: 3");

}

void Snake::setMission(){
	
	if(mission[0]==true) mvwprintw(mapWin,NLINE+6,83,"OK");
	else mvwprintw(mapWin,NLINE+6,83,"  ");
	

    if(mission[1]==true) mvwprintw(mapWin,NLINE+9,83,"OK");
    else mvwprintw(mapWin,NLINE+9,83,"  ");
    

    if(mission[2]==true) mvwprintw(mapWin,NLINE+12,83,"OK");
    else mvwprintw(mapWin,NLINE+12,83,"  ");
    

    if(mission[3]==true) mvwprintw(mapWin,NLINE+15,83,"OK");
    else mvwprintw(mapWin,NLINE+15,83,"  ");
    
    wrefresh(mapWin);
    
}


void Snake::setStage(){
    if (random==true) mvwprintw(mapWin,NLINE-20,150,"[Random Mode]");
    else mvwprintw(mapWin,NLINE-20,150,"[Sequential Mode]");
    for(int i=NLINE-15;i<NLINE+5;i++){    //0-35
        for(int j=140;j<190;j++){ //50-104
            if (i==NLINE-15||i==NLINE+4||j==140||j==189)
            {
                wattron(mapWin, COLOR_PAIR(HEAD));
                mvwprintw(mapWin, i, j, " ");
                wattroff(mapWin, COLOR_PAIR(HEAD));
            }
        }
    }

    mvwprintw(mapWin,NLINE-10,150,"Try:");
    mvwprintw(mapWin,NLINE-10,160,to_string((score_save[count][1])+1).c_str());
    mvwprintw(mapWin,NLINE+1,150,"Round: ");
    mvwprintw(mapWin,NLINE+1,160,to_string(count+1).c_str());
    mvwprintw(mapWin,NLINE+1,170," / ");
    mvwprintw(mapWin,NLINE+1,180,"4");
    wrefresh(mapWin);
}

void Snake::midScene(){
	startWin = newwin(NLINE+100, NCOL+200, 2, 2);
    
	score_save[count][1]+=1;
    for(int i=12;i<21;i++){    //0-35
        for(int j=35;j<100;j++){ //50-104
            if (i==12||i==20||j==35||j==99)
            {
                wattron(startWin, COLOR_PAIR(HEAD));
                mvwprintw(startWin, i, j, " ");
                wattroff(startWin, COLOR_PAIR(HEAD));
            }
        }
    }
	//wattron(mapWin, COLOR_PAIR(IMMUNE_WALL));
	mvwprintw(startWin,15,39,"LOSE!");
    mvwprintw(startWin,18,39,"Reason: ");
    if(reason==1) mvwprintw(startWin,18,48,"Because Body is too short(Too many Poison)");
    else if(reason==2) mvwprintw(startWin,18,48,"Wrong Direction Key!");
    else if(reason==3) mvwprintw(startWin,18,48,"Colliding with Walls");
    //else if(reason==4) mvwprintw(startWin,18,48,"Because Body is too short");
    
	//wattron(mapWin, COLOR_PAIR(POISON));
	mvwprintw(startWin,22,39,"If you continue game, Press o!");
	//wattron(mapWin, COLOR_PAIR(POISON));
	mvwprintw(startWin,25,39,"If you want to break, Press 'b'!");
    scoreScene(1);
	//wattroff(mapWin, COLOR_PAIR(POISON));
	wrefresh(startWin);
	char ch=0x00;
	while (true){
		std::cin.get(ch);
		if (ch == 'o'){
            continued=true;
            break;
        }
  		else if (ch=='b')  {
  			
            continued=false;
  			break;
		}
  		else continue;
  	}
	
	//sleep(60);
}

void Snake::successScene(){
	startWin = newwin(NLINE+100, NCOL+200, 2, 2);
	mvwprintw(startWin,15,39,"Success!");
	mvwprintw(startWin,20,39,"If you continue game, Press 'o'!");
	mvwprintw(startWin,23,39,"If you want to break, Press 'b'!");
    scoreScene(2);
	wrefresh(startWin);
	char ch=0x00;
	while (true){
  		cin.get(ch);
		if (ch == 'o') {
            continued=true;
            break;
        }
  		else if (ch=='b')  {
  			continued=false;
  			break;
		}
		else continue;
  	
  	}
	
	//sleep(60);
}


void Snake::completeScene(){
    startWin = newwin(NLINE+100, NCOL+200, 2, 2);
    if(count==3) mvwprintw(startWin,15,39,"Every STAGE 4 Complete!");
    else mvwprintw(startWin,15,39,"Thank you for playing our game!");
    mvwprintw(startWin,20,39,"Good job!!");
    mvwprintw(startWin,23,39,"Press 'b'! and you can exit this game");
    scoreScene(3);
    wrefresh(startWin);
    char ch=0x00;
    while (true){
        cin.get(ch);
        if (ch == 'b') {
            break;
        }
        
        else continue;
    
    }
    
    //sleep(60);
}



void Snake::scoreScene(int scene_option){

    for(int i=27;i<54;i++){    //0-35
        for(int j=36;j<170;j++){ //50-104
            if(i==27){
                wattron(startWin, COLOR_PAIR(IMMUNE_WALL));
                mvwprintw(startWin, i, j, " ");
                wattroff(startWin, COLOR_PAIR(IMMUNE_WALL));
            }
            else if (i==27||i==53||j==36||j==169)
            {
                wattron(startWin, COLOR_PAIR(HEAD));
                mvwprintw(startWin, i, j, " ");
                wattroff(startWin, COLOR_PAIR(HEAD));
            }
        }
    }
// print died, max body, growth num, poison, gate
    if (scene_option==1)  //call by midscene()
    {
        mvwprintw(startWin,31,39,"<This Round>");
        mvwprintw(startWin,33,39,"How many Play: ");
        mvwprintw(startWin,35,39,"How much is the longest body: ");
        mvwprintw(startWin,37,39,"How much of an growth item the snake ate: ");
        mvwprintw(startWin,39,39,"How much of an poison item the snake ate: ");
        mvwprintw(startWin,41,39,"How much of an gate the snake passed: ");

        mvwprintw(startWin,33,150,to_string(score_save[count][1]).c_str());
        mvwprintw(startWin,35,150,to_string(score[0]).c_str());
        mvwprintw(startWin,37,150,to_string(score[1]).c_str());
        mvwprintw(startWin,39,150,to_string(score[2]).c_str());
        mvwprintw(startWin,41,150,to_string(score[3]).c_str());
    }

    else if(scene_option==2){ //call by successscene()
        count_max(1);
        mvwprintw(startWin,30,39,"<This Round>");
        mvwprintw(startWin,33,39,"How many Play: ");
        mvwprintw(startWin,35,39,"How much is the longest body: ");
        mvwprintw(startWin,37,39,"How much of an growth item the snake ate: ");
        mvwprintw(startWin,39,39,"How much of an poison item the snake ate: ");
        mvwprintw(startWin,41,39,"How much of an gate the snake passed: ");

        mvwprintw(startWin,33,150,to_string(score_save[count][1]).c_str());
        mvwprintw(startWin,35,150,to_string(score_save[count][0]).c_str());
        mvwprintw(startWin,37,150,to_string(score_save[count][2]).c_str());
        mvwprintw(startWin,39,150,to_string(score_save[count][3]).c_str());
        mvwprintw(startWin,41,150,to_string(score_save[count][4]).c_str());
    
    }

    else if(scene_option==3){  //call by completeScene()
        count_max(2);
        mvwprintw(startWin,30,39,"<Total score>");
        mvwprintw(startWin,33,39,"Mode: ");
        mvwprintw(startWin,36,39,"Round: ");
        mvwprintw(startWin,39,39,"How many Play: ");
        mvwprintw(startWin,41,39,"How much is the longest body: ");
        mvwprintw(startWin,44,39,"How much of an growth item the snake ate: ");
        mvwprintw(startWin,47,39,"How much of an poison item the snake ate: ");
        mvwprintw(startWin,50,39,"How much of an gate the snake passed: ");

        if (random==true) mvwprintw(startWin,33,150,"[Random Mode]");
        else mvwprintw(startWin,33,150,"[Sequential Mode]");
        mvwprintw(startWin,36,150,to_string(count+1).c_str());
        mvwprintw(startWin,39,150,to_string(total_num[1]).c_str());
        mvwprintw(startWin,41,150,to_string(total_num[0]).c_str());
        mvwprintw(startWin,44,150, to_string(total_num[2]).c_str());
        mvwprintw(startWin,47,150,to_string(total_num[3]).c_str());
        mvwprintw(startWin,50,150, to_string(total_num[4]).c_str());
    
    }

}


void Snake::count_max(int count_option){
    //how many died
    //maxbody
    //growth
    //poison
    //gate
    if(count_option==1){  //this round end
        //int score_save[4][5]={{0x00,},}; 
        if (score_save[count][0]<score[0]) score_save[count][0]=score[0];
        score_save[count][1]+=1;
        for(int i=2;i<5;i++){
            score_save[count][i]=score[i-1];
        }
    }
 
    else if(count_option==2){ //total round end
        //int total_num[5]={0x00,};
        total_num[0]=score_save[count][0];
        for(int i=0;i<=count;i++){
            if(total_num[0]<score_save[i][0]) total_num[0]=score_save[i][0];
        }
        for(int i=1;i<5;i++){
            for(int j=0;j<=count;j++){
                total_num[i]+=score_save[j][i-1];
            }
        }

    }
    
}

void Snake::createMap() {
    for (int i = 0; i < NLINE; ++i){
        for (int j = 0; j < NCOL; ++j){
            // Wall
            if (MAP[i][j] == 1){
                wattron(mapWin, COLOR_PAIR(WALL));
                mvwprintw(mapWin, i, j, " ");
                wattroff(mapWin, COLOR_PAIR(WALL));
            }
            
            //Immune Wall
            if (MAP[i][j] == 2){
                wattron(mapWin, COLOR_PAIR(IMMUNE_WALL));
                mvwprintw(mapWin, i, j, " ");
                wattroff(mapWin, COLOR_PAIR(IMMUNE_WALL));
            }
        }
    }

}

void Snake::moveSnake(char key) {
    // snake가 움직일 때 빈 부분 처리  
    wattron(mapWin,COLOR_PAIR(EMPTY));
    for(int i = 0; i < len; i++)
        mvwprintw(mapWin,v[i].y,v[i].x," ");
    wattroff(mapWin,COLOR_PAIR(EMPTY));
    wrefresh(mapWin);
    
    // 아무것도 입력되지 않았을 때는 dir의 처음 방향인 오른쪽으로 감  
   
    if(key != 'n')
        dir = key;
         
    if(dir == 'w'){ // 위쪽
        if(v[0].x == growth.x && v[0].y - 1 == growth.y)
            eatGrowth();
        else if(v[0].x == poison.x && v[0].y -1 == poison.y)
            eatPoison();
        else if((v[0].x==gate1.x&&v[0].y-1==gate1.y)||(v[0].x==gate2.x&&v[0].y-1==gate2.y))
            Gate(1);
        else {
            for(int i = len; i >= 1; i--){
                v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].x = v[1].x; v[0].y = v[1].y - 1;   
        }
        
    }   
    if(dir == 'a'){ // 왼쪽
        if(v[0].x -1 == growth.x && v[0].y == growth.y)
            eatGrowth();
        else if(v[0].x -1== poison.x && v[0].y == poison.y)
            eatPoison();
        else if((v[0].x-1==gate1.x&&v[0].y==gate1.y)||(v[0].x-1==gate2.x&&v[0].y==gate2.y))
            Gate(2);

        else {
            for(int i = len; i >= 1; i--){
                v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].x = v[1].x - 1; v[0].y = v[1].y;
        }
    }
   if(dir == 's'){ // 아래쪽
       if(v[0].x == growth.x && v[0].y + 1 == growth.y)
            eatGrowth();
        else if(v[0].x == poison.x && v[0].y + 1 == poison.y)
            eatPoison();
        else if((v[0].x==gate1.x&&v[0].y+1==gate1.y)||(v[0].x==gate2.x&&v[0].y+1==gate2.y))
            Gate(3);
        else {
            for(int i = len; i >= 1; i--){
                v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].x = v[1].x; v[0].y = v[1].y + 1;
        }
    }
    if(dir == 'd'){ // 오른쪽  
        if(v[0].x + 1 == growth.x && v[0].y == growth.y)
            eatGrowth();
        else if(v[0].x + 1== poison.x && v[0].y == poison.y)
            eatPoison();
        else if((v[0].x+1==gate1.x&&v[0].y==gate1.y)||(v[0].x+1==gate2.x&&v[0].y==gate2.y))
            Gate(4);
        else {
            for(int i = len; i >= 1; i--){
                v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].x = v[1].x + 1; v[0].y = v[1].y;
        }
    }

   // snake
    wattron(mapWin, COLOR_PAIR(BODY));
    for(int i = 1; i < len; i++)
        mvwprintw(mapWin, v[i].y, v[i].x, " ");
    wattroff(mapWin, COLOR_PAIR(BODY));

    wattron(mapWin, COLOR_PAIR(HEAD));
    mvwprintw(mapWin, v[0].y, v[0].x, " ");
    wattroff(mapWin, COLOR_PAIR(HEAD));
    wrefresh(mapWin);
    
    // 벽 통과 시 종료처리
    if (MAP[v[0].y][v[0].x] == 1){
        game=false;
        success=false;
        reason=3;

    }

    
}

void Snake::createPoison(){
    int x,y;
    bool continuePlay = true;
    
    Time = time(NULL);
    mvwprintw(mapWin, poison.y, poison.x, " ");
    
    while(continuePlay){
        continuePlay = false;
        
        // wall에 생기는 것 방지
        x = rand()%38 + 1;
        y = rand()%20 + 1;
        if ((MAP[y][x] == 1)||(MAP[y][x] == 2)) {
        	continuePlay=true;
        	continue;}
        // snake과 겹치는지 확인
        for(int i = 0; i < len; i++){
            if(v[i].x == x && v[i].y == y){
                continuePlay = true;
                break;
            }
        }

        // growth 겹치는지 확인
        if(growth.x == x && growth.y == y)
            continuePlay = true;
    }
    
    poison.x = x; poison.y = y;
    isPoison = true;

    wattron(mapWin, COLOR_PAIR(POISON));
    mvwprintw(mapWin, y, x, " ");
    wattroff(mapWin, COLOR_PAIR(POISON));
    wrefresh(mapWin);
}


void Snake::eatPoison(){
	std::cout<<'\a'<<std::flush;
    cordinate* temp = new cordinate[len];
    for(int i = 0; i < len; i++){
        temp[i].x = v[i].x; temp[i].y = v[i].y;
    }

    score[2]=score[2]+1;
    
    
    if(len-1 < 3){
      game=false;
      success=false;
      reason=1;
    }
    len--;
    delete[] v;
    v = new cordinate[len];
    v[0].x = poison.x; v[0].y = poison.y;
    
    for(int i = 1; i < len; i++){
        v[i].x = temp[i-1].x; v[i].y = temp[i-1].y;
    }

    isPoison = false;
    
    createGate();
}


void Snake::createGrowth(){
    int x,y;
    bool continuePlay = true;
    
    Time = time(NULL); 
    mvwprintw(mapWin, growth.y, growth.x, " ");
    
    while(continuePlay){
        continuePlay = false;
        
        // wall에 생기는 것 방지  
        x = rand()%38 + 1;
        y = rand()%20 + 1;
        if ((MAP[y][x] == 1)||(MAP[y][x] == 2)) {
        	continuePlay=true;
        	continue;}
        // snake과 겹치는지 확인
        for(int i = 0; i < len; i++){
            if(v[i].x == x && v[i].y == y){
                continuePlay = true;
                break;
            }
        }

        // poison과 겹치는지 확인
        if(poison.x == x && poison.y == y)
            continuePlay = true;
    }
    
    growth.x = x; growth.y = y;
    isGrowth = true;

    wattron(mapWin, COLOR_PAIR(GROWTH));
    mvwprintw(mapWin, growth.y, growth.x, " ");
    wattroff(mapWin, COLOR_PAIR(GROWTH));
    wrefresh(mapWin);
}

void Snake::eatGrowth(){
    cordinate* temp = new cordinate[len];
    for(int i = 0; i < len; i++){
        temp[i].x = v[i].x; temp[i].y = v[i].y;
    }

    len++;
    score[1]+=1;
    if (score[0]<len) score[0]=len;
    delete[] v;
    v = new cordinate[len];
    
    for(int i = 1; i < len; i++){
        v[i].x = temp[i-1].x; v[i].y = temp[i-1].y;
    }
    v[0].x = growth.x; v[0].y = growth.y;


    isGrowth = false;
    createGate();
}

void Snake::createGate(){
    Time = time(NULL);
    mvwprintw(mapWin, gate1.y, gate1.x, " ");
    mvwprintw(mapWin, gate2.y, gate2.x, " ");


    
    if(mapMode[count]==1){
        gate1.x = 0; gate1.y = 19;
        gate2.x=39; gate2.y=5;
        isGate = true;
    }
    
    else if(mapMode[count]==2){
        gate1.x = 6; gate1.y = 6;
        gate2.x=0; gate2.y=19;
        isGate = true;
    }

    else if(mapMode[count]==3){
        gate1.x = 13; gate1.y = 11;
        gate2.x=0; gate2.y=5;
        isGate = true;
    }

    else if(mapMode[count]==4){
        gate1.x = 17; gate1.y = 11;
        gate2.x=8; gate2.y=8;
        isGate = true;
    }

    wattron(mapWin, COLOR_PAIR(GATE));
    mvwprintw(mapWin, gate1.y, gate1.x, " ");
    mvwprintw(mapWin, gate2.y, gate2.x, " ");
    wattroff(mapWin, COLOR_PAIR(GATE));
    wrefresh(mapWin);
        //}
}

// Growth와 Poison 출현 후 일정시간이 지나면 사라지고 다른 위치에 나타내기 위함  
void Snake::newCreate(){
    int end = time(NULL);
    if(end - Time >= 5) {
        createPoison();
        createGrowth();
        
    }

}



void Snake::passing_Gate(int option,int gate_x,int gate_y){
	score[3]+=1;
    if(option==1){  //오른쪽으로 진행
        //printf("a");
        wattron(mapWin, COLOR_PAIR(EMPTY));
        mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
        wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
        }
        v[0].x=gate_x+1;
        v[0].y=gate_y;
        //printf("(%d, %d)\n",v[0].x,v[0].y);

        wattron(mapWin, COLOR_PAIR(BODY));
        for(int i = 1; i < len; i++)
            mvwprintw(mapWin, v[i].y, v[i].x, " ");
        wattroff(mapWin, COLOR_PAIR(BODY));

        wattron(mapWin, COLOR_PAIR(HEAD));
        mvwprintw(mapWin, v[0].y, v[0].x, " ");
        wattroff(mapWin, COLOR_PAIR(HEAD));
        wrefresh(mapWin);
        
        for(int k=1;k<len;k++){
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        
            
            for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].x=v[0].x+1;
            
            wattron(mapWin, COLOR_PAIR(BODY));
            for(int i = 1; i < len; i++)
                mvwprintw(mapWin, v[i].y, v[i].x, " ");
            wattroff(mapWin, COLOR_PAIR(BODY));

            wattron(mapWin, COLOR_PAIR(HEAD));
            mvwprintw(mapWin, v[0].y, v[0].x, " ");
            wattroff(mapWin, COLOR_PAIR(HEAD));
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, gate_y, gate_x+1, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
            wrefresh(mapWin);
            


        }
    

    
    }
    else if(option==2){ //왼쪽으로 진행
        
        
        wattron(mapWin, COLOR_PAIR(EMPTY));
        mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
        wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
        }
        v[0].x=gate_x-1;
        v[0].y=gate_y;


        wattron(mapWin, COLOR_PAIR(BODY));
        for(int i = 1; i < len; i++)
            mvwprintw(mapWin, v[i].y, v[i].x, " ");
        wattroff(mapWin, COLOR_PAIR(BODY));

        wattron(mapWin, COLOR_PAIR(HEAD));
        mvwprintw(mapWin, v[0].y, v[0].x, " ");
        wattroff(mapWin, COLOR_PAIR(HEAD));
        wrefresh(mapWin);
        
        for(int k=1;k<len;k++){
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        
            
            for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].x=v[0].x-1;
            wattron(mapWin, COLOR_PAIR(BODY));
            for(int i = 1; i < len; i++)
                mvwprintw(mapWin, v[i].y, v[i].x, " ");
            wattroff(mapWin, COLOR_PAIR(BODY));

            wattron(mapWin, COLOR_PAIR(HEAD));
            mvwprintw(mapWin, v[0].y, v[0].x, " ");
            wattroff(mapWin, COLOR_PAIR(HEAD));
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, gate_y, gate_x-1, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
            wrefresh(mapWin);
            


        }

    }

    else if(option==3){ //위로 진행
        
        
        wattron(mapWin, COLOR_PAIR(EMPTY));
        mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
        wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        
        for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
           }
        v[0].x=gate_x;
        v[0].y=gate_y-1;

        wattron(mapWin, COLOR_PAIR(BODY));
        for(int i = 1; i < len; i++)
            mvwprintw(mapWin, v[i].y, v[i].x, " ");
        wattroff(mapWin, COLOR_PAIR(BODY));

        wattron(mapWin, COLOR_PAIR(HEAD));
        mvwprintw(mapWin, v[0].y, v[0].x, " ");
        wattroff(mapWin, COLOR_PAIR(HEAD));
        wrefresh(mapWin);
    
        
        for(int k=1;k<len;k++){
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        
            for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].y-=1;
            
            
            wattron(mapWin, COLOR_PAIR(BODY));
            wattroff(mapWin, COLOR_PAIR(BODY));

            wattron(mapWin, COLOR_PAIR(HEAD));
            mvwprintw(mapWin, v[0].y, v[0].x, " ");
            wattroff(mapWin, COLOR_PAIR(HEAD));
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, gate_y-1, gate_x, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
            
            wrefresh(mapWin);
            
        }
    }

    else if(option==4){ //아래로 진행
        
        wattron(mapWin, COLOR_PAIR(EMPTY));
        mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
        wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
        }
        v[0].x=gate_x;
        v[0].y=gate_y+1;


        wattron(mapWin, COLOR_PAIR(BODY));
        for(int i = 1; i < len; i++)
            mvwprintw(mapWin, v[i].y, v[i].x, " ");
        wattroff(mapWin, COLOR_PAIR(BODY));

        wattron(mapWin, COLOR_PAIR(HEAD));
        mvwprintw(mapWin, v[0].y, v[0].x, " ");
        wattroff(mapWin, COLOR_PAIR(HEAD));
        wrefresh(mapWin);
        
        for(int k=1;k<len;k++){
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, v[len-1].y, v[len-1].x, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
        
        
            
            for(int i = len-1; i >= 1; i--){
               v[i].x = v[i-1].x; v[i].y = v[i-1].y;
            }
            v[0].y+=1;
            wattron(mapWin, COLOR_PAIR(BODY));
            for(int i = 1; i < len; i++)
                mvwprintw(mapWin, v[i].y, v[i].x, " ");
            wattroff(mapWin, COLOR_PAIR(BODY));

            wattron(mapWin, COLOR_PAIR(HEAD));
            mvwprintw(mapWin, v[0].y, v[0].x, " ");
            wattroff(mapWin, COLOR_PAIR(HEAD));
            wattron(mapWin, COLOR_PAIR(EMPTY));
            mvwprintw(mapWin, gate_y+1, gate_x, " ");
            wattroff(mapWin,COLOR_PAIR(EMPTY));
            
            wrefresh(mapWin);
            


        }
    }
    

}


void Snake::Gate(int option){
  //중간에 위치한 gate처리
    int a=v[0].x;
    int b=v[0].y;

    if(option==1) b-=1;
    else if(option==2) a-=1;
    else if(option==3) b+=1; //위에서 아래로 진행
    else if(option==4) a+=1;

    if(a==gate1.x&&b==gate1.y) {
        if(gate2.x==39){ //option:1 오
            dir='a';
            tmp=dir;
            
            passing_Gate(2,gate2.x,gate2.y);
        }
        else if(gate2.x==0){ //option:2 왼
            dir='d';
            tmp='d';
            passing_Gate(1,gate2.x,gate2.y);
        }
        else if(gate2.y==0){ //option:3 위
            dir='s';
            tmp=dir;
            passing_Gate(4,gate2.x,gate2.y);
        }
        
        else if(gate2.y==21){//option:4 아
            dir='w';
            tmp=dir;
            passing_Gate(3,gate2.x,gate2.y);
        }

        else if(option==1){  //위
            if(MAP[gate2.y-1][gate2.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y][gate2.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y][gate2.x-1]==0) {
                dir='a';
                tmp=dir;
            
                passing_Gate(2,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y+1][gate2.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate2.x,gate2.y);
            }
        }
        else if(option==2){ //왼
            if(MAP[gate2.y][gate2.x-1]==0) {
                dir='a';
                tmp=dir;
            
                passing_Gate(2,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y-1][gate2.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y+1][gate2.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y][gate2.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate2.x,gate2.y);
            }            
                //else exit(1);
        }

        else if(option==3){ // 아래쪽로 들어감

            if(MAP[gate2.y+1][gate2.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y][gate2.x-1]==0) {
                dir='a';
                tmp=dir;
            
                passing_Gate(2,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y][gate2.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y-1][gate2.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate2.x,gate2.y);
            }
        }



        else if(option==4){ // 오른쪽  
            if(MAP[gate2.y][gate2.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y-1][gate2.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y+1][gate2.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate2.x,gate2.y);
            }
            else if(MAP[gate2.y][gate2.x-1]==0)  {
                dir='a';
                tmp=dir;
            
                passing_Gate(2,gate2.x,gate2.y);
            }
            //else exit(1);

        }



    }

    if(a==gate2.x&&b==gate2.y){

        if(gate1.x==39){ //option:1 오
            dir='a';
            tmp=dir;
            
            passing_Gate(2,gate1.x,gate1.y);
            
        }
        else if(gate1.x==0){ //option:2 왼
            dir='d';
            tmp=dir;
            
            passing_Gate(1,gate1.x,gate1.y);
            
        }
        else if(gate1.y==0){ //option:3 위
            dir='s';
            tmp=dir;
            passing_Gate(4,gate1.x,gate1.y);
            
        }
            
        else if(gate1.y==21){//option:4 아
            dir='w';
            tmp=dir;
            passing_Gate(3,gate1.x,gate1.y);
            
        }


    //중간에 위치한 gate처리
     
        else if(option==1){  //위
            if(MAP[gate1.y-1][gate1.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate1.x,gate1.y);
            }
            else if(MAP[gate1.y][gate1.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate1.x,gate1.y);
            }
            else if(MAP[gate1.y][gate1.x-1]==0) {
                dir='a';
                tmp=dir;
                passing_Gate(2,gate1.x,gate1.y);
            }
            else if(MAP[gate1.y+1][gate1.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate1.x,gate1.y);
            }
          //else exit(1);
        }
        else if(option==2){ //왼
            if(MAP[gate1.y][gate1.x-1]==0) {
                dir='a';
                tmp=dir;
                passing_Gate(2,gate1.x,gate1.y);
            }
                
            else if(MAP[gate1.y-1][gate1.x]==0) {
                
                dir='w';
                tmp=dir;
                passing_Gate(3,gate1.x,gate1.y);
            }
            else if(MAP[gate1.y+1][gate1.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate1.x,gate1.y);
                
            }

            else if(MAP[gate1.y][gate1.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate1.x,gate1.y);
                
            }
          //else exit(1);
        }

        else if(option==3){ // 아래쪽
            if(MAP[gate1.y+1][gate1.x]==0) {
                dir='s';
                tmp=dir;
                passing_Gate(4,gate1.x,gate1.y);
                
            }
            else if(MAP[gate2.y][gate1.x-1]==0) {
                dir='a';
                tmp=dir;
                passing_Gate(2,gate1.x,gate1.y);
                
            }
            else if(MAP[gate1.y][gate1.x+1]==0) {
                dir='d';
                tmp=dir;
                passing_Gate(1,gate1.x,gate1.y);
                
            }
            else if(MAP[gate1.y-1][gate1.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate1.x,gate1.y);

            }
          //else exit(1);
        }



        else if(option==4){ // 오른쪽  
            if(MAP[gate1.y][gate1.x+1]==0) {
                passing_Gate(1,gate2.x,gate2.y);
                dir='d';}
            else if(MAP[gate1.y+1][gate1.x]==0) {
                passing_Gate(4,gate2.x,gate2.y);
                dir='s';}
            else if(MAP[gate1.y-1][gate1.x]==0) {
                dir='w';
                tmp=dir;
                passing_Gate(3,gate2.x,gate2.y);
            }
            else if(MAP[gate1.y][gate1.x-1]==0) {
                dir='a';
                tmp=dir;
                passing_Gate(2,gate2.x,gate2.y);
                 

            }
                //else exit(1);

        }     
    }

  
  isGate=false;

}


void Snake::setMap(int set_count){
    
    ifstream in((string)MAPS + to_string(mapMode[set_count]) + ".txt");
    
    for (int i = 0; i < NLINE; i++) {
        for (int j = 0; j < NCOL; j++) {
            in >> MAP[i][j]; }
    }
}


void Snake::check(){
	if (score[0]>=7) mission[0]=true;
	if (score[1]>=5) mission[1]=true;
	if (score[2]>=2) mission[2]=true;
	else if (score[2]<2) mission[2]=false;

	if (score[3]>=3) mission[3]=true;
	int map_count=0;
	for(int i=0;i<4;i++) {
		if (mission[i]) map_count+=1;
	}
	if (map_count>=2){
		
		success=true;
		game=false;
		setMission();
	}
	

}

void Snake::play(){
    timeout(200);
    int key;
   
    while((key=getch())) {
    	setScore();
    	setMission();
        setStage();

        newCreate();
        isGate=false;
        
        if((key=='a'&&tmp=='d')||(key=='d'&&tmp=='a')||(key=='w'&&tmp=='s')||(key=='s'&&tmp=='w')) {
        	game=false;
        	success=false;
            reason=2;
        }
        if(key == 'a' || key == 'w' || key == 'd' || key == 's'){
            moveSnake(key);
            tmp=key;
        } 
        else {
            moveSnake();
        }

        
        check();
        if(game==false) {
        	if (success==false) {
        		midScene();
                
                
        		if(continued==false) {
                    completeScene();
                    exit(1);
        		}

                init(count);
                setDefault();
        		continue;
        	}
            if(count==3){
                completeScene();
                exit(1);
            } 
        	successScene();

            if(continued==false) {
                completeScene();
                exit(1);
            }
            
            count++;
            
            init(count);
            setDefault();
            
            
           
        }
        // 커서 삭제
        curs_set(0);
    }  
        if(isPoison == false)
            createPoison();
        if(isGrowth == false)
            createGrowth();

        
}



