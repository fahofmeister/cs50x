#include "helpers.h"
#include <math.h>

// User defined functions
int averagePixel(int len, int arr[]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Retrieving pixel color
            float red = image[row][col].rgbtRed;
            float green = image[row][col].rgbtGreen;
            float blue = image[row][col].rgbtBlue;

            // Calculates the average gray pixel value
            int gray = round((red + green + blue) / 3);

            // Assign the new value to the pixel
            image[row][col].rgbtRed = gray;
            image[row][col].rgbtGreen = gray;
            image[row][col].rgbtBlue = gray;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Retrieving pixel color
            float red = image[row][col].rgbtRed;
            float green = image[row][col].rgbtGreen;
            float blue = image[row][col].rgbtBlue;

            // Calculates the new red pixel value for sepia
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);

            // Calculates the new green pixel value for sepia
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);

            // Calculates the new blue pixel value for sepia
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            // Cap pixel values to maximum 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Assign the new value to the pixel
            image[row][col].rgbtRed = sepiaRed;
            image[row][col].rgbtGreen = sepiaGreen;
            image[row][col].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            // Swaping each pixel for its opposite
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy blurred image version
    RGBTRIPLE blurImg[height][width];

    // Calculate each blurred pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Number of pixels to get values
            int nPixels;

            if ((row == 0 || row == height - 1) && (col == 0 || col == width - 1))
            {
                // Corner cases
                nPixels = 4;
            }
            else if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
            {
                // Edge cases
                nPixels = 6;
            }
            else
            {
                // Middle pixels
                nPixels = 9;
            }

            // Arrays to save the pixel color values
            int red[nPixels];
            int green[nPixels];
            int blue[nPixels];

            // Variable to store array position
            int pxl = 0;

            // Loop to get each pixel color value into the array
            for (int boxRow = row - 1; boxRow <= row + 1; boxRow++)
            {
                for (int boxCol = col - 1; boxCol <= col + 1; boxCol++)
                {
                    if (boxRow >= 0 && boxRow < height && boxCol >= 0 && boxCol < width)
                    {
                        red[pxl] = image[boxRow][boxCol].rgbtRed;
                        green[pxl] = image[boxRow][boxCol].rgbtGreen;
                        blue[pxl] = image[boxRow][boxCol].rgbtBlue;

                        pxl++;
                    }
                }
            }

            // Saving the average value into the blur copy
            blurImg[row][col].rgbtRed = averagePixel(nPixels, red);
            blurImg[row][col].rgbtGreen = averagePixel(nPixels, green);
            blurImg[row][col].rgbtBlue = averagePixel(nPixels, blue);
        }
    }

    // Replace the original pixels for the blurred pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = blurImg[row][col];
        }
    }

    return;
}

// Average the values in an array
int averagePixel(int len, int arr[])
{
    float sum = 0;

    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }

    return round(sum / len);
}