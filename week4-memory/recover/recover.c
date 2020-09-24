#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

bool checkJPG(unsigned char buffer[512]);

int main(int argc, char *argv[])
{
    // Check for arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file - based in Week 4 example code
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open the file.\n");
        return 1;
    }

    // Setting variables
    unsigned char buffer[512];
    int fileStream = 0;
    int nImg = 0;
    bool jpgFile = false;
    char *filename = malloc(8 * sizeof(char));
    FILE *img;

    // Repeat until end of file
    while (true)
    {
        // Saving the return value from fread
        fileStream = fread(buffer, 512, 1, file);

        // Sentinel for the end of file
        if (fileStream != 1)
        {
            break;
        }

        // Check if buffer contain a JPEG header file
        if (checkJPG(buffer))
        {
            jpgFile = true;
            if (nImg == 0)
            {
                sprintf(filename, "%03i.jpg", nImg);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", nImg);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }

            nImg++;
        }
        else if (jpgFile)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    // Free the memory
    free(filename);
    fclose(img);
    fclose(file);
    printf("I found %i JPG files\n", nImg);
}

// Function to check if header is from a JPG file
bool checkJPG(unsigned char buffer[512])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}
