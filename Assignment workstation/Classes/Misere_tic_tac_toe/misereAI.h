
#ifndef _MISEREAI_H
#define _MISEREAI_H

#include "../../BoardGame_Classes.h"

template <typename T>
class MISERE_MinMax_Player : public Player<T>
{
public:
    MISERE_MinMax_Player(string name, T symbol);

    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();
};

//--------------------------------------- IMPLEMENTATION

#include <limits>
#include <algorithm> // For max and min
using namespace std;
// Constructor for the templated class
template <typename T>
MISERE_MinMax_Player<T>::MISERE_MinMax_Player(string name, T symbol) : Player<T>(symbol)
{
    this->name = name;
}

// Method to get the best move for the player
template <typename T>
void MISERE_MinMax_Player<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int MISERE_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing)
{
    if (this->boardPtr->is_win())
    {
        return isMaximizing ? -1 : 1;
    }
    else if (this->boardPtr->is_draw())
    {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (this->boardPtr->update_board(i, j, s))
            {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing)
                {
                    bestValue = max(bestValue, value);
                }
                else
                {
                    bestValue = min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
pair<int, int> MISERE_MinMax_Player<T>::getBestMove()
{
    int bestValue = numeric_limits<int>::max();
    pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (this->boardPtr->update_board(i, j, this->symbol))
            {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue < bestValue)
                {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif