#include <iostream>
#include <string>
#include "bomb1.h"
#include "bomb2.h"
using namespace std;

#define BLACK "\xe2\x97\x8f"
#define WHITE "\xe2\x97\x8c"

void InputBoard(char ** b, int s);
void PrintBoard(char ** b, int s);
void GetUserInput(string &input, char **b, int s); // get user input complete with error handling
void ModifyBoard(char ** b, string input, int turn, int s);
void flipable_horizontal(char ** b, string input, int s, int turn, int * from_col, int * until_col); // to determine from which column until which column that the disk should be flipped
void flip_horizontal(char **b, int from_col, int until_col, int turn, string input); // to flip in horizontal manner, given from which column until which column to be flipped
void flipable_vertical(char ** b, string input, int s, int turn, int * from_row, int * until_row); // to determine from which row until which row that the disk should be flipped
void flip_vertical(char **b, int from_row, int until_row, int turn, string input); // to flip in vertical manner, given from which row until which row to be flipped
void flipable_diagonal1(char ** b, string input, int s, int turn, int * from_row, int * until_row, int * from_col, int * until_col); // to determine from which column & row until which column & row that the disk should be flipped
void flip_diagonal1(char **b, int from_row, int until_row, int from_col, int until_col, int turn, string input); // to flip in a diagonal manner (negative gradient)
void flipable_diagonal2(char ** b, string input, int s, int turn, int * from_row, int * until_row, int * from_col, int * until_col); // to determine from which column & row until which column & row that the disk should be flipped
void flip_diagonal2(char **b, int from_row, int until_row, int from_col, int until_col, int turn, string input); // to flip in a diagonal manner (positive gradient)
void FlipBoard(char ** board, string userinput, int bsize, int turn, int from_row, int until_row, int from_col, int until_col); // wraps up all above flipable and flip functions


int main()
{
     int bsize = 0;
     cout << "Input board size between 8 to 14 (N x N): ";
     cin >> bsize;
     
     if (bsize >= 8 && bsize <= 16){
          char ** board = new char * [bsize];
          for (int i = 0; i < bsize; i++){
               board[i] = new char [bsize];}

          InputBoard(board, bsize);
          PrintBoard(board, bsize);

          string userinput = "";
          int turn = 0;

          int row, column;

          while (userinput != "quit")
          {
               row = 0;
               column = 0;

               int from_col, until_col, from_row, until_row;

               if (turn == 0)
               {
                    cout << "Player white turn, input block to fill: ";
                    GetUserInput(userinput, board, bsize);
                    turn = 1;
                    ModifyBoard(board, userinput, turn, bsize);
                    FlipBoard(board, userinput, bsize, turn, from_row, until_row, from_col, until_col);
                    PrintBoard(board, bsize);
                    continue;
               }

               else if (turn == 1)
               {
                    cout << "Player black turn, input block to fill: ";
                    GetUserInput(userinput, board, bsize);
                    turn = 0;
                    ModifyBoard(board, userinput, turn, bsize);
                    FlipBoard(board, userinput, bsize, turn, from_row, until_row, from_col, until_col); 
                    PrintBoard(board, bsize);
                    continue;
               }
          }
     }
     else{
          cout << "Invalid input, please restart" << endl;
     }

     return 0;
}

void GetUserInput(string &input, char **b, int s){
     cin >> input; //keep prompting user input until correct input is given
     
     //if user input in lower case, make it to uppercase
     if (input[0] >= 'a' && input[0] <= 'z'){
          input[0] = input[0] - ('a' - 'A');
     }

     int row = 0, column = 0;
     if (input.length() == 3)
     {
          row = (int) input[0] - 65;
          column += 10;
          column += ((int) input[2]-48);
     }
     else if (input.length() == 2)
     {
          row = (int) input[0] - 65;
          column += (int) input[1] - 48;
     }
     column--;
     
     //check if user input out of bounds
     if (row > s || row < 0 || column < 0 || column > s){
          cout << "Input out of bounds" << endl << "Try again: ";
          GetUserInput(input, b, s);
     }

     //check if user input already filled with disk
     if (b[row][column] == '0' || b[row][column] == '1'){
          cout << "Board has been filled" << endl << "Try again: ";
          GetUserInput(input, b, s);
     }
          
     return;
}

void InputBoard(char ** b, int s)
{
    for (int i = 0; i < s; i++)
    {
         for (int j = 0; j < s; j++)
         {
              if ((i == (s/2-1) && j == (s/2-1)) || (i == (s/2) && j == (s/2)))
              {
                   b[i][j] = '0';
                   continue;
              }
              else if ((i == (s/2-1) && j == (s/2)) || (i == (s/2) && j == (s/2-1)))
              {
                   b[i][j] = '1';
                   continue;
              }
               b[i][j] = ' ';
         }
         cout << endl;
    }
}

