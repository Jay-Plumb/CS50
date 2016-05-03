#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    
    printf("minutes: ");
    int mins = GetInt();
    printf("bottles: ");
    int bottles = ( (1.5 * 128) / 16 ) * mins;
    
    printf("bottles: %i \n", bottles);
}
