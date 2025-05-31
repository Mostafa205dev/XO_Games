// #include "../../BoardGame_Classes.h"
// #include <bits/stdc++.h>
// #include <cctype>
// #include <algorithm>
// using namespace std;

// template <typename T>
// class FIVEXFIVE_AI_Player : public Player<T>
// {
// public:
//     FIVEXFIVE_AI_Player(string name, T symbol);

//     void getmove(int &x, int &y) override;

// private:
//     pair<int, int> getBestMove();

//     const int MAX_DEPTH = 3; // You can adjust the depth value here
// };

// // ======================== //
// template <typename T>
// FIVEXFIVE_AI_Player<T>::FIVEXFIVE_AI_Player(string name, T symbol) : Player<T>(symbol)
// {
//     this->name = "AI Player";
// }

// // Method to get the best move for the player
// template <typename T>
// void FIVEXFIVE_AI_Player<T>::getmove(int &x, int &y)
// {
//     pair<int, int> bestMove = getBestMove();
//     x = bestMove.first;
//     y = bestMove.second;
// }

// template <typename T>
// pair<int, int> FIVEXFIVE_AI_Player<T>::getBestMove()
// {
//     pair<int, int> bestMove = {-1, -1};
//     T opSymbol = this->symbol == 'X' ? 'O' : 'X';
//     if (opSymbol == 'X')
//     {
//         AIisX = false;
//     }
//     // Check if the AI can win or block a loss (first priority)
//     for (int i = 0; i < 5; i++)
//     {
//         for (int j = 0; j < 5; j++)
//         {
//             int difBefore = dif1;
//             if (this->boardPtr->update_board(i, j, this->symbol))
//             {
//                 if (dif1 != difBefore)
//                 {
//                     cout << "now in win, difBefore is " << difBefore << "\n";
//                     cout << "wining move dif1 is " << dif1 << "\nat indexes " << i << " " << j << "\n";
//                     this->boardPtr->display_board();
//                     AIundo = true;
//                     this->boardPtr->update_board(i, j, ' ');
//                     AIundo = false;
//                     return {i, j};
//                 }
//                 AIundo = true;
//                 this->boardPtr->update_board(i, j, ' ');
//                 AIundo = false;
//             }
//         }
//     }

//     // Block the opponent from winning
//     for (int i = 0; i < 5; i++)
//     {
//         for (int j = 0; j < 5; j++)
//         {
//             int dif2Before = -dif1;
//             if (this->boardPtr->update_board(i, j, opSymbol))
//             {
//                 if (-dif1 != -dif2Before)
//                 {
//                     cout << "losing move dif2Before is " << dif2Before << " dif1 is " << dif1 << "\nat indexes " << i << " " << j << "\n";
//                     this->boardPtr->display_board();
//                     AIundo = true;
//                     this->boardPtr->update_board(i, j, ' ');
//                     AIundo = false;
//                     cout << "\n";
//                     return {i, j};
//                 }
//                 AIundo = true;
//                 this->boardPtr->update_board(i, j, ' ');
//                 AIundo = false;
//             }
//         }
//     }

//     do
//     {
//         x = rand() % 5;
//         y = rand() % 5;
//     } while (!this->boardPtr->update_board(x, y, this->symbol));

//     return {x, y};
// }
