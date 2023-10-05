#include <iostream>
using namespace std;

bool isGameOver;
const int width = 20;
const int height = 20;
int dwidth = width*2; // to draw properly depending on the terminal configuration
int dheight = height;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup() {
    isGameOver = false;
    dir = STOP;
    x = int(width/2);
    y = int(height/2);
    fruitX = rand() % width; // we use module to set "max" bound
    fruitY = rand() % height;
    score = 0;
}

void draw() {
    system("cls"); //system("clear") for linux
    
    // top wall
    for (int i = 0; i < dwidth; i++) { 
        cout << "#";
    }
    cout << '\n'; // or should I use endl?
    
    // side walls and map
    for (int i = 0; i < dheight; i++) {
        for (int j = 0; j < dwidth; j++) {
            if (j == 0 || j == dwidth-1) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << '\n';
    }

    // bottom wall
    for (int i = 0; i < dwidth; i++) { 
        cout << "#";
    }
    cout << '\n';
}

void input() {

}

void logic() {

}

int main() {
    while (!isGameOver) {
        draw();
        input();
        logic();
    }
    return 0;
}