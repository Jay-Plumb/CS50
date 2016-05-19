/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

int main(int argc, char* argv[])
{
    // Open the memory card file
    char* file = "card.raw";
    FILE* memoryCard = fopen(file,"r");
    
    if (memoryCard == NULL) {
        printf("Could not open %s\n", file);
        return 2;
    }
    
    // Find beginning of JPEG 0xff 0xd8 0xff 0xe# where # is (0-9 and A-F) - stored side by side 
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK];
    char fileName[8]; // This will hold xxx.jpg\0 so we need a char array of 8
    int count = 0;
    FILE* img = NULL;
    
    // Keep reading in 512 block bytes from memoryCard until end
    while (fread(&buffer, BLOCK, 1, memoryCard) == 1) {
        // Look for start of jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer[3] == 0xe2 || buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer[3] == 0xe5 || buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer[3] == 0xe8 || buffer[3] == 0xe9 || buffer[3] == 0xea || buffer[3] == 0xeb || buffer[3] == 0xec || buffer[3] == 0xed || buffer[3] == 0xee ||buffer[3] == 0xef)) {
            
            // Close previous image if we had one
            if (count > 0) {
                fclose(img);
            }
            
            
            
            // Open a new jpg
            sprintf(fileName, "%03d.jpg", count);
       
            img = fopen(fileName,"a"); // We want to keep appending data to this file
            
            // Keep on reading 512 bytes until 
            if (img == NULL) {
                printf("Unable to open %s\n", fileName);
                return 2;
            }
            
            // Write from buffer to output file - write all 512 buffer
            fwrite(&buffer, BLOCK, 1, img);
             count++;      
        } else {
            // We either have bad data (only initially) or we need to add the remaining bytes from jpeg image
            if (count > 0) {
                 // Write 512 bytes until jpg is found
                fwrite(&buffer, BLOCK, 1, img);
            }
        }
            
        
            
    }
    
}
