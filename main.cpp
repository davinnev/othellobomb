#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include "bomb1.h"
#include "bomb2.h"
using namespace std;

#define BLACK "\xe2\x97\x8f"
#define WHITE "\xe2\x97\x8c"
#define SILLY "\xf0\x9f\x98\x86"
#define NICE "\xf0\x9f\x98\x87"
#define EVIL "\xf0\x9f\x98\x88"

void InputBoard(char ** b, int s);
void PrintBoard(char ** b, int s);
string GetUserInput(char **b, int s); // get user input complete with error handling
int GetBoardSize(); // get user input of the size of board
bool CountEmpty(char ** b, int s);
int get_row(string input); //to get the integer representation of row (ex: A1 -> row = 0, B0 -> row = 1)
int get_column(string input); //to get the integer representation of column (ex: A1 -> col = 1, B0 -> col = 0)
void ModifyBoard(char ** b, string input, int turn, int s);
void Bomb3(char ** b, string input, int &turn, int s); // Bomb 3 lets the current player go on another turn
void flipable_horizontal(char ** b, string input, int s, int turn, int * from_col, int * until_col); // to determine from which column until which column that the disk should be flipped
void flip_horizontal(char **b, int from_col, int until_col, int turn, string input); // to flip in horizontal manner, given from which column until which column to be flipped
void flipable_vertical(char ** b, string input, int s, int turn, int * from_row, int * until_row); // to determine from which row until which row that the disk should be flipped
void flip_vertical(char **b, int from_row, int until_row, int turn, string input); // to flip in vertical manner, given from which row until which row to be flipped
void flipable_diagonal1(char ** b, string input, int s, int turn, int * from_row, int * until_row, int * from_col, int * until_col); // to determine from which column & row until which column & row that the disk should be flipped
void flip_diagonal1(char **b, int from_row, int until_row, int from_col, int until_col, int turn, string input); // to flip in a diagonal manner (positive gradient)
void flipable_diagonal2(char ** b, string input, int s, int turn, int * from_row, int * until_row, int * from_col, int * until_col); // to determine from which column & row until which column & row that the disk should be flipped
void flip_diagonal2(char **b, int from_row, int until_row, int from_col, int until_col, int turn, string input); // to flip in a diagonal manner (negative gradient)
void FlipBoard(char ** board, string userinput, int bsize, int turn, int from_row, int until_row, int from_col, int until_col); // wraps up all above flipable and flip functions
void GenerateRandomPositionForBomb(char ** b, int s, int no_of_bombs);
void CountScore(char ** b, int s, string p1, string p2); //count the score of each player, decide winner, store in leaderboard

int main()
{
     cout << endl;
     cout << "*******************************************" << endl;
     cout << "          WELCOME TO OTHELLO BOMB          " << endl;
     cout << "                LET'S PLAY!                " << endl;
     cout << "*******************************************" << endl;
     cout << "Input board size between 6 to 10 (N x N): ";
     int bsize = GetBoardSize(); //assume user input integer
     
     char ** board = new char * [bsize];
     for (int i = 0; i < bsize; i++){
          board[i] = new char [bsize];}

     InputBoard(board, bsize);
     
     int no_of_bombs;
     cout << "Input how many bombs do you want: ";
     cin >> no_of_bombs; // assume no of bombs not more than bsize*bsize
     
     string player1, player2;
     cout << "Player 1 name (white): ";
     cin >> player1;
     cout << "Player 2 name (black): ";
     cin >> player2;

     PrintBoard(board, bsize);

     GenerateRandomPositionForBomb(board, bsize, no_of_bombs);

     string userinput = "";
     int turn = 0;

     int row, column;

    while (CountEmpty(board, bsize ))
     {
          row = 0;
          column = 0;

          int from_col, until_col, from_row, until_row;

          if (turn == 0)
          {
               cout << "Player white " << WHITE << " turn, input block to fill: ";
               userinput = GetUserInput(board, bsize);
               if (userinput == "quit" || userinput == "QUIT"){
                    break;
               }
               from_row = get_row(userinput); until_row = get_row(userinput); 
               from_col = get_column(userinput); until_col = get_column(userinput);

               ModifyBoard(board, userinput, turn, bsize);
               FlipBoard(board, userinput, bsize, turn, from_row, until_row, from_col, until_col);
               PrintBoard(board, bsize);

               turn = 1;
               Bomb3(board, userinput, turn, bsize);
               continue;
          }

          else if (turn == 1)
          {
               cout << "Player black " << BLACK << " turn, input block to fill: ";
               userinput = GetUserInput(board, bsize);
               if (userinput == "quit" || userinput == "QUIT"){
                    break;
               }

               from_row = get_row(userinput); until_row = get_row(userinput); 
               from_col = get_column(userinput); until_col = get_column(userinput);

               ModifyBoard(board, userinput, turn, bsize);
               FlipBoard(board, userinput, bsize, turn, from_row, until_row, from_col, until_col);
               PrintBoard(board, bsize);

               turn = 0;
               Bomb3(board, userinput, turn, bsize);
               continue;
          }
     }
     CountScore(board, bsize, player1, player2);
     return 0;
}

