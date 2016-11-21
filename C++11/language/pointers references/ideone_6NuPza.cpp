#include <iostream>

// Returning reference to a local variable from a function
int& functA( int& elem )
{
    int i = elem;
    printf("i: %d, &i:%p\n",i, &i );
    
    i++;
    
    printf("i: %d, &i:%p\n",i, &i );
    
     
    return i;
}
 
int main(void) 
{
    int k = 100;    
    
    int result =  functA(k);

    printf("k: %d, result: %d\n", k, result );
    
    return 0;
}