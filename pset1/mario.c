#include <stdio.h>
#include <cs50.h>

int main(void) 
{
   
    int height;
    
    do
    {
         printf("Height: \n");
        height = GetInt(); 
      
    } while (height < 0 || height >= 24);

    int width = height + 1;
    int numberOfHashes = 2;
    // 0 -> 7 : rows
    for (int i = 0; i < height; i++) 
    {
        int spaces = width - numberOfHashes; 
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }
        
        for (int k = 0; k < numberOfHashes; k++) {
            printf("#");
        }
        printf("\n");
        numberOfHashes++;
    }

}