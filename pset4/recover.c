/*Marial Gutierrez
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    // open file card.raw (read)
    FILE *in_file = fopen("card.raw", "r");
    if (in_file == NULL)
    {
        printf("could not open file\n");
        return 1;
    }
    
    // Buffer
    uint8_t buffer[512];
    bool found = false;
    
    // set counter to zero for name of files
    int name_file = 0;
    char tittle[8];
    sprintf(tittle, "%.3d.jpg", name_file);
    FILE *out_file = NULL;
    
    // interate throught memory chunks of 512 bytes
    while(fread(&buffer, 512, 1, in_file) != 0)
    {
    
    // check if each block size start with JPGE characteristic
        // Case that we found a JPEG for first time (where found is false)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff 
            && (buffer[3] == 0xe0 || buffer[3] == 0xe1) && found == false)
        {
            found = true;
            out_file = fopen(tittle, "a");
            fwrite(&buffer, 512, 1, out_file);
        }
        
        // Case that we found a JPEG - second time (where found is true)
        else if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff 
                && (buffer[3] == 0xe0 || buffer[3] == 0xe1) && found == true)
        {
            // close first file
            fclose(out_file); 
            name_file++;
            sprintf(tittle, "%.3d.jpg", name_file);
            out_file = fopen(tittle, "a");
            fwrite(&buffer, 512, 1, out_file);            
        }
        
        // Case that we dont found the first 4 characters of JPEG 
        // (but found is true)
        else if(found == true)
        {
            fwrite(&buffer, 512, 1, out_file);
        }
    } 
    // Close last file 
    fclose(out_file); 
}
