#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

class Snake {
public:
    vector<pair<int, int>> body;
    char direction;
    bool alive;

    Snake(int startX, int startY) {
        body.push_back(make_pair(startX, startY));
        direction = ' ';
        alive = true;
    }

    void move() {
        pair<int, int> head = body.front();
        switch (direction) {
            case 'U': head.first--; break;
            case 'D': head.first++; break;
            case 'L': head.second--; break;
            case 'R': head.second++; break;
        }
        body.insert(body.begin(), head);
        body.pop_back();
    }

    void grow() {
        pair<int, int> tail = body.back();
        body.push_back(tail);
    }

    void setDirection(char newDirection) {
        direction = newDirection;
    }

    void draw() {
        for (auto segment : body) {
            gotoxy(segment.second, segment.first);
            cout << "O";
        }
    }

    void clear() {
        for (auto segment : body) {
            gotoxy(segment.second, segment.first);
            cout << " ";
        }
    }

private:
    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};

class Game {
public:
    Snake snake;
    int width, height;

    Game(int w, int h) : snake(Snake(w / 2, h / 2)), width(w), height(h) {}

    void run() {
        while (snake.alive) {
            if (_kbhit()) {
                char newDirection = _getch();
                snake.setDirection(newDirection);
            }
            snake.clear();
            snake.move();
            snake.draw();
            Sleep(100);
        }
    }
};