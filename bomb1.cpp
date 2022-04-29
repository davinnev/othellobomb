#include <iostream>
#include "bomb1.h"

// this bomb erases all the disks in the same row and column as the bomb
void Bomb1(char ** b, int s, int row, int column )
{
    // erase the disks in the same row
    for (int i = 0; i < s; i++)
        b[row][i] = ' ';
    // erase the disks in the same column
    for (int i = 0; i < s; i++)
        b[i][column] = ' ';
}
