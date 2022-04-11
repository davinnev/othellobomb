#include <iostream>
#include <string>
using namespace std;

#define BLACK "\xe2\x97\x8f"
#define WHITE "\xe2\x97\x8c"

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

void ModifyBoard(char ** b, string input, int turn)
{
     int row = 0, column;

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
     if (turn == 0)
          b[row][column] = '0';
     else if (turn == 1)
          b[row][column] = '1';
}

void CheckMoves(char **b, int turn, int row, int column, int s)
{
     int count = 0;
     if (turn == 0)
     {
          // horizontal
          for (int i = 0; i < s; i++)
          {
               if (b[row][i] == '0') 
          }
     }

}

int main()
{
     int bsize;
     cout << "Input board size between 8 to 14 (N x N): ";
     cin >> bsize;

     char ** board = new char * [bsize];
     for (int i = 0; i < bsize; i++)
          board[i] = new char [bsize];

     InputBoard(board, bsize);
     PrintBoard(board, bsize);

     string userinput = "";
     int turn = 0;

     int row, column;

     while (userinput != "quit")
     {
          row = 0;
          column = 0;
          if (turn == 0)
          {
               cout << "Player white turn, input block to fill: ";
               cin >> userinput;
               turn = 1;
               ModifyBoard(board, userinput, turn);
               PrintBoard(board, bsize);
               continue;
          }

          else if (turn == 1)
          {
               cout << "Player black turn, input block to fill: ";
               cin >> userinput;
               turn = 0;
               ModifyBoard(board, userinput, turn);
               PrintBoard(board, bsize);
               continue;
          }
     }

     return 0;
}
