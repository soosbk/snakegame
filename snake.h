#ifndef Snake_h
#define Snake_h
#include<string>
#include <ncurses.h>
#include <map>
#include<fstream>
#include <string.h>
#include<cstring>
using namespace std;

const int NCOL = 40, NLINE = 22;  

struct cordinate{
    int x;
    int y;
};

class Snake{

public:
    Snake();
    void init(int count=0); //@author 이성주(20163144)
    void startm(); //@author 김수빈(20192218)


    void colorInit(); //@author 이성주(20163144)
    void setDefault(); //@author 김수빈(20192218)
    
    void moveSnake(char key = 'n'); //@author 이성주(20163144)
    
    void createScore(); //김수빈(20192218)
    void setScore(); //김수빈(20192218)

    void createMission(); //@author 김수빈(20192218)
    void setMission(); //@author 김수빈(20192218)
 
    void setStage(); //@author 김수빈(20192218)

    void setMap(int count); //@author 김수빈(20192218)
    void createMap(); //@author 이성주(20163144)
    void createGrowth(); //@author 이성주(20163144)
    void createPoison(); //@author 이성주(20163144)

    void newCreate(); //@author 이성주(20163144)
    void eatGrowth(); //@author 이성주(20163144)
    void eatPoison(); //@author 이성주(20163144)
    
    void createGate(); //@author 김수빈(20192218)
    void Gatecheck(); //@author 김수빈(20192218)
    void passing_Gate(int option,int gate_x,int gate_y); //@author 김수빈(20192218)
 
    void Gate(int option); //@author 김수빈(20192218)


    

    void midScene();//@author 김수빈(20192218)
    void successScene();//@author 김수빈(20192218)
    void completeScene();//@author 김수빈(20192218)
    void scoreScene(int scene_option); //@author 김수빈(20192218)

    void count_max(int count_option); //@author 김수빈(20192218)

    void check(); //@author 김수빈(20192218)
    void play(); //@author 이성주(20163144)

private:
    int len = 3;
    int count=0;
    int starttime;
    int Time;
    char dir;
    int score[4]={3,0x00,0x00,0x00};  //max body,growth, poision, gate
    bool mission[4]={false,false, false, false};
    int mapMode_save[24][4]={{1,2,3,4},{1,2,4,3},{1,3,2,4},{1,3,4,2},{1,4,2,3},{1,4,3,2},
    {2,1,3,4},{2,1,4,3},{2,3,1,4},{2,3,4,1},{2,4,3,1},{2,4,1,3},
    {3,1,2,4},{3,1,4,2},{3,2,1,4},{3,2,4,1},{3,4,1,2},{3,4,2,1},
    {4,1,2,3},{4,1,3,2},{4,2,3,1},{4,2,1,3},{4,3,1,2},{4,3,2,1}};
    int mapMode[4]={0,0,0,0};
    //died, maxbody, growth, poison, gate;
    int score_save[4][5]={{0x00,},}; 
    int total_num[5]={0x00,};
    int reason=0;
    cordinate* v = new cordinate[3];
    
    cordinate growth;
    cordinate poison;


    cordinate gate1;
    cordinate gate2;

    bool isGrowth; 
    bool isPoison; 
    bool isGate; 
    bool game=true;
    bool success=false;

    bool random=false;
    bool continued=true;

    WINDOW *startWin;
    WINDOW *mapWin;
};

#endif

