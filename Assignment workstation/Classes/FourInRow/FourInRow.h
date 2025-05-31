#ifndef FOURINROW_H
#define FOURINROW_H

#include "../../BoardGame_Classes.h"

#pragma once


template <typename T>
class Four_In_Row_Board : public Board<T>
{
public:
    Four_In_Row_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Four_In_Row_Player : public Player<T>
{
public:
    Four_In_Row_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Four_In_Row_Random_Player : public RandomPlayer<T>
{
public:
    Four_In_Row_Random_Player(T symbol);
    void getmove(int &x, int &y);
};






#endif