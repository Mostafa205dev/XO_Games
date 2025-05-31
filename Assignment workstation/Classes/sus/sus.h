#ifndef SUS_H
#define SUS_H

#include "../../BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cctype> // for toupper()

template <typename T>
class Sus_Board : public Board<T>
{
private:
    bool lastplayer = true;
    int counterp1 = 0;
    int counterp2 = 0;

public:
    string name1 = "", name2 = "";
    Sus_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Sus_Player : public Player<T>
{
private:
public:
    Sus_Player(std::string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Sus_Random_Player : public RandomPlayer<T>
{
private:
public:
    Sus_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

#endif // SUS_H
