#include "helpers.h"
#include <math.h>

/* In each case don't forget to roundoff to the nearest integer
 ****** Don't allow implicit truncation *******
 */

/* Convert the image into greyscale
 * Find the average of the values of r,g and b.
 * Assign the average value to each color giving it the required intensity of grey
 */
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = (BYTE) round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

/* To reflect image horizontally,
 * go through each and every pixel and then flip the array of pixels
 */
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            /* Flip the current pixel with the respective pixel from the end */
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

/* Box Blurring an image */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* Creating a copy of the image is very essential as we manipulate the pixels */
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    /* Go through every pixel one by one */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Create a 3*3 matrix keeping the current pixel at position (1,1) */
            int totalBlue = 0, totalGreen = 0, totalRed = 0, counter = 0;
            for (int gi = -1; gi <= 1; gi++)
            {
                for (int gj = -1; gj <= 1; gj++)
                {
                    int ni = gi + i, nj = gj + j;
                    /* Validate the index for bounds of array */
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        /* Find the average blue by adding all the blues values of the neighboring
                         * valid pixels */
                        totalBlue += copy[ni][nj].rgbtBlue;
                        totalGreen += copy[ni][nj].rgbtGreen;
                        totalRed += copy[ni][nj].rgbtRed;
                        counter++;
                    }
                }
            }
            image[i][j].rgbtBlue = (BYTE) round(totalBlue / (float) counter);
            image[i][j].rgbtGreen = (BYTE) round(totalGreen / (float) counter);
            image[i][j].rgbtRed = (BYTE) round(totalRed / (float) counter);
        }
    }
    return;
}

/* Detect edges using Sobel's Edge Detection Algorithm */

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /* Copying the array of pixels into another array */
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    /* Defining the required matrices */
    int Sobel_Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Sobel_Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx[3] = {0}, Gy[3] = {0};
            // Resetting is very important as Gx and Gy's are different for each pixel.

            /* Manipulating each pixel by creating a grid of 3*3
             * with pixel(i,j) as the centre of the 3*3 matrix
             * i.e the element at position (1,1)
             */
            for (int gi = -1, k = 0; gi <= 1; gi++, k++)
            {
                for (int gj = -1, l = 0; gj <= 1; gj++, l++)
                {
                    int ni = gi + i, nj = gj + j;

                    /* Checking for the validity of the index */
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        Gx[0] += copy[ni][nj].rgbtBlue * Sobel_Gx[k][l];
                        Gx[1] += copy[ni][nj].rgbtGreen * Sobel_Gx[k][l];
                        Gx[2] += copy[ni][nj].rgbtRed * Sobel_Gx[k][l];

                        Gy[0] += copy[ni][nj].rgbtBlue * Sobel_Gy[k][l];
                        Gy[1] += copy[ni][nj].rgbtGreen * Sobel_Gy[k][l];
                        Gy[2] += copy[ni][nj].rgbtRed * Sobel_Gy[k][l];
                    }
                }
            }

            /* The resultant = sqrt(Gx[i]*Gx[i] + Gy[i]*Gy[i])
             can be > 0xff(255) */

            image[i][j].rgbtBlue = (BYTE) round(fmin(sqrt(Gx[0] * Gx[0] + Gy[0] * Gy[0]), 0xff));
            image[i][j].rgbtGreen = (BYTE) round(fmin(sqrt(Gx[1] * Gx[1] + Gy[1] * Gy[1]), 0xff));
            image[i][j].rgbtRed = (BYTE) round(fmin(sqrt(Gx[2] * Gx[2] + Gy[2] * Gy[2]), 0xff));
        }
    }
    return;
}

/* Just for fun:
    1.Flipping the image vertically
void(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0;i<height/2;i++)
    {
        for(int j = 0 ;j< width ;j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[height - i - 1][j];
            image[height - i - 1][j] = temp;
        }
    }
    return;
}
    2. Mirror image horizontal.
void(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0;i<height;i++)
    {
        for(int j = 0 ;j< width/2 ;j++)
        {
            image[i][j] = image[i][width - j - 1];
        }
    }
    return;
}
    3. Mirror image vertical.
void(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0;i<height/2;i++)
    {
        for(int j = 0 ;j< width ;j++)
        {
            image[i][j] = image[height - i - 1][j];
        }
    }
    return;
}
*/