bool CountEmpty(char ** b, int s)
{
     for (int i = 0; i < s; i++)
     {
          for (int j = 0; j < s; j++)
          {
               if (b[i][j] == ' ')
                    return 1;
          }
     }
     return 0;
}

int get_row(string input){
     int row = (int) input[0] - 65;
     return row;
}

int get_column(string input){
     int column = -1;
     if (input.length() == 3)
     {
          column += 10;
          column += ((int) input[2]-48);
     }
     else if (input.length() == 2)
     {
          column += (int) input[1] - 48;
     }
     return column;
}

void GenerateRandomPositionForBomb(char ** b, int s, int no_of_bombs){
     srand(time(0));
     for (int i = 2; i < no_of_bombs+2; i++){
          int row = rand() % s;
          int column = rand() % s;
          // cout << "bomb " << i << " in postion b [" << row << "][" << column << "]" << endl;
          if (b[row][column] != '0' && b[row][column] != '1' && b[row][column] != '1' && b[row][column] != '2' && b[row][column] != '3'){
               if (i % 3 == 0){
                    b[row][column] = '3'; //'3' for flip_color bomb
               }
               else if (i % 3 == 1){
                    b[row][column] = '4'; //'4' for good bomb
               }
               else if (i % 3 == 2){
                    b[row][column] = '2'; //'2' for erase bomb
               }
          }
          else{
               i--;
          }
     }
}

int GetBoardSize(){
     int board_size;
     cin >> board_size;
     while (board_size < 6 || board_size > 10){
          cout << "Board size must be between 6-10" << endl << "Please try again: ";
          cin >> board_size;
     }
     return board_size;
}

string GetUserInput(char **b, int s){
     bool correct = false;
     string input;
     while (correct == false){
          cin >> input; //keep prompting user input until correct input is given
          correct = true;
          if (input == "quit"){
               return input;
          }
          //if user input in lower case, make it to uppercase
          if (input[0] >= 'a' && input[0] <= 'z'){
               input[0] = input[0] - ('a' - 'A');
          }
          //get row and column in integer form
          int row = get_row(input), column = get_column(input);

          //check for out of bounds
          bool out_of_bounds = false;
          if (row < 0 || row > s || column < 0 || column > s){
               cout << "input out of bounds" << endl << "Please try again: ";
               correct = false;
               out_of_bounds = true;
          }
          //check for input in filled box
          if (out_of_bounds == false){
               if (b[row][column] == '0' || b[row][column] == '1'){
                    cout << "Board has been filled" << endl << "Please try again: ";
                    correct = false;
               }
          }
     }
     return input;
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
    }
}

