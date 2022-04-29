#include <iostream>
#include "bomb2.h"

// This bomb reverses the color of the disks
void Bomb2(char ** b, int s, int row, int column)
{
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {
            // turn white disks into black disks
            if (b[i][j] == '0')
                b[i][j] = '1';
            // turn black disks into white disks
            else if (b[i][j] == '1')
                b[i][j] = '0';
        }
    }
    b[row][column] = ' ';
}
