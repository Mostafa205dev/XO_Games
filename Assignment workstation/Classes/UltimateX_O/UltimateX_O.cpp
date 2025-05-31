#include "UltimateX_O.h"
#include <cctype>

// -------------- Board --------------- //

template <typename T>
UltimateX_OBoard<T>::UltimateX_OBoard(bool main) : isMain(main)
{
    this->rows = 3;
    this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = ' ';
        }
    }

    for (int i = 0; i < 9; i++)
    {
        boards[i] = main ? new UltimateX_OBoard<char>(false) : nullptr;
    }
};

template <typename T>
bool UltimateX_OBoard<T>::update_board(int x, int y, T symbol) // for main board only
{
    int boardIndex = ((x / 3) * 3) + (y / 3);
    if ((isLogical(x, y) && this->boards[boardIndex]->board[x % 3][y % 3] == ' ' && !this->boards[boardIndex]->game_is_over() && !this->game_is_over()) || symbol == ' ')
    {
        if (symbol == ' ')
        {
            if (this->boards[boardIndex]->is_win())
            {
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (this->boards[boardIndex]->board[i][j] == '-')
                        {
                            this->boards[boardIndex]->board[i][j] = ' ';
                        }
                    }
                }
                this->board[x / 3][y / 3] = ' ';
            }
            this->boards[boardIndex]->board[x % 3][y % 3] = ' ';
            return true;
        }

        this->boards[boardIndex]->board[x % 3][y % 3] = toupper(symbol);
        this->boards[boardIndex]->n_moves++;
        // cout << "iswin " << this->boards[boardIndex]->is_win() << "\n";
        // this->boards[boardIndex]->display_board();
        if (this->boards[boardIndex]->is_win())
        {
            this->n_moves++;
            this->board[x / 3][y / 3] = toupper(symbol);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (this->boards[boardIndex]->board[i][j] == ' ')
                    {
                        this->boards[boardIndex]->board[i][j] = '-';
                    }
                }
            }
        }
        else if (this->boards[boardIndex]->is_draw())
        {
            this->n_moves++;
            this->board[x / 3][y / 3] = '-';
        }
        return true;
    }
    return false;
}

template <typename T>
void UltimateX_OBoard<T>::display_board()
{
    if (!this->isMain)
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
        cout << endl;
        return;
    }

    cout << "THE WHOLE BOARD\n=========================================\n";
    for (int i = 0; i < 9; i++)
    {
        cout << "|| ";
        for (int j = 0; j < 9; j++)
        {
            bool dbl = (j == 2 || j == 5);
            int boardIndex = ((i / 3) * 3) + (j / 3);
            cout << (char)toupper(this->boards[boardIndex]->board[i % 3][j % 3]);
            if (dbl)
            {
                cout << " || ";
            }
            else if (j != 8)
            {
                cout << " | ";
            }
        }
        cout << " ||\n";
        if ((i + 1) % 3 == 0)
            cout << "=========================================\n";
    }

    cout << "\nTHE MINIMIZED BOARD\n-------------";
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << this->board[i][j] << " | ";
        }
        cout << "\n-------------";
    }
    cout << "\n";
}

template <typename T>
bool UltimateX_OBoard<T>::is_win()
{
    for (int i = 0; i < this->rows; i++)
    {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' '))
        {
            return true;
        }
    }
    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' '))
    {
        return true;
    }
    return false;
}

template <typename T>
bool UltimateX_OBoard<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool UltimateX_OBoard<T>::game_is_over()
{
    return (is_win() || is_draw());
}

// -------------- Player --------------- //

template <typename T>
UltimateX_OPlayer<T>::UltimateX_OPlayer(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
void UltimateX_OPlayer<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x (0 to 8) and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// -------------- Rand Player --------------- //

template <typename T>
UltimateX_ORandPlayer<T>::UltimateX_ORandPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void UltimateX_ORandPlayer<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}