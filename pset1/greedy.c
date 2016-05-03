#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Input: 9.75 for $9.75
int main(void) {
    // 25, 10, 5, 1 cents
    int numberOfCoins = 0;
    float cash;
    printf("O hai! ");
    // Input 
    do {
        printf("How much change is owed?\n");
        cash = GetFloat();
        
    } while(cash < 0);
    
    // Convert from float to int
    //printf("%i",cash);
    cash = (int) roundf(cash*100);
 
    //printf("%f", cash);
    while (cash > 0) {
        // Subtract - use multiple if else statements
        if (cash >= 25) {
            cash -= 25;
            numberOfCoins++;
        } else if (cash >= 10) {
            cash -= 10;
            numberOfCoins++;
        } else if (cash >= 5) {
            cash -= 5;
            numberOfCoins++;
        } else if (cash >= 1) {
            cash -= 1;
            numberOfCoins++;
        }
    
    }
    
    // Output
     printf("%i\n",numberOfCoins);
    
}