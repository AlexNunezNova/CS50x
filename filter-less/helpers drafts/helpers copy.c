//libraries to add
#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column to go pixel by pixel
        for (int j = 0; j < width; j++)
        {
            //set values of separate colors in separate variables
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            //set gray tone as the average of RGB (it may have decimals, therefore it must be a float)
            float graytone = ((red + green + blue) / 3);
            //round the average
            graytone = round(graytone);
            //apply number to all RGB
            image[i][j].rgbtRed = graytone;
            image[i][j].rgbtGreen = graytone;
            image[i][j].rgbtBlue = graytone;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column to go pixel by pixel
        for (int j = 0; j < width; j++)
        {
            //set values of separate colors in separate variables
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            //set sepia tone with the given formula for each color
            float sepiaR = 0.393 * red + 0.769 * green + 0.189 * blue;
            float sepiaG = 0.349 * red + 0.686 * green + 0.168 * blue;
            float sepiaB = 0.272 * red + 0.534 * green + 0.131 * blue;

            //round the results
            int sepiaRed = round(sepiaR);
            int sepiaGreen = round(sepiaG);
            int sepiaBlue = round(sepiaB);

            //if exceed number 255, cut to 255
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

            //apply number to all RGB
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
        //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column to go pixel by pixel
        //but, to avoid losing the first half of pixels, use temporary variable
        for (int j = 0; j < width / 2; j++)
        {
            //set an extra variable to allow swap and invert the position of each pixel
            RGBTRIPLE tempimage = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = tempimage;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //1. set a copy image to keep a track of original colors
    RGBTRIPLE copyimage[height][width];
        //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column to copy image pixel by pixel
        for (int j = 0; j < width; j++)
        {
            copyimage[i][j] = image[i][j];
        }
    }

    //2. Read pixel average and write in image
    for (int i = 0; i < height; i++)
    {
        //loop over each column to go pixel by pixel
        for (int j = 0; j < width; j++)
        {
            //2.1 first, set a counter to determine how many pixels for the average
            int totalPixels = 0;

            //2.2 then, set a counter for the sum of the values for each color
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;

            //2.3 then, go pixel by pixel with an if statement to check if the pixel exists (9 ifs)
            //if it exists, add the values to the sum

            //pixel [i - 1][j - 1] (upper left corner)
            //must check that row is at least 0 and column is at least 0
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sumRed += copyimage[i - 1][j - 1].rgbtRed;
                sumBlue += copyimage[i - 1][j - 1].rgbtBlue;
                sumGreen += copyimage[i - 1][j - 1].rgbtGreen;
                totalPixels++;
            }

            //pixel [i - 1][j] (up)
            //must check that row[i] is at least 0
            if (i - 1 >= 0)
            {
                sumRed += copyimage[i - 1][j].rgbtRed;
                sumBlue += copyimage[i - 1][j].rgbtBlue;
                sumGreen += copyimage[i - 1][j].rgbtGreen;
                totalPixels++;
            }

            //pixel [i - 1][j + 1] (upper right corner)
            //must check that row is at least 0 and column is smaller than width
            if (i - 1 >= 0 && j + 1 < width)
            {
                sumRed += copyimage[i - 1][j + 1].rgbtRed;
                sumBlue += copyimage[i - 1][j + 1].rgbtBlue;
                sumGreen += copyimage[i - 1][j + 1].rgbtGreen;
                totalPixels++;
            }

            //pixel [i][j - 1] (left)
            //must check column is at least 0
            if (j - 1 >= 0)
            {
                sumRed += copyimage[i][j - 1].rgbtRed;
                sumBlue += copyimage[i][j - 1].rgbtBlue;
                sumGreen += copyimage[i][j - 1].rgbtGreen;
                totalPixels++;
            }

            //pixel [i][j + 1] (right)
            //must check that column is smaller than width
            if (j + 1 < width)
            {
                sumRed += copyimage[i][j + 1].rgbtRed;
                sumBlue += copyimage[i][j + 1].rgbtBlue;
                sumGreen += copyimage[i][j + 1].rgbtGreen;
                totalPixels++;
            }

            //pixel [i + 1][j - 1] (down left corner)
            //must check that row is smaller than height and column is at least 0
            if (i + 1 < height && j - 1 >= 0)
            {
                sumRed += copyimage[i + 1][j - 1].rgbtRed;
                sumBlue += copyimage[i + 1][j - 1].rgbtBlue;
                sumGreen += copyimage[i + 1][j - 1].rgbtGreen;
                totalPixels++;
            }

            //pixel [i + 1][j] (down)
            //must check that row is smaller than height
            if (i + 1 < height)
            {
                sumRed += copyimage[i + 1][j].rgbtRed;
                sumBlue += copyimage[i + 1][j].rgbtBlue;
                sumGreen += copyimage[i + 1][j].rgbtGreen;
                totalPixels++;
            }

            //pixel [i + 1][j + 1] (down right corner)
            //must check that row is smaller than height and column is smaller than width
            if (i + 1 < height && j + 1 < width)
            {
                sumRed += copyimage[i + 1][j + 1].rgbtRed;
                sumBlue += copyimage[i + 1][j + 1].rgbtBlue;
                sumGreen += copyimage[i + 1][j + 1].rgbtGreen;
                totalPixels++;
            }

            //central pixel
            //as it exists, if statement is not necessary
            sumRed += copyimage[i][j].rgbtRed;
            sumBlue += copyimage[i][j].rgbtBlue;
            sumGreen += copyimage[i][j].rgbtGreen;
            totalPixels++;

            //2.4 having the total, we can obtain the average
            int averageRed = round(sumRed / totalPixels);
            int averageBlue = round(sumBlue / totalPixels);
            int averageGreen = round(sumGreen / totalPixels);

            //2.5 with the given averages, assign to the image pixel (not the copy)
            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
    return;
}
