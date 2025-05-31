#include "misere.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <cctype> // for toupper()

using namespace std;

template <typename T>
Misere_board<T>::Misere_board()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Misere_board<T>::update_board(int x, int y, T mark)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0))
    {
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template <typename T>
void Misere_board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << "\n";
}

template <typename T>
bool Misere_board<T>::is_win()
{
    for (int i = 0; i < this->rows; i++)
    {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0))
        {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0))
    {
        return true;
    }
    return false;
}

template <typename T>
bool Misere_board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Misere_board<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
Misere_board<T>::~Misere_board()
{

    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
inline Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
inline void Misere_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(string name, T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Misere_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}
