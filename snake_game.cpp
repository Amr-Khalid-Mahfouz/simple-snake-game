// the code is for training purposes only.
// credit mostly to NVitanovic

#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

bool game_over;

string good_game = "GOOD GAME";

// map size:
int width = 40;
int height = 20;

static int x, y, fruit_x, fruit_y;
int score;
int speed = 260;

int tail_x[50], tail_y[50];
int tail_length = 0;

enum direction {stop = 0, LEFT, RIGHT, up, down, quit};
direction Dir;

void setup(){
    game_over = false;
    Dir = stop;
    x = width / 2;
    y = height / 2;
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    score = 0;
}

void draw(){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});

    CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    
    for(int i = 0 ; i < width + 2; i++){
        cout << '#';
    }
    cout << '\n';
    
    for(int i = 0 ; i < height+2; i++){
        for(int j = 0 ; j < width + 2; j++){
            
            if(j == 0 || j == width){cout << '#';}
            if (i == y && j == x) {cout << 'O';}
            else if(j == fruit_x && i == fruit_y){cout << '*';}
            else {
                bool printed = false;
                for(int x  = 0 ; x < tail_length + 1; x++){
                    if(tail_x[x] == j && tail_y[x] == i){
                        cout << 'o';
                        printed  = true;}
                }
                if(!printed){cout << ' ';}
                }
            }
            cout << '\n';}
        
    for(int i = 0 ; i < width + 2; i++)    {cout << '#';}

    cout << '\n';
    cout << "score : " << score ;
}

void input(){

    if(_kbhit()){
        switch (_getch()){
        case 'a':
            Dir = LEFT;  
            break;
        case 'w':
            Dir = up;  
            break;
        case 's':
            Dir = down;  
            break;
        case 'd':
            Dir = RIGHT;      
            break;
        case 'q':
            Dir = quit;
            system("cls");
            cout << "final score : " << score << endl; 
            for(char i : good_game){cout << i; _sleep(400);}
            break;}
    }
}

void logic(){
        
        switch (Dir){
        case up:
            y -= 1;  
            break;
        case down:
            y += 1;  
            break;
        case LEFT:
            x -= 1;  
            break;
        case RIGHT:
            x += 1;      
            break;
        case quit:

            exit(0);
            break;}        

    for(int i = 0 ; i < tail_length ; i++){
        if(tail_x[i] == x && tail_y[i] == y)    {game_over = true;}} 

    if(x == -1)  {x = width - 1;}
    else if(x == width)    {x = 1;}

    if(y == -1)  {y = height;}
    else if(y == height + 2)    {y = 0;}

    if(x == fruit_x && y == fruit_y){
        if(tail_length < 49)    tail_length ++;
        score ++;
        if(speed >= 80) {speed = speed - 20;}
        fruit_x = rand() % width;
        fruit_y = rand() % height;}

    tail_x[0] = x;  tail_y[0] = y;
    int prevX = tail_x[0];
    int prevY = tail_y[0];
    int prev2X, prev2Y;

    for(int l = 1 ; l <= tail_length ; l++){
        prev2X = tail_x[l];
        prev2Y = tail_y[l];
        tail_x[l] = prevX;
        tail_y[l] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
}

int main(){
    system("cls");
    srand(time(NULL));    
    setup();
    while(!game_over){
        draw();
        input();
        logic();
        _sleep(speed);
        }
        system("cls");
        cout << "final score : " << score << endl; 
        for(char i : good_game){cout << i; _sleep(300);}
    return 0;
}
