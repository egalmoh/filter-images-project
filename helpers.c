#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    // Calculate
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average pixel value
            average =
                ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);

            // Set each color value to average value
            image[i][j].rgbtBlue = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtRed = (int) round(average);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    // Calculate
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average pixel value
            sepiaRed = (float) ((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) +
                                (.189 * image[i][j].rgbtBlue));
            sepiaGreen = (float) ((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) +
                                  (.168 * image[i][j].rgbtBlue));
            sepiaBlue = (float) ((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) +
                                 (.131 * image[i][j].rgbtBlue));

            // Check if they exceed 255 or less than 0
            if (sepiaRed > 255)
            {
                sepiaRed = (float) 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = (float) 0;
            }

            // check for sepie-green
            if (sepiaGreen > 255)
            {
                sepiaGreen = (float) 255;
            }
            else if (sepiaGreen < 0)
            {
                sepiaGreen = (float) 0;
            }
            // Check for sepia-blue
            if (sepiaBlue > 255)
            {
                sepiaBlue = (float) 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = (float) 0;
            }

            // assaigning values to their correct pixels
            image[i][j].rgbtRed = (int) round(sepiaRed);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtBlue = (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpRed;
    int tmpGreen;
    int tmpBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swapping Red
            tmpRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tmpRed;

            // Swapping Green
            tmpGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tmpGreen;

            // Swapping Blue
            tmpBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avRed;
    float avGreen;
    float avBlue;

    // Create a copy of image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Corner pixels
            // // Top-left corner
            if (j == 0 && i == 0)
            {
                avRed = (image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed +
                         image[1][1].rgbtRed) /
                        (float) 4;
                avGreen = (image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen +
                           image[1][1].rgbtGreen) /
                          (float) 4;
                avBlue = (image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue +
                          image[1][1].rgbtBlue) /
                         (float) 4;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // // Bottom-left corner
            else if (i == height - 1 && j == 0)
            {
                avRed = (image[height - 1][0].rgbtRed + image[height - 2][0].rgbtRed +
                         image[height - 2][1].rgbtRed + image[height - 1][1].rgbtRed) /
                        (float) 4;
                avGreen = (image[height - 1][0].rgbtGreen + image[height - 2][0].rgbtGreen +
                           image[height - 2][1].rgbtGreen + image[height - 1][1].rgbtGreen) /
                          (float) 4;
                avBlue = (image[height - 1][0].rgbtBlue + image[height - 2][0].rgbtBlue +
                          image[height - 2][1].rgbtBlue + image[height - 1][1].rgbtBlue) /
                         (float) 4;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // // Bottom-right corner
            else if (i == height - 1 && j == width - 1)
            {
                avRed =
                    (image[height - 1][width - 1].rgbtRed + image[height - 2][width - 1].rgbtRed +
                     image[height - 2][width - 2].rgbtRed + image[height - 1][width - 2].rgbtRed) /
                    (float) 4;
                avGreen = (image[height - 1][width - 1].rgbtGreen +
                           image[height - 2][width - 1].rgbtGreen +
                           image[height - 2][width - 2].rgbtGreen +
                           image[height - 1][width - 2].rgbtGreen) /
                          (float) 4;
                avBlue =
                    (image[height - 1][width - 1].rgbtBlue + image[height - 2][width - 1].rgbtBlue +
                     image[height - 2][width - 2].rgbtBlue +
                     image[height - 1][width - 2].rgbtBlue) /
                    (float) 4;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // // Top-right corner
            else if (i == 0 && j == width - 1)
            {
                avRed = (image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed +
                         image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed) /
                        (float) 4;
                avGreen = (image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen +
                           image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen) /
                          (float) 4;
                avBlue = (image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue +
                          image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue) /
                         (float) 4;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // Edge pixels
            // // Top row pixels
            else if (i == 0 && j > 0 && j < width - 1)
            {
                avRed = (image[0][j].rgbtRed + image[0][j - 1].rgbtRed + image[0][j + 1].rgbtRed +
                         image[1][j].rgbtRed + image[1][j - 1].rgbtRed + image[1][j + 1].rgbtRed) /
                        (float) 6;
                avGreen = (image[0][j].rgbtGreen + image[0][j - 1].rgbtGreen +
                           image[0][j + 1].rgbtGreen + image[1][j].rgbtGreen +
                           image[1][j - 1].rgbtGreen + image[1][j + 1].rgbtGreen) /
                          (float) 6;
                avBlue =
                    (image[0][j].rgbtBlue + image[0][j - 1].rgbtBlue + image[0][j + 1].rgbtBlue +
                     image[1][j].rgbtBlue + image[1][j - 1].rgbtBlue + image[1][j + 1].rgbtBlue) /
                    (float) 6;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // // Left column pixels
            else if (i > 0 && i < height - 1 && j == 0)
            {
                avRed = (image[i][0].rgbtRed + image[i - 1][0].rgbtRed + image[i + 1][0].rgbtRed +
                         image[i][1].rgbtRed + image[i - 1][1].rgbtRed + image[i + 1][1].rgbtRed) /
                        (float) 6;
                avGreen = (image[i][0].rgbtGreen + image[i - 1][0].rgbtGreen +
                           image[i + 1][0].rgbtGreen + image[i][1].rgbtGreen +
                           image[i - 1][1].rgbtGreen + image[i + 1][1].rgbtGreen) /
                          (float) 6;
                avBlue =
                    (image[i][0].rgbtBlue + image[i - 1][0].rgbtBlue + image[i + 1][0].rgbtBlue +
                     image[i][1].rgbtBlue + image[i - 1][1].rgbtBlue + image[i + 1][1].rgbtBlue) /
                    (float) 6;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // // Bottom row pixels
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                avRed = (image[height - 1][j].rgbtRed + image[height - 1][j - 1].rgbtRed +
                         image[height - 1][j + 1].rgbtRed + image[height - 2][j].rgbtRed +
                         image[height - 2][j - 1].rgbtRed + image[height - 2][j + 1].rgbtRed) /
                        (float) 6;
                avGreen =
                    (image[height - 1][j].rgbtGreen + image[height - 1][j - 1].rgbtGreen +
                     image[height - 1][j + 1].rgbtGreen + image[height - 2][j].rgbtGreen +
                     image[height - 2][j - 1].rgbtGreen + image[height - 2][j + 1].rgbtGreen) /
                    (float) 6;
                avBlue = (image[height - 1][j].rgbtBlue + image[height - 1][j - 1].rgbtBlue +
                          image[height - 1][j + 1].rgbtBlue + image[height - 2][j].rgbtBlue +
                          image[height - 2][j - 1].rgbtBlue + image[height - 2][j + 1].rgbtBlue) /
                         (float) 6;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // // Right column pixels
            else if (i > 0 && i < height - 1 && j == width - 1)
            {
                avRed = (image[i][width - 1].rgbtRed + image[i - 1][width - 1].rgbtRed +
                         image[i + 1][width - 1].rgbtRed + image[i][width - 2].rgbtRed +
                         image[i - 1][width - 2].rgbtRed + image[i + 1][width - 2].rgbtRed) /
                        (float) 6;
                avGreen = (image[i][width - 1].rgbtGreen + image[i - 1][width - 1].rgbtGreen +
                           image[i + 1][width - 1].rgbtGreen + image[i][width - 2].rgbtGreen +
                           image[i - 1][width - 2].rgbtGreen + image[i + 1][width - 2].rgbtGreen) /
                          (float) 6;
                avBlue = (image[i][width - 1].rgbtBlue + image[i - 1][width - 1].rgbtBlue +
                          image[i + 1][width - 1].rgbtBlue + image[i][width - 2].rgbtBlue +
                          image[i - 1][width - 2].rgbtBlue + image[i + 1][width - 2].rgbtBlue) /
                         (float) 6;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }

            // Interior pixels
            else
            {
                // Calculating average for Red
                avRed = (float) (image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                 image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                 image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                 image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                 image[i + 1][j + 1].rgbtRed) /
                        9;

                // Calculating average for Green
                avGreen = (float) (image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                   image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                   image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                   image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                   image[i + 1][j + 1].rgbtGreen) /
                          9;

                // Calculating average for Blue
                avBlue = (float) (image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                  image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                  image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                  image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                  image[i + 1][j + 1].rgbtBlue) /
                         9;

                // RGB equals average values
                copy[i][j].rgbtRed = (int) round(avRed);
                copy[i][j].rgbtGreen = (int) round(avGreen);
                copy[i][j].rgbtBlue = (int) round(avBlue);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
