#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h> 


void GetCapitalInitials(string name);

int main(void) {
    string name = GetString();
    GetCapitalInitials(name);
}


void GetCapitalInitials(string name) {

   printf("%c", toupper(name[0]));
   
    for (int i = 0, n = strlen(name); i < n; i++) {
        if (name[i] == ' ') {
           printf("%c", toupper(name[i+1]));
        }
    }
    
    printf("\n");
}

