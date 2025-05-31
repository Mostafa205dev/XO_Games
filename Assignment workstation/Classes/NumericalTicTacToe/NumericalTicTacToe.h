#ifndef NumericalTicTacToe_H
#define NumericalTicTacToe_H


#include "../../BoardGame_Classes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <cctype> // for toupper()

bool isOdd=true;
vector<int> vecOdd={1,3,5,7,9};
vector<int> vecEven={2,4,6,8};



    
template <typename T>
class Numerical_Tic_Tac_Toe_Board : public Board<T>
{
public:
    Numerical_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Numerical_Tic_Tac_Toe_Player : public Player<T>
{
public:
    
    Numerical_Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class Numerical_Tic_Tac_Toe_Random_Player : public RandomPlayer<T>
{
public:
    Numerical_Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y);
};



#pragma once

































#endif