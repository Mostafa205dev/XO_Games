#include "FiveXFive.h"
#include <iostream>
#include <iomanip>
#include <set>
#include <cctype> // for toupper()

using namespace std;

template <typename T>

FiveXFive_board<T>::FiveXFive_board()
{
    this->rows = this->columns = 5;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FiveXFive_board<T>::update_board(int x, int y, T mark)
{
    // if (AIundo)
    // {
    //     cout << "im now undoing\n"
    //          << "while winrev = " << winRev << "\n";
    // }
    if (AIisX)
    {
        dif1 = count_lines('X') - count_lines('O');
    }
    else
    {
        dif1 = count_lines('O') - count_lines('X');
    }
    if (AIundo && winRev)
    {
        winRev = false;
    }
    if (winRev && !AIundo)
    {
        last = !last;
        return true;
    }
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' || mark == ' '))
    {
        if (mark == ' ')
        {
            this->n_moves--;
            this->board[x][y] = ' ';
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            last = !last;
        }
        // cout << " n moves --> " << this->n_moves << "\n";
        return true;
    }
    return false;
}

template <typename T>
void FiveXFive_board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n------------------------------------------";
    }
    cout << "\n";
}

template <typename T>
int FiveXFive_board<T>::count_lines(T symbol)
{
    int Xlines = 0;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] != symbol)
                continue;
            int cnt = 1;
            // top left
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                if (this->board[i - 1][j - 1] == symbol)
                    cnt++;
            }
            // bottom right
            if (i + 1 < this->rows && j + 1 < this->columns)
            {
                if (this->board[i + 1][j + 1] == symbol)
                    cnt++;
            }
            if (cnt == 3)
            {
                Xlines++;
            }
            cnt = 1;
            // top right
            if (i - 1 >= 0 && j + 1 < this->columns)
            {
                if (this->board[i - 1][j + 1] == symbol)
                    cnt++;
            }
            // bottom left
            if (i + 1 < this->rows && j - 1 >= 0)
            {
                if (this->board[i + 1][j - 1] == symbol)
                    cnt++;
            }
            if (cnt == 3)
            {
                Xlines++;
            }
            cnt = 1;
            // up
            if (i - 1 >= 0)
            {
                if (this->board[i - 1][j] == symbol)
                    cnt++;
            }
            // down
            if (i + 1 < this->rows)
            {
                if (this->board[i + 1][j] == symbol)
                    cnt++;
            }
            if (cnt == 3)
            {
                Xlines++;
            }
            cnt = 1;
            // left
            if (j - 1 >= 0)
            {
                if (this->board[i][j - 1] == symbol)
                    cnt++;
            }
            // right
            if (j + 1 < this->columns)
            {
                if (this->board[i][j + 1] == symbol)
                    cnt++;
            }
            if (cnt == 3)
            {
                Xlines++;
            }
        }
    }
    return Xlines;
}

template <typename T>
bool FiveXFive_board<T>::is_win()
{
    if (this->n_moves == 24 || winRev)
    {
        set<char> s;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                if (this->board[i][j] == ' ')
                    continue;
                s.insert(this->board[i][j]);
            }
        }
        char a[2];
        int i = 0;
        for (auto c : s)
        {
            a[i] = c;
            i++;
        }
        int xlines = count_lines(a[1]); // x after o
        int ylines = count_lines(a[0]);
        if (xlines > ylines && last || xlines < ylines && !last)
        {
            cout << "X lines are " << xlines << " " << "O lines are " << ylines << "\n";
            return true;
        }
        else if ((xlines < ylines && last) || (xlines > ylines && !last))
        {
            winRev = true;
            return false;
        }
    }

    return false;
}

template <typename T>
bool FiveXFive_board<T>::is_draw()
{
    if (winRev)
        return false;
    return (this->n_moves == 24 && !is_win());
}

template <typename T>
bool FiveXFive_board<T>::game_is_over()
{
    return (is_win() || is_draw());
}

template <typename T>
FiveXFive_board<T>::~FiveXFive_board()
{
    for (int i = 0; i < this->rows; ++i)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
FiveXFive_Player<T>::FiveXFive_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FiveXFive_Player<T>::getmove(int &x, int &y)
{
    if (winRev)
        return;
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
FiveXFive_Random_Player<T>::FiveXFive_Random_Player(T symbol)
    : RandomPlayer<T>(symbol) // Pass symbol to the base class constructor
{
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void FiveXFive_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % 5; // Random x position in [0, 4]
    y = rand() % 5; // Random y position in [0, 4]
}
