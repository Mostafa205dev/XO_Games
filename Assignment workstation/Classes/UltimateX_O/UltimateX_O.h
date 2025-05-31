#ifndef ULTIMATEX_O_H
#define ULTIMATEX_O_H

#pragma once
template <typename T>
class UltimateX_OBoard : public Board<T>
{
private:
    bool isLogical(int r, int c)
    {
        return (r >= 0 && r < 9 && c >= 0 && c < 9);
    };
    UltimateX_OBoard *boards[9];
    bool isMain;

public:
    UltimateX_OBoard() {};
    UltimateX_OBoard(bool main);
    ~UltimateX_OBoard()
    {
        if (isMain)
        {
            delete[] this->boards;
        }
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
class UltimateX_OPlayer : public Player<T>
{
public:
    UltimateX_OPlayer() {};
    UltimateX_OPlayer(string name, T symbol);

    void getmove(int &x, int &y);
};

template <typename T>
class UltimateX_ORandPlayer : public RandomPlayer<T>
{
private:
    int columns;
    int rows;

public:
    UltimateX_ORandPlayer() {};
    UltimateX_ORandPlayer(T symbol);

    void getmove(int &x, int &y);
};

#endif