void PrintBoard(char ** b, int s)
{
     cout << "  ";
     for (int i = 0; i < s; i++)
     {
          if (i >= 9)
               cout << " " << i+1 << " ";
          else if (i < 9)
               cout << "  " << i+1 << " ";
     }
     cout << endl;

     for (int i = 0; i < s; i++)
     {
          cout << "   ";
          for (int j = 0; j < s; j++)
               cout << "---" << " ";
          cout << endl;

          cout << (char) ('A'+i) << " ";
          for (int k = 0; k < s; k++)
          {
               if (b[i][k] == '0')
               {
                    cout << "| " << WHITE << " ";
                    continue;
               }

               else if (b[i][k] == '1')
               {
                    cout << "| " << BLACK << " ";
                    continue;
               }

               cout << "| " << b[i][k] << " ";
          }
          cout << "|" << endl;
     }
     cout << "   ";
     for (int j = 0; j < s; j++)
          cout << "---" << " ";
     cout << endl;
}

void ModifyBoard(char ** b, string input, int turn, int s)
{
     int row = 0, column = 0;

     if (input.length() == 3)
     {
          row = (int) input[0] - 65;
          column += 10;
          column += ((int) input[2]-48);
     }
     else if (input.length() == 2)
     {
          row = (int) input[0] - 65;
          column += (int) input[1] - 48;
     }

     column--;

     if (b[row][column] == ' ')
     {
         if (turn == 0)
             b[row][column] = '0';
         else if (turn == 1)
             b[row][column] = '1';
     }

     else if (b[row][column] == '2')
         Bomb1(b, s, row, column);

     else if (b[row][column] == '3')
         Bomb2(b, s, row, column);

     else if (b[row][column] == '4')
     {
         if (turn == 0)
             turn = 1;
         else if (turn == 1)
             turn = 0;
         b[row][column] = ' ';
     }
}

void flipable_horizontal(char ** b, string input, int s, int turn, int * from_col, int * until_col){
     int row = (int) input[0] - 65;
     int origin = 0;
     if (input.length() == 3)
     {
          origin += 10;
          origin += ((int) input[2]-49);
     }
     else if (input.length() == 2)
     {
          origin += (int) input[1] - 49;
     }
     
     char my_turn = turn + 48;

     //from
     for (int i = origin-1; i >= 0; i--){
          if (b[row][i] != '0' && b[row][i] != '1'){
               *from_col = origin;
               break;
          }
          if (b[row][i] == my_turn){
               *from_col = i;
               break;
          } 
     }
     if (origin == 0){ //case for index = 0
          *from_col = 0;
     }
     //until
     for (int j = origin+1; j <= s; j++){
          if (b[row][j] != '0' && b[row][j] != '1'){
               *until_col = origin;
               break;
          }
          if (b[row][j] == my_turn){
               *until_col = j;
               break;
          } 
     }
}

void flip_horizontal(char **b, int from_col, int until_col, int turn, string input){
     int row = (int) input[0] - 65;
     for (int i = from_col + 1; i < until_col; i++){
          if (turn == 1){
               b[row][i] = '1';
          }
          else if (turn == 0){
               b[row][i] = '0';
          }
     }
}

void flipable_vertical(char ** b, string input, int s, int turn, int * from_row, int * until_row){
     int column = 0;
     if (input.length() == 3)
     {
          column += 10;
          column += ((int) input[2]-49);
     }
     else if (input.length() == 2)
     {
          column += (int) input[1] - 49;
     }
     int origin = (int) input[0] - 65;
     char my_turn = turn + 48;

     //from
     for (int i = origin-1; i >= 0; i--){
          if (b[i][column] != '0' && b[i][column] != '1'){
               *from_row = origin;
               break;
          }
          if (b[i][column] == my_turn){
               *from_row = i;
               break;
          } 
     }
     if (origin == 0){ //case for index = 0
          *from_row = 0;
     }
     //until
     for (int j = origin+1; j <= s; j++){
          if (b[j][column] != '0' && b[j][column] != '1'){
               *until_row = origin;
               break;
          }
          if (b[j][column] == my_turn){
               *until_row = j;
               break;
          } 
     }
}

