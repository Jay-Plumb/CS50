#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Prototypes
bool GetStringKeyword(string argv);
string GetPlainText(void);
void VigenereCipher(string k, string p);

int main(int argc, string argv[]) {
    
    if (argc != 2 ) {
        printf("Run Using: ./ + key \n");
        return 1;
    }
    string k = "";
    
    if ( GetStringKeyword(argv[1])) {
        k = argv[1];
    } else {
        printf("Please only enter strings and not numbers");
        return 1;
    }
    
    // Get users plaintext message
    string plainText = GetPlainText();
    VigenereCipher(k, plainText);
   // printf("%s: %s", k, plainText);
}


void VigenereCipher(string k, string p) {
    int j = 0;
    for (int i = 0; i < strlen(p); i++) {
        // Make sure each index has a character in the string p
        if (isalpha(p[i]) ) {
            if ( isupper(p[i]) ) {
                //printf("%lu",i % strlen(k)); // i % strlen(k) gives a wrapped around index 
                printf("%c", ((p[i] - 'A') + ( tolower(k[j % strlen(k)]) - 'a') ) % 26 + 'A'); // A,a B,b are treated the same so use tolower() -'a'
            }else if ( islower(p[i]) ){
                printf("%c", ((p[i] - 'a') + (tolower(k[j % strlen(k)]) - 'a') ) % 26 + 'a'); // 
            } 
            j++;
        } else {
                printf("%c", p[i]); // Print character as is
        }
    }
    printf("\n");
}

string GetPlainText(void) {
    string p = "";
    p = GetString();
    return p;
}

bool GetStringKeyword(string argv) {
    // Check if input is actually a string
    for (int i=0; i< strlen(argv); i++) {
        if (!isalpha(argv[i])) {
            return false;
        }
    }
    return true;
}