#ifndef FIVEXFIVE_H
#define FIVEXFIVE_H

#include "../../BoardGame_Classes.h"

#pragma once
bool winRev = false;
bool AIundo = false;
bool AIisX = true;
int dif1 = 0;
template <typename T>
class FiveXFive_board : public Board<T>
{
public:
    bool last = false;
    FiveXFive_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    int count_lines(T symbol);
    bool is_win();
    bool is_draw();
    bool game_is_over();
    ~FiveXFive_board();

private:
};

template <typename T>
class FiveXFive_Player : public Player<T>
{

public:
    FiveXFive_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class FiveXFive_Random_Player : public RandomPlayer<T>
{
public:
    FiveXFive_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

#endif