void flip_vertical(char **b, int from_row, int until_row, int turn, string input){
     int column = 0;
     if (input.length() == 3)
     {
          column += 10;
          column += ((int) input[2]-49);
     }
     else if (input.length() == 2)
     {
          column += (int) input[1] - 49;
     }
     for (int i = from_row + 1; i < until_row; i++){
          if (turn == 1){
               b[i][column] = '1';
          }
          else if (turn == 0){
               b[i][column] = '0';
          }
     }
}

void flipable_diagonal1(char ** b, string input, int s, int turn, int * from_row, int * until_row, int * from_col, int * until_col){
     int origin_row = (int) input[0] - 65;
     int origin_column = 0;
     if (input.length() == 3){
          origin_column += 10;
          origin_column += ((int) input[2]-49);
     }
     else if (input.length() == 2){
          origin_column += (int) input[1] - 49;
     }
     
     char my_turn = turn + 48;

     //from
     int i = 1;
     while (origin_column - i >= 0 && origin_row - i >= 0){
          if (b[origin_row - i][origin_column - i] != '0' && b[origin_row - i][origin_column - i] != '1'){
               *from_col = origin_column;
               *from_row = origin_row;
               break;
          }
          if (b[origin_row - i][origin_column - i] == my_turn){
               *from_col = origin_column - i;
               *from_row = origin_row - i;
               break;
          }
          i++;
     }

     //until
     int j = 1;
     while (origin_column + j <= s && origin_row + j <= s){
          if (b[origin_row + j][origin_column + j] != '0' && b[origin_row + j][origin_column + j] != '1'){
               *until_col = origin_column;
               *until_row = origin_row;
               break;
          }
          if (b[origin_row + j][origin_column + j] == my_turn){
               *until_col = origin_column + j;
               *until_row = origin_row + j;
               break;
          }
          j++;
     }
}

void flip_diagonal1(char **b, int from_row, int until_row, int from_col, int until_col, int turn, string input){

     int i = 0;
     while (from_row + i != until_row && from_col + i != until_col){
          if (turn == 1){
               b[from_row+i][from_col+i] = '1';
          }
          else if (turn == 0){
               b[from_row+i][from_col+i] = '0';
          }
          i++;
     }
}

void flipable_diagonal2(char ** b, string input, int s, int turn, int * from_row, int * until_row, int * from_col, int * until_col){
     int origin_row = (int) input[0] - 65;
     int origin_column = 0;
     if (input.length() == 3){
          origin_column += 10;
          origin_column += ((int) input[2]-49);
     }
     else if (input.length() == 2){
          origin_column += (int) input[1] - 49;
     }
     
     char my_turn = turn + 48;
     
     //from
     int i = 1;
     while (origin_row + i <= s && origin_column - i >= 0){
          if (b[origin_row + i][origin_column - i] != '0' && b[origin_row + i][origin_column - i] != '1'){
               *from_row = origin_row;
               *from_col = origin_column;
               break;
          }
          if (b[origin_row + i][origin_column - i] == my_turn){
               *from_row = origin_row + i;
               *from_col = origin_column - i;
               break;
          }
          i++;
     }

     //until
     int j = 1;
     while (origin_row - j >= 0 && origin_column + j <= s ){
          if (b[origin_row - j][origin_column + j] != '0' && b[origin_row - j][origin_column + j] != '1'){
               *until_row = origin_row;
               *until_col = origin_column;
               break;
          }
          if (b[origin_row - j][origin_column + j] == my_turn){
               *until_row = origin_row - j;
               *until_col = origin_column + j;
               break;
          }
          j++;
     }
}

void flip_diagonal2(char **b, int from_row, int until_row, int from_col, int until_col, int turn, string input){

     int i = 0;
     while (from_row - i != until_row && from_col + i != until_col){
          if (turn == 1){
               b[from_row-i][from_col+i] = '1';
          }
          else if (turn == 0){
               b[from_row-i][from_col+i] = '0';
          }
          i++;
     }
}

void FlipBoard(char ** board, string userinput, int bsize, int turn, int from_row, int until_row, int from_col, int until_col){
     flipable_horizontal(board, userinput, bsize, turn, &from_col, &until_col);
     flip_horizontal(board, from_col, until_col, turn, userinput);
     flipable_vertical(board, userinput, bsize, turn, &from_row, &until_row);
     flip_vertical(board, from_row, until_row, turn, userinput);
     flipable_diagonal1(board, userinput, bsize, turn, &from_row, &until_row, &from_col, &until_col);
     flip_diagonal1(board, from_row, until_row, from_col, until_col, turn, userinput);
     flipable_diagonal2(board, userinput, bsize, turn, &from_row, &until_row, &from_col, &until_col);
     flip_diagonal2(board, from_row, until_row, from_col, until_col, turn, userinput);
}
