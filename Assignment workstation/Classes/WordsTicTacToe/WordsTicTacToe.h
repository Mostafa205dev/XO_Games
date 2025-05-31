#ifndef WORDSTICTACTOE_H
#define WORDSTICTACTOE_H

#include "../../BoardGame_Classes.h"
// #include <vector>
#include <unordered_set>
#pragma once

template <typename T>
class WordsBoard : public Board<T>
{
private:
    // vector<string> words;
    std::unordered_set<string> words;
    bool isLogical(int r, int c);
    bool isWord(char one, char two, char three);

public:
    WordsBoard();
    ~WordsBoard()
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
class WordsPlayer : public Player<T>
{
public:
    WordsPlayer() {};
    WordsPlayer(string name, T symbol);

    void getmove(int &x, int &y);
};

template <typename T>
class WordsRandPlayer : public RandomPlayer<T>
{
private:
public:
    WordsRandPlayer() {};
    WordsRandPlayer(T symbol);

    void getmove(int &x, int &y);
};

#endif