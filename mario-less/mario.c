#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        //Will ask for the Size of the Pyramid until the number is smaller than 1 or bigger than 8
        n = get_int("Size of Pyramid = ");
    }
    while (n < 1 || n > 8);

//This is for the Pyramid construction itself

//Rows (n size)
    for (int i = 0; i < n; i++)
    {
//a: for spaces, equals the height, minus 1 and minus i (i starts at 0)
        for (int k = 0; k < n - (i + 1); k++)
        {
            printf(" ");
        }
//b: for hashes
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //Break line
        printf("\n");
    }
}