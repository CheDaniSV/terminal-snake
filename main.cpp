#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool isGameOver;
const int width = 30;
const int height = 15 - 2;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tailL;
enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void place_apple() {
    fruitX = 1 + rand() % (width-1); // [1:width-1]
    fruitY = rand() % height;
    if (fruitX == x && fruitY == y)
        place_apple();
    for (int i = 0; i < tailL; i++) {
        if (fruitX == tailX[i] && fruitY == tailY[i])
            place_apple();
            break;
    }
}

void setup() {
    isGameOver = false;
    dir = STOP;
    score = 0;

    // initial head position
    x = int(width/2);
    y = int(height/2);

    // placing an apple
    place_apple();
}

void draw() {
    system("cls"); // system("clear") for linux
    
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
            else if(i == y && j == x)
                cout << 'O';
            else if (i == fruitY && j == fruitX)
                cout << 'a';
            else {
                bool print = false;
                for (int k = 0; k < tailL; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << 'o';
                        print = true;
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
    // cout << "DEBUG: a:[" << fruitX << ',' << fruitY << "] O:[" << x << ',' << y << "]" << endl;
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
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y; // buffer
    tailX[0] = x;
    tailY[0] = y;

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

    if (x <= 0 || x >= width || y < 0 || y > height)
        isGameOver = true;
    // if (x >= width) x = 0; else if (x < 0) x = width - 1;
    // if (y >= height) y = 0; else if (y < 0) y = height - 1;
    
    for (int i = 0; i < tailL; i++)
        if (tailX[i] == x && tailY[i] == y)
            isGameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score++;
        tailL++;
        place_apple();
    }
}

void results() {
    system("cls");
    cout << "===Game Over!===" << '\n';
    cout << "Final score: " << score << endl;
}

int main() {
    setup();
    while (!isGameOver) {
        input();
        logic();
        draw();
        Sleep(70);
    }
    results();
    return 0;
}