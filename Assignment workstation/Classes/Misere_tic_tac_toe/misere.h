#ifndef MISERE_H
#define MISERE_H

#include "../../BoardGame_Classes.h"

#pragma once

template <typename T>
class Misere_board : public Board<T>
{
public:
    Misere_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    ~Misere_board();

private:
};

template <typename T>
class Misere_Player : public Player<T>
{
public:
    Misere_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Misere_Random_Player : public RandomPlayer<T>
{
public:
    Misere_Random_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

#endif