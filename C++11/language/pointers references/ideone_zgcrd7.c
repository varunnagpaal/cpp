#include <stdio.h>

// Returning address of a local variable from a function
int* functA( int elem )
{
    int i = elem;
    printf("i: %d, &i:%p\n",i, &i );
    i++;
    printf("i: %d, &i:%p\n",i, &i );
     
    return &i;
}

int main(void) 
{
    int k = 100;    
    int *p = NULL;
    
    p = functA( k );
    
    printf("k: %d, p: %p\n", k, p );
    printf("*p: %d \n", *p );   // This line will throw an error
    
	return 0;
}