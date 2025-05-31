#include "NumericalTicTacToe.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

#include <cctype> // for toupper()


using namespace std;

//////////////////////////////////// start Board IMPLEMENTATION
template <typename T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board()
{
    this->rows=3;
    this->columns=3;
    this->board = new int *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0; 
        }
    }
    this->n_moves = 0;
}


template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x,int y,T symbol)
{
    if(this->board[x][y]==0){
        this->board[x][y] = symbol;
        this->n_moves++;
        if(isOdd){
            vecOdd.erase(remove(vecOdd.begin(), vecOdd.end(), symbol), vecOdd.end());
        }else{
            vecEven.erase(remove(vecEven.begin(), vecEven.end(), symbol), vecEven.end());
        }

        isOdd=!isOdd;
        return true;
        
    }
    return false;
}


template <typename T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board()
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
            if(this->board[i][j]==0){
                cout << "| " << " " << " ";
            }else{
                cout << "| " << this->board[i][j] << " ";
            }
            
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
bool Numerical_Tic_Tac_Toe_Board<T>::is_win(){
    for(int i=0;i<this->rows;i++)
    {
        if( ((this->board[i][0] + this->board[i][1] + this->board[i][2]) == 15  && this->board[i][0] !=0 && this->board[i][1] !=0 && this->board[i][2] !=0) || ////Check horizontal  
             (this->board[0][i] + this->board[1][i] + this->board[2][i]) == 15  && this->board[0][i] !=0 && this->board[1][i] !=0 && this->board[2][i] !=0)      ////Check vertical
        {
            return true;
        }
    }


    if((this->board[0][0] + this->board[1][1] + this->board[2][2]) == 15  && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2]!= 0 ||
        ((this->board[0][2] + this->board[1][1] + this->board[2][0]) == 15  && this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0]!= 0))       ////Check diagonal
    {
        return true;
    }

    
    return false;
}


template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw(){
    return this->n_moves==9 && !is_win();
}


template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over(){
    return is_win() || is_draw();
}
/////////////////////////////////////// end Board IMPLEMENTATION



/////////////////////////////////////// start player IMPLEMENTATION
// Constructor for Numerical_Tic_Tac_Toe_player
template <typename T>
Numerical_Tic_Tac_Toe_Player<T>::Numerical_Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol){

}



template <typename T>
void Numerical_Tic_Tac_Toe_Player<T>::getmove(int &x, int &y){
    
    int number;
    if(isOdd)
    {
        cout << "\nchoose odd number in the following and dont repeat ";
        for (auto c : vecOdd) {   if ( c   % 2 == 1) { cout << c << " "; }   }
        cout<<endl;
        cin >> number;

        while(find(vecOdd.begin(), vecOdd.end(), number) == vecOdd.end())
        {
            cout << " \ninvalid please choose odd number in the following and dont repeat ";
            for (auto c : vecOdd) { if (c % 2 == 1) {  cout << c << " ";} }
            cout<<endl;
            cin >> number;
        }

        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
        cout<<endl;
              
    }else{
        cout << "\nchoose even number in the following and dont repeat ";
        for (auto c : vecEven) {   if ( c  % 2 == 0) {  cout << c << " ";  }    }
        cout<<endl;
        cin >> number;
        

        while( find(vecEven.begin(), vecEven.end(), number) == vecEven.end())
        {
            cout << "\ninvalid please choose even number in the following and dont repeat ";
            for (auto c : vecEven) {  if ( c  % 2 == 0) {  cout << c << " "; }  }
            cin >> number;
        }

        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
         
    }
    this->symbol = number;
    
}

/////////////////////////////////////// end player IMPLEMENTATION



/////////////////////////////////////// start Random_player IMPLEMENTATION
// Constructor for Numerical_Tic_Tac_Toe_Random_player
template <typename T>
Numerical_Tic_Tac_Toe_Random_Player<T>::Numerical_Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol){
    if(isOdd){
        this->name= "Random Computer odd Player";
    }else{
        this->name= "Random Computer even Player";
    }
    
}


template <typename T>
void Numerical_Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y) {
    
    // Randomly generate x and y coordinates
    x = rand() % 3;
    y = rand() % 3;

    
    if(isOdd)
    {
        int random_index = rand() % vecOdd.size();
        this->symbol = vecOdd[random_index]; 
    }else{
        int random_index = rand() % vecEven.size();
        this->symbol = vecEven[random_index];
    }
    
}


/////////////////////////////////////// end Random_player IMPLEMENTATION