#include "PyramicTicTacToe.h"
#include <cctype>
// -------------- Board --------------- //

template <typename T>
PyramidBoard<T>::PyramidBoard()
{
    this->rows = 3;
    this->columns = 5;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            if ((i == 0 && j != 2) || (i == 1 && j != 1 && j != 2 && j != 3))
            {
                this->board[i][j] = '-';
            }
            else
            {
                this->board[i][j] = ' ';
            }
        }
    }
}

template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol)
{
    if ((isLogical(x, y) && this->board[x][y] == ' ') || symbol == ' ')
    {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }

    return false;
}

template <typename T>
void PyramidBoard<T>::display_board()
{
    T **temp = this->board;
    for (int i = 0; i < this->rows; i++)
    {
        cout << "| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << " " << (char)toupper(temp[i][j]) << " ";
        }
        cout << " |\n";
    }
    cout << "\n";
}

template <typename T>
bool PyramidBoard<T>::is_win()
{
    T **temp = this->board;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            // cout << "i and j => " << i << " " << j << " " << temp[i][j] << "\n";
            if (temp[i][j] != ' ' && isLogical(i + 1, j) && isLogical(i + 2, j) && temp[i][j] == temp[i + 1][j] && temp[i][j] == temp[i + 2][j]) // vertical win
            {
                // cout << "vertical win\n";
                return true;
            }
            if (temp[i][j] != ' ' && isLogical(i, j + 1) && isLogical(i, j + 2) && temp[i][j] == temp[i][j + 1] && temp[i][j] == temp[i][j + 2]) // horizontal win
            {
                // cout << "horizontal win\n";
                return true;
            }
            if (temp[i][j] != ' ' && isLogical(i + 1, j + 1) && isLogical(i + 2, j + 2) && temp[i][j] == temp[i + 1][j + 1] && temp[i][j] == temp[i + 2][j + 2]) // r-diagonal win
            {
                // cout << "r-diagonal win\n";
                return true;
            }
            if (temp[i][j] != ' ' && isLogical(i + 1, j - 1) && isLogical(i + 2, j - 2) && temp[i][j] == temp[i + 1][j - 1] && temp[i][j] == temp[i + 2][j - 2]) // l-diagonal win
            {
                // cout << "l-diagonal win\n";
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool PyramidBoard<T>::is_draw()
{
    T **temp = this->board;
    int count = 0;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (temp[i][j] == ' ')
            {
                count++;
            }
        }
    }
    return !count;
}

template <typename T>
bool PyramidBoard<T>::game_is_over()
{
    return (is_win() || is_draw());
}

// -------------- Player --------------- //

template <typename T>
PyramidPlayer<T>::PyramidPlayer(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
void PyramidPlayer<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// -------------- Rand Player --------------- //

template <typename T>
PyramidRandPlayer<T>::PyramidRandPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    // this->dimension = 3;
    this->columns = 5;
    this->rows = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void PyramidRandPlayer<T>::getmove(int &x, int &y)
{
    x = rand() % this->rows; // Random number between 0 and 2
    y = rand() % this->columns;
}
