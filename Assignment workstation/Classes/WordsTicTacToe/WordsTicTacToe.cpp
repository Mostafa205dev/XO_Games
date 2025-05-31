#include "WordsTicTacToe.h"
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>
#include <algorithm>

template <typename T>
bool WordsBoard<T>::isLogical(int r, int c)
{
    return (r >= 0 && r < 3 && c >= 0 && c < 3);
}

template <typename T>
bool WordsBoard<T>::isWord(char one, char two, char three)
{
    string wordToFind = "";
    wordToFind += (char)toupper(one);
    wordToFind += (char)toupper(two);
    wordToFind += (char)toupper(three);
    auto it = words.find(wordToFind);
    if (it != words.end())
    {
        return true;
    }
    else
    {
        reverse(wordToFind.begin(), wordToFind.end());
        auto it2 = words.find(wordToFind);
        return (it2 != words.end());
    }
}

template <typename T>
WordsBoard<T>::WordsBoard()
{
    // board init
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
    // words init
    ifstream inputFile("Classes/WordsTicTacToe/dic.txt");
    string word;
    // cout << "is open " << inputFile.is_open() << "\n";
    if (inputFile.is_open())
    {
        while (inputFile >> word)
        {
            this->words.insert(word);
        }
        inputFile.close();
    }
    else
    {
        cerr << "Error: Unable to open file." << "\n";
    }
}

template <typename T>
bool WordsBoard<T>::update_board(int x, int y, T symbol)
{
    if ((isLogical(x, y) && symbol == ' '))
    {
        this->board[x][y] = toupper(symbol);
        return true;
    }

    if (isLogical(x, y) && this->board[x][y] == ' ')
    {
        this->board[x][y] = toupper(symbol);
        return true;
    }

    return false;
}

template <typename T>
void WordsBoard<T>::display_board()
{
    T **temp = this->board;
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n ";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "| " << (char)toupper(temp[i][j]) << (j == this->columns - 1 ? " |" : " ");
        }
        cout << "\n";
        for (int j = 0; j < this->columns; j++)
        {
            cout << "-----";
        }
    }
    cout << "\n";
}

template <typename T>
bool WordsBoard<T>::is_win()
{
    T **temp = this->board;
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            // cout << "i and j => " << i << " " << j << " " << temp[i][j] << "\n";
            if (isLogical(i + 1, j) && isLogical(i + 2, j) && isWord(temp[i][j], temp[i + 1][j], temp[i + 2][j]))
            {
                // cout << "vertical win\n";
                return true;
            }
            if (isLogical(i, j + 1) && isLogical(i, j + 2) && isWord(temp[i][j], temp[i][j + 1], temp[i][j + 2])) // horizontal win
            {
                // cout << "horizontal win\n";
                return true;
            }
            if (isLogical(i + 1, j + 1) && isLogical(i + 2, j + 2) && isWord(temp[i][j], temp[i + 1][j + 1], temp[i + 2][j + 2])) // r-diagonal win
            {
                // cout << "r-diagonal win\n";
                return true;
            }
            if (isLogical(i + 1, j - 1) && isLogical(i + 2, j - 2) && isWord(temp[i][j], temp[i + 1][j - 1], temp[i + 2][j - 2])) // l-diagonal win
            {
                // cout << "l-diagonal win\n";
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool WordsBoard<T>::is_draw()
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
bool WordsBoard<T>::game_is_over()
{
    return (is_win() || is_draw());
}

// -------------- Player --------------- //

template <typename T>
WordsPlayer<T>::WordsPlayer(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
void WordsPlayer<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    char letter;
    cout << "\n Please enter the letter to insert: ";
    cin >> letter;
    this->symbol = toupper(letter);
}

// -------------- Rand Player --------------- //

template <typename T>
WordsRandPlayer<T>::WordsRandPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    // this->dimension = 3;
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void WordsRandPlayer<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension; // Random number between 0 and 2
    y = rand() % this->dimension;
    char letter = (rand() % 26) + 97;
    this->symbol = letter;
}
