#include "sus.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cctype> // for toupper()

using namespace std;

//////////////////////////////////// start BoardPtr IMPLEMENTATION
template <typename T>
Sus_Board<T>::Sus_Board()
{

    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = '0';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Sus_Board<T>::update_board(int x, int y, T mark)
{
    bool tem_return = false;

    if (this->board[x][y] == '0')
    {
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        lastplayer = !lastplayer;
    }
    else
    {
        return false;
    }
    int cnt = 0;
    if (string({this->board[x][0], this->board[x][1], this->board[x][2]}) == "SUS")
    {
        cnt++;
    }
    if (string({this->board[0][y], this->board[1][y], this->board[2][y]}) == "SUS")
    {
        cnt++;
    }
    if (x == 0)
    {
        if (y == 0)
        {
            if (string({this->board[0][0], this->board[1][1], this->board[2][2]}) == "SUS")
            {
                cnt++;
            }
        }
        if (y == 2)
        {
            if (string({this->board[2][0], this->board[1][1], this->board[0][2]}) == "SUS")
            {
                cnt++;
            }
        }
    }
    else if (x == 1)
    {
        if (y == 1)
        {
            if (string({this->board[0][0], this->board[1][1], this->board[2][2]}) == "SUS")
            {
                cnt++;
            }
            if (string({this->board[2][0], this->board[1][1], this->board[0][2]}) == "SUS")
            {
                cnt++;
            }
        }
    }
    else
    {
        if (y == 2)
        {
            if (string({this->board[0][0], this->board[1][1], this->board[2][2]}) == "SUS")
            {
                cnt++;
            }
        }
        if (y == 0)
        {
            if (string({this->board[2][0], this->board[1][1], this->board[0][2]}) == "SUS")
            {
                cnt++;
            }
        }
    }
    if (!this->lastplayer && cnt > 0)
    {
        this->counterp1 += cnt;
        cout << "player 1 has " << this->counterp1 << " SUS\n";
    }
    else if (this->lastplayer && cnt > 0)
    {
        this->counterp2 += cnt;
        cout << "player 2 has " << this->counterp2 << " SUS\n";
    }
    return true;
}

template <typename T>
void Sus_Board<T>::display_board()
{
    // Print column numbers at the top
    cout << "   ";
    for (int j = 0; j < this->columns; j++)
    {
        cout << setw(3) << j << " ";
    }
    cout << "\n";

    // Print the boardptr with horizontal and vertical borders
    for (int i = 0; i < this->rows; i++)
    {
        // Print the top border of each row
        cout << "   ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "----";
        }
        cout << "-\n";

        // Print the row content
        cout << setw(2) << i << " "; // Print row number
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] == 0)
            {
                cout << "| " << " " << " ";
            }
            else
            {
                cout << "| " << this->board[i][j] << " ";
            }
        }
        cout << "|\n";
    }

    // Print the bottom border
    cout << "   ";
    for (int j = 0; j < this->columns; j++)
    {
        cout << "----";
    }
    cout << "-\n";
    cout << endl;
}

template <typename T>
bool Sus_Board<T>::is_win()
{

    if (counterp1 > counterp2 && this->n_moves == 9)
    {
        cout << this->name1;
        return true;
    }
    else if (counterp1 > counterp2 && this->n_moves == 9)
    {
        cout << this->name2;
        return true;
    }

    return false;
}

template <typename T>
bool Sus_Board<T>::is_draw()
{
    return this->n_moves == 9 && counterp1 == counterp2;
}

template <typename T>
bool Sus_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}
//////////////////////////////////// end BoardPtr IMPLEMENTATION

//////////////////////////////////// start player IMPLEMENTATION
// Constructor for Sus_Player
template <typename T>
Sus_Player<T>::Sus_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Sus_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}
//////////////////////////////////// end player IMPLEMENTATION

//////////////////////////////////// start Random player IMPLEMENTATION
// Constructor for Sus_Random_Player
template <typename T>
Sus_Random_Player<T>::Sus_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Sus_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % 3;
    y = rand() % 3;
}
//////////////////////////////////// end Random player IMPLEMENTATION