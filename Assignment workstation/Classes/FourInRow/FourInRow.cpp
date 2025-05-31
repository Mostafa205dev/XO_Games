#include "FourInRow.h"
#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()

using namespace std;

//////////////////////////////////// start Board IMPLEMENTATION

template <typename T>
Four_In_Row_Board<T>::Four_In_Row_Board()
{
    this->rows = 6;
    this->columns = 7;
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
bool Four_In_Row_Board<T>::update_board(int x,int y,T mark){

    for(int i=this->rows-1;i>=0;i--){
        if(this->board[i][y]==0){
            this->board[i][y]=mark;
            return true;
        }
    }  
    return false;
}


// Display the board 
template <typename T>
void Four_In_Row_Board<T>::display_board()
{
    // Print column numbers at the top
    cout << "   ";
    for (int j = 0; j < this->columns; j++) {
        cout << setw(3) << j << " ";
    }
    cout << "\n";

    // Print the board with horizontal and vertical borders
    for (int i = 0; i < this->rows; i++) {
        // Print the top border of each row
        cout << "   ";
        for (int j = 0; j < this->columns; j++) {
            cout << "----";
        }
        cout << "-\n";

        // Print the row content
        cout << setw(2) << i << " "; // Print row number
        for (int j = 0; j < this->columns; j++) {
            char symbol = (this->board[i][j] == 0) ? ' ' : this->board[i][j]; // Empty = ' ', else player symbol
            cout << "| " << symbol << " ";
        }
        cout << "|\n";
    }

    // Print the bottom border
    cout << "   ";
    for (int j = 0; j < this->columns; j++) {
        cout << "----";
    }
    cout << "-\n";
    cout<<endl;
}


template <typename T>
bool Four_In_Row_Board<T>::is_win(){

    // Check rows and columns
    for (int i = 0; i < this->rows; i++)
    {
        for(int j=0;j<4;j++)
        {
            if (this->board[i][j] != 0 && 
                this->board[i][j] == this->board[i][j+1] && 
                this->board[i][j] == this->board[i][j+2] && 
                this->board[i][j] == this->board[i][j+3])     //Check horizontal  
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for(int j=0;j < 4  ;j++)
        {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j+1] &&
                this->board[i][j] == this->board[i+2][j+2] &&
                this->board[i][j] == this->board[i+3][j+3])       //check diagonal     
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for(int j=3;j < this->columns  ;j++)
        {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j-1] &&
                this->board[i][j] == this->board[i+2][j-2] &&
                this->board[i][j] == this->board[i+3][j-3])       //check inverse diagonal     
            {
                return true;
            }
        }
    }

    for (int i = 0; i < 3 ; i++)
    {
        for(int j=0;j < this->columns;j++)
        {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i+1][j] &&
                this->board[i][j] == this->board[i+2][j] &&
                this->board[i][j] == this->board[i+3][j])      //check vertical     
            {
                return true;
            }
        }
    }

    return false;
}


template <typename T>
bool Four_In_Row_Board<T>::is_draw(){
    return (this->n_moves==this->columns*this->rows) && !is_win() ;
}

template <typename T>
bool Four_In_Row_Board<T>::game_is_over(){
    return is_win() || is_draw();
}
/////////////////////////////////////// end Board IMPLEMENTATION




/////////////////////////////////////// start player IMPLEMENTATION
// Constructor Four_In_Row_Player
template <typename T>
Four_In_Row_Player<T>::Four_In_Row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_In_Row_Player<T>::getmove(int &x, int &y)
{
    cout << "\nenter the number of column u want\n";
    cin >> y;
}
/////////////////////////////////////// end player IMPLEMENTATION




/////////////////////////////////////// start Random_player IMPLEMENTATION
// Constructor for Four_In_Row_Random_Player
template <typename T>
Four_In_Row_Random_Player<T>::Four_In_Row_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name= "Random Computer Player";
    
}


template <typename T>
void  Four_In_Row_Random_Player<T>::getmove(int &x, int &y)
{
    

    // Generate a random number between 0 and 6
    y= rand() % 7;
}
/////////////////////////////////////// end Random_player IMPLEMENTATION
