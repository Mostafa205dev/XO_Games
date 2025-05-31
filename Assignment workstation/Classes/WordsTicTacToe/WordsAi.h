#include "../../BoardGame_Classes.h"
#include <bits/stdc++.h>
#include <cctype>
#include <algorithm>
using namespace std;

template <typename T>
class WordsAi : public Player<T>
{
public:
    WordsAi(T symbol);

    void getmove(int &x, int &y) override;

private:
    tuple<int, int, char> getBestMove();
};

// ============================= //
template <typename T>
WordsAi<T>::WordsAi(T symbol) : Player<T>(symbol)
{
    this->name = "AI Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Method to get the best move for the player
template <typename T>
void WordsAi<T>::getmove(int &x, int &y)
{
    tuple<int, int, char> bestMove = getBestMove();
    x = get<0>(bestMove);
    y = get<1>(bestMove);
    this->symbol = get<2>(bestMove);
    // [ x, y, this->symbol ] = bestMove;
}

// ========= main work ========= //
template <typename T>
tuple<int, int, char> WordsAi<T>::getBestMove()
{
    tuple<int, int, char> bestMove = {-1, -1, 'a'};

    // check if win in next
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->boardPtr->update_board(i, j, 'z'))
            {
                this->boardPtr->update_board(i, j, ' ');
                for (int k = 0; k < 26; k++)
                {
                    char letter = char(97 + k);
                    if (this->boardPtr->update_board(i, j, letter))
                    {
                        if (this->boardPtr->is_win())
                        {
                            this->boardPtr->update_board(i, j, ' ');
                            return {i, j, letter};
                        }
                        this->boardPtr->update_board(i, j, ' ');
                    }
                }
            }
        }
    }

    // if not win try not to make the opponent win
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->boardPtr->update_board(i, j, 'z'))
            {
                this->boardPtr->update_board(i, j, ' ');
                for (int k = 0; k < 26; k++) // main letter
                {
                    bool changeLetter = false;
                    // this->boardPtr->display_board();
                    char letter = char(97 + k);
                    // cout << "first letter " << letter << i << j << "\n";
                    this->boardPtr->update_board(i, j, letter);
                    for (int ii = 0; ii < 3; ii++)
                    {
                        for (int jj = 0; jj < 3; jj++)
                        {
                            if (this->boardPtr->update_board(ii, jj, 'z'))
                            {
                                this->boardPtr->update_board(ii, jj, ' ');
                                for (int kk = 0; kk < 26; kk++)
                                { // second letter
                                    char letter2 = char(97 + kk);
                                    // cout << "second letter " << letter2 << ii << jj << "\n";
                                    // this->boardPtr->display_board();
                                    if (this->boardPtr->update_board(ii, jj, letter2))
                                    {
                                        // this->boardPtr->display_board();
                                        if (this->boardPtr->is_win())
                                        {
                                            changeLetter = true;
                                            this->boardPtr->update_board(ii, jj, ' ');
                                            break;
                                        }
                                        this->boardPtr->update_board(ii, jj, ' ');
                                    }
                                }
                            }
                            if (changeLetter)
                                break;
                        }
                        if (changeLetter)
                            break;
                    }
                    this->boardPtr->update_board(i, j, ' ');
                    if (!changeLetter)
                    {
                        return {i, j, letter};
                    }
                }
            }
        }
    }

    // if not all just generate a random letter
    int x = rand() % 3; // Random number between 0 and 2
    int y = rand() % 3;
    char letter = (rand() % 26) + 97;
    return {x, y, letter};
}
