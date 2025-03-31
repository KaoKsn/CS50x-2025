/* A C program that can change the volume of a given .wav file */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int8_t BYTE;
typedef int16_t SAMPLE_SIZE;

#define INPUT_FILE_DOES_NOT_EXIST 4041
#define OUTPUT_FILE_DOES_NOT_EXIST 4042
#define HEADER_SIZE 44

/* Input type: ./volume input.wav output.wav factor */
int main(int argc, char *argv[])
{
    /* Validate command line arguments */
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    /* Opening the input .wav file */
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open the input file.\n");
        return INPUT_FILE_DOES_NOT_EXIST;
    }
    /* Opening the output file in the write mode */
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open output file.\n");
        return OUTPUT_FILE_DOES_NOT_EXIST;
    }

    /* Check the validity of factor */
    float factor = atof(argv[3]);
    if (factor < 0)
    {
        /* A negative factor shifts the phase which cannot be */
        factor = -factor;
    }

    /* Copy header from input file to output file
     * The header contains 44 bytes of main information regarding the wave file
     */

    /* Read the header of the input wave file and write it as it is into the required output wave
     * file */
    BYTE header_byte[44];

    fread(header_byte, sizeof(BYTE), 44, input);
    fwrite(header_byte, sizeof(BYTE), 44, output);


    /* fread() is able to track the byte that it is reading */
    SAMPLE_SIZE sample;

    /* Multiply the values in the sample by the value of factor */
    while (fread(&sample, sizeof(sample), 1, input) != 0)
    {
        /* bytes read from the input file are stored in the variable sample */
        sample *= factor;
        fwrite(&sample, sizeof(sample), 1, output);
    }

    /* free dynamically allocated memory */


    /* Close files */
    fclose(input);
    fclose(output);
}
