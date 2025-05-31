#include "../../BoardGame_Classes.h"
using namespace std;

template <typename T>
class PyramidAi : public Player<T>
{
public:
    PyramidAi(T symbol);

    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    pair<int, int> getBestMove();
};

// ======================== //
template <typename T>
PyramidAi<T>::PyramidAi(T symbol) : Player<T>(symbol)
{
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void PyramidAi<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
pair<int, int> PyramidAi<T>::getBestMove()
{
    // cout << "i am called\n";
    pair<int, int> bestMove = {-1, -1};
    T opSymbol = this->symbol == 'X' ? 'O' : 'X';
    // cout << "checking if win \n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (this->boardPtr->update_board(i, j, this->symbol))
            {
                if (this->boardPtr->is_win())
                {
                    // cout << "iam winning\n";
                    this->boardPtr->update_board(i, j, ' ');
                    return {i, j};
                }
                this->boardPtr->update_board(i, j, ' ');
                // this->boardPtr->display_board();
                // cout << "\n";
            }
        }
    }
    // cout << "checking if block lose \n";
    // cout << "Iam not winning\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (this->boardPtr->update_board(i, j, opSymbol))
            {
                if (this->boardPtr->is_win())
                {
                    this->boardPtr->update_board(i, j, ' ');
                    return {i, j};
                }
                this->boardPtr->update_board(i, j, ' ');
            }
        }
    }
    // return bestMove;
    // cout << "check what is the best move \n";
    int bestValue = -100;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (this->boardPtr->update_board(i, j, this->symbol))
            {
                int value = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, ' ');
                if (value > bestValue)
                {
                    bestValue = value;
                    bestMove = {i, j};
                }
            }
        }
    }

    return bestMove;
}

template <typename T>
int PyramidAi<T>::calculateMinMax(T symbol, bool isMaximizing)
{
    if (this->boardPtr->is_win())
    {
        return isMaximizing ? 1 : -1;
    }
    else if (this->boardPtr->is_draw())
    {
        return 0;
    }

    int bestValue = isMaximizing ? -100 : 100;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (this->boardPtr->update_board(i, j, symbol))
            {
                int value = calculateMinMax(symbol = 'X' ? 'O' : 'X', !isMaximizing);
                this->boardPtr->update_board(i, j, ' ');
                if (isMaximizing)
                {
                    bestValue = value > bestValue ? value : bestValue;
                }
                else
                {
                    bestValue = value < bestValue ? value : bestValue;
                }
            }
        }
    }

    return bestValue;
}