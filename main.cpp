#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool isGameOver;
bool debugMode;
enum gameModes {CLASSIC, CLASSIC_SPEEDUP, NOWALLS, NOWALLS_INVINCIBLE};
gameModes gamemode;
const int playableWidth = 30;
const int playableHeight = 15;
const int width = playableWidth + 2;
const int height = playableHeight - 2;
int x, y, fruitX, fruitY, score;
int tailX[playableWidth*height], tailY[playableWidth*height];
int tailL;
int sleepTime;
enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void place_apple() {
    fruitX = 1 + rand() % playableWidth;
    fruitY = rand() % height;
    if (fruitX == x && fruitY == y)
        place_apple();
    if (fruitX < 1 || fruitX > playableWidth || fruitY < 0 || fruitX > playableHeight)
        place_apple();
    for (int i = 0; i < tailL; i++) {
        if (fruitX == tailX[i] && fruitY == tailY[i])
            place_apple();
            break;
    }
}

void setup() {
    cout << "0. classic \n1. classic_speedup \n2. nowalls \n3. nowalls_invincible \nSelect a game mode: ";
    int selectedGM;
    cin >> selectedGM;
    system("cls");
    switch (selectedGM) {
    case 0:
        gamemode = CLASSIC;
        break;
    case 1:
        gamemode = CLASSIC_SPEEDUP;
        break;
    case 2:
        gamemode = NOWALLS;
        break;
    case 3:
        gamemode = NOWALLS_INVINCIBLE;
        break;
    default:
        gamemode = CLASSIC;
        break;
    }

    debugMode = false;
    isGameOver = false;
    dir = STOP;
    score = 0;
    sleepTime = 70;

    // initial head position
    x = int(width/2);
    y = int(height/2);

    // placing an apple
    place_apple();
}

void draw() {
    // system("cls"); // system("clear") for linux
    printf("\x1b[H");
    
    // top wall
    for (int i = 0; i < width; i++) { 
        cout << '#';
    }
    cout << '\n';
    
    // side walls and map
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (j == 0 || j == width-1)
                cout << '#';
            else if (i == y && j == x)
                cout << 'O';
            else if (i == fruitY && j == fruitX)
                cout << 'a';
            else {
                bool print = false;
                for (int k = 0; k < tailL; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << 'o';
                        print = true;
                        break;
                    }
                }
                if (!print)
                    cout << ' ';
            }
        }
        cout << '\n';
    }

    // bottom wall
    for (int i = 0; i < width; i++) { 
        cout << '#';
    }

    cout << '\n';
    cout << "Score: " << score << endl;
    if (debugMode) cout << "DEBUG: a:(" << fruitX << ',' << fruitY << ") O:(" << x << ',' << y << ") sleepTime:" << sleepTime
    << "\ngridSize:(" << playableWidth << 'x' << playableHeight << ") gm:" << gamemode << endl;
}

void input() {
    if (_kbhit())
    {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        case '`':
            debugMode = !debugMode;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y; // buffer
    tailX[0] = x; // move the first part on the previous head's place
    tailY[0] = y; 

    // start with 1,ּ as 0 tail part is already moved
    for (int i = 1; i < tailL; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    switch (gamemode) {
        case CLASSIC:
            if (x <= 0 || x >= width || y < 0 || y > height)
                isGameOver = true;
            break;
        case CLASSIC_SPEEDUP:
            if (x <= 0 || x >= width || y < 0 || y > height)
                isGameOver = true;
            break;
        case NOWALLS:
            if (x >= width - 1) x = 1; else if (x <= 0) x = width - 1;
            if (y >= height) y = 0; else if (y < 0) y = height - 1;
            break;
        case NOWALLS_INVINCIBLE:
            if (x >= width-1) x = 1; else if (x <= 0) x = width - 1;
            if (y >= height) y = 0; else if (y < 0) y = height - 1;
            break;
    }

    // funny way to do that, but at least it uses less code
    if (gamemode != NOWALLS_INVINCIBLE) {
        for (int i = 0; i < tailL; i++)
            if (tailX[i] == x && tailY[i] == y)
                isGameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score++;
        tailL++;
        place_apple();
        if (gamemode == CLASSIC_SPEEDUP && sleepTime > 30) sleepTime -= 2;
    }
}

void results() {
    system("cls");
    cout << "---Game Over!---" << '\n';
    cout << "Final score: " << score << '\n';
    if (debugMode) cout << "DEBUG: a:(" << fruitX << ',' << fruitY << ") O:(" << x << ',' << y << ") sleepTime:" << sleepTime
    << "\ngridSize:(" << playableWidth << 'x' << playableHeight << ") gm:" << gamemode << endl;
    system("pause");
}

int main() {
    setup();
    while (!isGameOver) {
        input();
        logic();
        draw();
        Sleep(sleepTime);
    }
    results();
    return 0;
}