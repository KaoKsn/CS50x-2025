#include "helpers.h"
#include <math.h>

/* The BITMAPFILEHEADER and BITMAPINFOHEADER will be copied into the output .bmp file for us by
 * filter.c */

/* To convert an image to greyscale you need to have equal amounts of green,blue and red */
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Ensure proper rounding off and avoid truncation */
            average = (BYTE) round(
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

/* Convert an image with the sepia filter
 * Applying sepia makes the image have a reddish brown filter giving it a old time feel
 * Use the sepia algorithm to turn the pixels to their sepia equivalents.
 */
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    uint16_t sepiaRed, sepiaBlue, sepiaGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Avoid truncation and ensure proper round off. */
            sepiaRed =
                (uint16_t) round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen +
                                 0.189 * image[i][j].rgbtBlue);
            sepiaGreen =
                (uint16_t) round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen +
                                 0.168 * image[i][j].rgbtBlue);
            sepiaBlue =
                (uint16_t) round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen +
                                 0.131 * image[i][j].rgbtBlue);

            /* Ensure that the new values lie within 256 */
            sepiaBlue = fmin(255, sepiaBlue);
            sepiaGreen = fmin(255, sepiaGreen);
            sepiaRed = fmin(255, sepiaRed);

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /* To reflect an image horizontally we need to reverse the array of pixels in each row */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

/* Box Blur Filter
 * In order to blur an image we typically average out the surrouding pixels
 * and provide the average value to the current pixel.
 */
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* Create a copy of image on which operations are to be done to affect the original image */
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Ensure proper roundoff and avoid truncation */
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtBlue =
                    (BYTE) round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                  copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                 4.0);
                image[i][j].rgbtGreen =
                    (BYTE) round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                  copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                                 4.0);
                image[i][j].rgbtRed =
                    (BYTE) round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                  copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                 4.0);
            }
        }
    }
    return;
}

/* Some other implementations for fun
    1. Mirroring the image about one half horizontally.
    void mirror(int height, int widht, RGBTRIPLE image[height][width])
    {
    for(int i = 0; i< height; i++)
        {
            for(int j = 0; j< width/2 ; j++)
            {
                image [i][j] = image[i][width-j-1];
            }
        }
        return;
    }
*/
