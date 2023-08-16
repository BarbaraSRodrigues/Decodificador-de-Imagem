/*---------------------------------------------------------
 *              UNIFAL - Universidade Federal de Alfenas.
 *                  BACHARELADO EM CIENCIA DA COMPUTACAO.
 * Trabalho...: Esteganografia
 * Disciplina.: Processamento de Imagens
 * Professor..: Luiz Eduardo da Silva
 * Aluna......: Barbara Silveira Rodrigues
 * Data.......: 04/07/2023
 *---------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "imagelib.h"
#define DEBUG(x) x

// Function to concatenate binary numbers
int concatenation(int binary, int lastBit){
    binary = (binary << 1) | lastBit;
}

void decode(image In)
{
    FILE *file;
    char name[100] = "";
    int fsize = 0;
    unsigned char byte;
    int binR, binG, binB;
    int concat = 0;
    int count = 0;
    int banda = 0, i; // Banda is the RGB color model. R=0, G=1, B=2

    // Decode the name
    for(i = 0; i < In->nr*In->nc; i++){
        // banda is not inside the parameter
        if(banda == 3)
            banda = 0; // Variable banda goes back to R

        // Switch case to know which band to concatenate
        switch(banda){

            case 0: // Uses the binary of R
                binR = (In->px[i] >> 16) & 0x01; // Get the least significant bit 
                concat = concatenation(concat, binR); // Concatenate the bit
                count++;
            break;    
            case 1: // Uses the binary of G
                binG = (In->px[i] >> 8) & 0x01;
                concat = concatenation(concat, binG);
                count++;
            break;
            case 2: // Uses the binary of B
                binB = In->px[i] & 0x01;
                concat = concatenation(concat, binB);
                count++;
            break;
        }

        if(count == 8){ // 8 = full binary number
            count = 0;
            name[strlen(name)] = (char)concat; 
            if((char)concat == '\0') // Found the end of the coded name
                break;
        }
        
        banda++; // Goes to the next
    }
    name[strlen(name)] = '\0'; // End the string 
    printf("File name: %s\n", name);

    // Synch all the variables used for index
    banda++; 
    i++;
    concat = 0; // concat starts all over again 

     // Decode the file size
    for(int j = 0;j < 32; j++, i++){
        if(banda == 3)
            banda = 0;

        switch(banda){

            case 0: 
                binR = (In->px[i] >> 16) & 0x01;
                concat = concatenation(concat, binR);
                count++;
            break;    
            case 1: 
                binG = (In->px[i] >> 8) & 0x01;
                concat = concatenation(concat, binG);
                count++;
            break;
            case 2: 
                binB = In->px[i] & 0x01;
                concat = concatenation(concat, binB);
                count++;
            break;
        }
        banda++;
    }
    fsize = concat; // fsize receives the full concatenated binary
    printf("File size: %d\n" ,fsize);
    
    // Decode the rest of the file

    // Create the file
    file = fopen(name, "wb");
        if(!file){
            printf("Cannot open file.\n");
            exit(10);
        }

    concat = 0;

    // Travel all of the rest of the file
    while(fsize){
        for(int j = 0; j <= 7; j++, i++){
            if(banda >= 3)
                banda = 0; // Variable banda goes back to R

            switch(banda){

                case 0: 
                    binR = (In->px[i] >> 16) & 0x01;
                    concat = concatenation(concat, binR);
                    count++;
                break;    
                case 1: 
                    binG = (In->px[i] >> 8) & 0x01;
                    concat = concatenation(concat, binG);
                    count++;
                break;
                case 2: 
                    binB = In->px[i] & 0x01;
                    concat = concatenation(concat, binB);
                    count++;
                break;
            }
            banda++; 
        }
        // Write the byte to the new file
        byte = (unsigned char)concat; 
        fprintf(file, "%c", byte);

        //Synch again
        concat = 0;
        
        fsize--;
    }
}

void msg(char *s)
{
    printf("\nSteganography - decode");
    printf("\n-------------------------------");
    printf("\nUSE.:  %s  <IMG.PPM>", s);
    printf("\nWhere:\n");
    printf("    <IMG.PPM>  Image file in PPM ASCII format\n\n");
    exit(20);
}

/*-----------------------------------------
  Main program
------------------------------------------*/
int main(int argc, char *argv[])
{
    // Variables used
    char name[100];
    image In;
    char *p;

    // Checks if the args was given correctly
    if (argc < 2)
        msg(argv[0]);
    
    // Create the image
    strcpy(name, argv[1]);
    p = strstr(name, ".ppm");
    if (p)
        *p = 0;
    strcat(name, ".ppm");
    In = img_get(name, COLOR);

    // Decode function to decode the coded file given in args
    decode(In);

    // Free the image
    img_free(In);
    return 0;
}