void PrintBoard(char ** b, int s)
{
     cout << endl;
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
               else if (b[i][k] == '2' || b[i][k] == '3' || b[i][k] == '4')
               {
                    cout << "| " << ' ' << " ";
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
     int row = get_row(input), column = get_column(input);

     if (b[row][column] == ' ')
     {
         if (turn == 0)
             b[row][column] = '0';
         else if (turn == 1)
             b[row][column] = '1';
     }
     
     else if (b[row][column] == '2')
     {
         cout << "You stepped on The Evil Bomb!" << " " << EVIL << endl;
         Bomb1(b, s, row, column);
     }

     else if (b[row][column] == '3')
     {
         cout << "You stepped on The Silly Bomb!" << " " << SILLY << endl;
         Bomb2(b, s, row, column);
     }
}

void Bomb3(char ** b, string input, int &turn, int s)
{
    int row = get_row(input), column = get_column(input);

    if (b[row][column] == '4')
    {
        cout << "You stepped on The Nice Bomb!" << " " << NICE << endl;
        if (turn == 1)
        {
            turn = 0;
            b[row][column] = '0';
            PrintBoard(b, s);
        }
        else if (turn == 0)
        {
            turn = 1;
            b[row][column] = '1';
            PrintBoard(b, s);
        }
    }
}

void CountScore(char ** b, int s, string p1, string p2){
     int white_counter = 0, black_counter = 0;

     for (int i = 0; i < s; i++){
          for (int j = 0; j < s; j++){
               if (b[i][j] == '0'){
                    white_counter += 1;
               }
               else if (b[i][j] == '1'){
                    black_counter += 1;
               }
          }
     }
     cout << "White Player Score: " << white_counter << endl;
     cout << "Black Player Score: " << black_counter << endl;
     
     ofstream fout("leaderboard_temp.txt", ios::app);
     ifstream fin("leaderboard.txt");
     
     string pname = "";
     string line;
     int counter = 0;

     while (getline(fin, line))
     {
          ofstream fout("leaderboard_temp.txt", ios::app);
          ifstream fin("leaderboard.txt");
          pname = "";

          for (int i = 0; i < line.length(); i++)
          {
               if (line[i] != ' ')
                    pname += line[i];
               else if (line[i] == ' ')
                    break;
          }

          if (white_counter > black_counter)
          {
               string currentrecord = line.substr(p1.length()+1, 2);
               int crecord = atoi(currentrecord.c_str());
               int newrecord = (white_counter*100/(s*s));

               if (pname != p1)
               {
                    fout << line << endl;
                    continue;
               }

               else if (pname == p1)
               {
                    if (crecord < newrecord)
                    {
                         line.replace(p1.length()+1, currentrecord.length(), to_string(newrecord));
                         fout << line << endl;
                         remove("leaderboard.txt");
                         ofstream fout("leaderboard.txt", ios::app);
                         ifstream fin("leaderboard_temp.txt");
                         while (getline(fin, line))
                              fout << line << endl;
                         remove("leaderboard_temp.txt");
                         fout.close();
                         fin.close();
                    }
                    counter = 1;
                    break;
               }
          }

          else if (white_counter < black_counter)
          {
               string currentrecord = line.substr(p2.length()+1, 2);
               int crecord = atoi(currentrecord.c_str());
               int newrecord = (black_counter*100/(s*s));

               if (pname != p2)
               {
                    fout << line << endl;
                    continue;
               }

               else if (pname == p2)
               {
                    if (crecord < newrecord)
                    {
                         line.replace(p2.length()+1, currentrecord.length(), to_string(newrecord));
                         fout << line << endl;
                         remove("leaderboard.txt");
                         ofstream fout("leaderboard.txt", ios::app);
                         ifstream fin("leaderboard_temp.txt");
                         while (getline(fin, line))
                              fout << line << endl;
                         remove("leaderboard_temp.txt");
                         fout.close();
                         fin.close();
                    }
                    counter = 1;
                    break;
               }
          }
     }

     ofstream fout2("leaderboard.txt", ios::app);
     if (counter == 0)
     {
          if (white_counter > black_counter)
          {
               fout2 << p1 << " ";
               fout2 << (white_counter*100/(s*s)) << "% of board filled";
               fout2 << endl;
          }

          else if (white_counter < black_counter)
          {
               fout2 << p2 << " ";
               fout2 << (black_counter*100/(s*s)) << "% of board filled";
               fout2 << endl;
          }
          remove("leaderboard_temp.txt");
     }

     fin.close();
     fout2.close();
     

     if (white_counter > black_counter){
          cout << "White " << WHITE << " Player Wins" << endl;
     }
     else if (white_counter < black_counter){
          cout << "Black " << BLACK << " Player Wins" << endl;
     }
     else{
          cout << "It's a tie !!" << endl;
     }
}

void flipable_horizontal(char ** b, string input, int s, int turn, int * from_col, int * until_col){
     int row = get_row(input), column = get_column(input);
     char my_turn = turn + 48;
     //from
     for (int i = column; i >= 0; i--){
          if (b[row][i] != '0' && b[row][i] != '1' && i != column){
               *from_col = column;
               break;
          }
          if (b[row][i] == my_turn && i != column){
               *from_col = i;
               break;
          } 
     }
     
     //until
     for (int j = column; j < s; j++){
          if (b[row][j] != '0' && b[row][j] != '1' && j != column){
               *until_col = column;
               break;
          }
          if (b[row][j] == my_turn && j != column){
               *until_col = j;
               break;
          } 
     }
     
}

void flip_horizontal(char **b, int from_col, int until_col, int turn, string input){
     int row = get_row(input);
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
     int column = get_column(input), row = get_row(input);
     char my_turn = turn + 48;
     
     //from
     for (int i = row; i >= 0; i--){
          if (b[i][column] != '0' && b[i][column] != '1' && i != row){
               *from_row = row;
               break;
          }
          if (b[i][column] == my_turn && i != row){
               *from_row = i;
               break;
          } 
     }
     
     //until
     for (int j = row; j < s; j++){
          if (b[j][column] != '0' && b[j][column] != '1' && j != row){
               *until_row = row;
               break;
          }
          if (b[j][column] == my_turn && j != row){
               *until_row = j;
               break;
          } 
     }

}

void flip_vertical(char **b, int from_row, int until_row, int turn, string input){
     int column = get_column(input);
     
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
     int origin_row = get_row(input), origin_column = get_column(input);
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
     while (origin_column + j < s && origin_row + j < s){
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
     while (from_row + i < until_row && from_col + i < until_col){
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
     int origin_row = get_row(input), origin_column = get_column(input);
     char my_turn = turn + 48;
     //from
     int i = 1;
     while (origin_row + i < s && origin_column - i >= 0){
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
     while (origin_row - j >= 0 && origin_column + j < s){
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
     while (from_row - i > until_row && from_col + i < until_col){
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
