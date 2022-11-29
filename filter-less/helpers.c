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

    //2. Do a loop pixel by pixel again
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //2.1 Set variables for storing values of RGB, and a counter for the total of pixels considered
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float totalPixels = 0.0;

            //2.2 Once each pixel is taken individually, consider the 3x3 grid surrounding it
            //create a double-for loop to focus on this 3x3 pixel grid

            //for rows, go from i-1 to i+1 (3 places)
            for (int row = i - 1; row <= i + 1; row++)
            {
                //for columns, from j-1 to j+1
                for (int col = j - 1; col <= j + 1; col++)
                {
                    //check if every pixel in this grid exists (must not exceed image limits)
                    if (col >= 0 && col <= width - 1 && row >= 0 && row <= height - 1)
                    {
                        //collect amount of RGB from each existing pixel and add 1 to counter
                        sumRed += copyimage[row][col].rgbtRed;
                        sumGreen += copyimage[row][col].rgbtGreen;
                        sumBlue += copyimage[row][col].rgbtBlue;
                        totalPixels++;
                    }
                }
            }
            //3. Once done with the 3x3 looping, assign RGB as an average of existing pixels (original image)
            image[i][j].rgbtRed = round(sumRed / totalPixels);
            image[i][j].rgbtGreen = round(sumGreen / totalPixels);
            image[i][j].rgbtBlue = round(sumBlue / totalPixels);

        }
    }
}
