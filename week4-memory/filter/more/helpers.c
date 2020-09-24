// Unfinished code.

#include "helpers.h"
#include <math.h>

// User defined functions
int averagePixel(int len, int arr[]);
void getSobelSquare(RGBTRIPLE *square, RGBTRIPLE *image, int row, int col);

// Define a new format
typedef struct{
    int dx;
    int dy;
}
sobel;

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Pictures with edge detected
    RGBTRIPLE edgeImg[height][width];
    RGBTRIPLE sobelSquare[3][3];
    sobel diffs[3][3];
    sobel kernel[3][3];

    // Populating diffs array
    for (int boxRow = 0; boxRow < 3; boxRow++)
    {
        for (int boxCol = 0; boxCol < 3; boxCol++)
        {
            diffs[boxRow][boxCol].dx = boxRow - 1;
            diffs[boxRow][boxCol].dy = boxCol - 1;
        }
    }

    // Populating kernel array
    for (int boxRow = 0; boxRow < 3; boxRow++)
    {
        for (int boxCol = 0; boxCol < 3; boxCol++)
        {
            // Fill the kernel matrix
        }
    }

    // Calculate each edge pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            for (int boxRow = 0; boxRow < 3; boxRow++)
            {
                for (int boxCol = 0; boxCol < 3; boxCol++)
                {
                    sqRow = row + diffs[boxRow][boxCol];
                    sqCol = col + diffs[boxRow][boxCol];

                    if (sqRow < 0 || sqRow > height - 1 || sqCol < 0 || sqCol > width - 1)
                    {
                        // If edges of image, just a black pixel
                        sobelSquare[boxRow][boxCol].rgbtRed = 0;
                        sobelSquare[boxRow][boxCol].rgbtGreen = 0;
                        sobelSquare[boxRow][boxCol].rgbtBlue = 0;
                    }
                    else
                    {
                        // If middle of image, copy the values
                        sobelSquare[boxRow][boxCol].rgbtRed = image[sqRow][sqCol].rgbtRed;
                        sobelSquare[boxRow][boxCol].rgbtGreen = image[sqRow][sqCol].rgbtGreen;
                        sobelSquare[boxRow][boxCol].rgbtBlue = image[sqRow][sqCol].rgbtBlue;
                    }
                }
            }



        }
    }

    // Replace the original pixels for the edge pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = edgeImg[row][col];
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
