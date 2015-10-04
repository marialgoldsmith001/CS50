/**Marial Gutierrez
 * resize.c
 * Computer Science 50
 * Problem Set 4
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
    char* infile = argv[2];
    char* outfile = argv[3];

    //number by which image will be resized
    int number = atoi(argv[1]);
    
    // condition for user to provide a number between 1 and 100
    if (number < 1)
    {
        printf("Number must be positive\n");
        return 1;
    }
    if (number > 100)
    {
        printf("Number must be less than 100\n");
        return 1;
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
    BITMAPFILEHEADER bf, bf_new;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_new = bf;
    

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_new;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_new = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // dimensions
    bi_new.biWidth = bi.biWidth * number;
    bi_new.biHeight = bi.biHeight * number;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) %4;
    
    // size
    bi_new.biSizeImage = (bi_new.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_new.biHeight);
    bf_new.bfSize = (bf.bfSize - bi.biSizeImage) + ((bi_new.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_new.biHeight));

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate scanlines number times
        for(int s = 0; s < number; s++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write new RGB triple to outfile
                for (int n = 0; n<number; n++ )
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // Padding
            for (int p = 0; p < new_padding; p++)
            {
                fputc(0, outptr);
            }
            if(s < number-1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
