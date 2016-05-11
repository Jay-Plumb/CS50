#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Prototypes 
int ConvertCmdLineToInt(string arg);
bool isPositive(int a);
string GetPlainText();
void createCipherText(string plainText, int k);

int main(int argc, string argv[]) {
    // Check command line arguments
    if (argc != 2 ) {
        printf("Run Using: ./ + key \n");
        return 1;
    }
    int k = ConvertCmdLineToInt(argv[1]); // k will rotate the plaintext by 'k' positions 
    
    
    if ( !isPositive(k) ) {
        //printf("error\n");
       return 1; 
    } 
    
    string plainText = GetPlainText();
    createCipherText(plainText, k);
}

void createCipherText(string p, int k) {
    // Rotate each alphabetical letter by k
    // Non alphabetical characters left unchanged

    
    for (int i = 0; i < strlen(p); i++) {
        // Check if character is in the alphabet
        if (isalpha(p[i]) ) {
            // Check if upper case (isupper())
            // check if lower case (islower())
            if ( isupper(p[i]) ) {
                // printf("upper");
                printf("%c", ((p[i] - 'A') + k) % 26 + 'A');
            }else if ( islower(p[i]) ){
                // printf("lower");
                printf("%c", ((p[i] - 'a') + k) % 26 + 'a');
            } 
        }else {
                printf("%c", p[i]); // Print character as is
        }
    }
    printf("\n");
}

string GetPlainText() {
   // printf("Please Enter PlainText Message: \n");
    return GetString();
}


int ConvertCmdLineToInt(string argv) {
   // int digit = atoi(argv);
   
    return atoi(argv);
}

bool isPositive(int a) {
    if (a < 1) {
        return false;
    }
    return true;
}