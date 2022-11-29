// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // 1: Copy header from input file to output file

    // 1.1 Create array of bytes for the header, which is a constant
    uint8_t header_array[HEADER_SIZE];

    // 1.2 Create operations of reading and writing header
    fread(&header_array, HEADER_SIZE, 1, input);
    fwrite(&header_array, HEADER_SIZE, 1, output);

    // 2: Read samples from input file and write updated data to output file

    // 2.1 Create buffer variable to store audio
    int16_t buffer;

    //2.2 create loop to read and write samples, one by one until EOF
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        //Change volume (considering factor) and write each sample into the output
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);

    }

    // Close files
    fclose(input);
    fclose(output);
}
