#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
//define functions
bool gameOver;
const int height = 20, width = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
enum Edirection {STOP=0, UP, DOWN, RIGHT, LEFT};
Edirection dir;


//define functions
void setUp() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}
void Draw() {
    system("cls");
    //print top wall
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    //print rest of map
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width ; j++) {
            if (j == 0 )
                cout << "#";    
            //print head
            if (i == y && j == x)
                cout << "O";
            else if (j== fruitX && i== fruitY)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if(!print)
                cout << " ";
            }
               
            if (j == width - 1)
                cout << "#";
         
        }
        cout << endl;
    }
    //print bottom wall
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input() {
    if (_kbhit())
    {
        switch (_getch()) {
        case 'w': dir = UP;
            break;  
        case 'a': dir = LEFT;
            break;
        case 's': dir = DOWN;
            break;
        case 'd': dir = RIGHT;
            break;
        case 'p': gameOver = true;
            break;  
        }
    }
}
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX; 
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    case LEFT:
        x --;
        break;
    default:
        break;
    }

    /*if (x < 0 || x > height || y < 0 || y > width)
        gameOver = true;*/
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if(y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i=0; i< nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        nTail++;
        score++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}


int main()
{
    
    setUp();
    while (!gameOver) {
        Draw();
        if (dir == LEFT || dir == RIGHT)
        {
            Sleep(20);
        }
        Sleep(10);
        if (dir == UP || dir == DOWN)
        {
            Sleep(60);
        }
        Input();
        Logic();
        
    }

}

