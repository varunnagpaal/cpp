#include <stdio.h>

#define ROW 3
#define COL 5

// Partial initialized arrays
int main()
{
    int i,j;
    int Array[ROW][COL] = {{5,4}}; // Partially initialized array.
    
    // What are the other remaining values in the array ?
    for( i = 0 ; i < ROW ; i++ )
    {
        for( j = 0 ; j < COL ; j++ )
        {
            printf("%d ", Array[i][j] );
        }
        printf( "\n");
    }
   return 0;    
}