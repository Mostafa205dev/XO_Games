#ifndef PYRAMICTICTACTOE_H
#define PYRAMICTICTACTOE_H

#include "../../BoardGame_Classes.h"

#pragma once

template <typename T>
class PyramidBoard : public Board<T>
{
private:
    bool isLogical(int r, int c)
    {
        return (r >= 0 && r < 3 && c >= 0 && c < 5);
    };

public:
    PyramidBoard();
    ~PyramidBoard()
    {
        for (int i = 0; i < this->rows; i++)
        {
            delete[] this->board[i];
        }
        delete[] this->board;
    };

    bool update_board(int x, int y, T symbol);

    void display_board();

    bool is_win();

    bool is_draw();

    bool game_is_over();
};

template <typename T>
class PyramidPlayer : public Player<T>
{
public:
    PyramidPlayer() {};
    PyramidPlayer(string name, T symbol);

    void getmove(int &x, int &y);
};

template <typename T>
class PyramidRandPlayer : public RandomPlayer<T>
{
private:
    int columns;
    int rows;

public:
    PyramidRandPlayer() {};
    PyramidRandPlayer(T symbol);

    void getmove(int &x, int &y);
};

#endif