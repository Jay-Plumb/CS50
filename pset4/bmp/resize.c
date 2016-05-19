/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int scale = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if (scale < 1 || scale > 100) {
        printf("%i is not within the range 1-100\n", scale);
        return 2;
    }
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    BITMAPINFOHEADER bi_resize;
    BITMAPFILEHEADER bf_resize;
    // copy content
    bi_resize = bi;
    bf_resize = bf;
    
    // Update output header info
    bi_resize.biWidth = bi.biWidth * scale;
    bi_resize.biHeight = bi.biHeight * scale;
   
    // determine old and new paddings
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi_resize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // new padding

    // Determine new image size
    bi_resize.biSizeImage = ( ( bi_resize.biWidth * sizeof(RGBTRIPLE) ) + newPadding) * abs(bi_resize.biHeight); 
    bf_resize.bfSize = bi_resize.biSizeImage + bf.bfOffBits; // not sure why 54
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_resize, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resize, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines - each row
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Resize vertically - create scale extra rows
        for (int a = 0; a < scale; a++) {
            // Don't reset on first pass
            if (a != 0) {
                fseek(inptr, -(bi.biWidth*sizeof(RGBTRIPLE)), SEEK_CUR);
            }
            
            // iterate over pixels in scanline - column
            for (int j = 0; j < bi.biWidth; j++) 
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                for (int k = 0; k < scale; k++) {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
             // padding 
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);
    
          
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
