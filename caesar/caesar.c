//libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//declared functions
bool digitcheck(string key);
char rotate(char c, int keynumber);


int main(int argc, string argv[])
{
    //First, create a validation method
    //The string element is located at argv[1] and it must be a digit (ideally positive integer)
    //This is the key, that should be transformed into an integer, and it moves the letters n times
    //Then the program asks for text.
    //The program prints back the text ciphered with each letter (not character) moving n times further in the alphabet.



    //Validation with conditional to verify: only one command-line argument, and only digits in argv[1]
    if (argc == 2 && digitcheck(argv[1]))
    {
        //If both conditions are met, then turn string key into an integer
        int cipherkey = atoi(argv[1]);

        //Now we can ask the user for the text to cipher
        string originaltext = get_string("Please insert your text:");

        //Then iterate each caracter of the text with the cipher method (rotation), to obtain the ciphered text
        printf("ciphertext: ");
        for (int i = 0, n = strlen(originaltext); i < n; i++)
        {
            char ciphertext = rotate(originaltext[i], cipherkey);
            printf("%c", ciphertext);
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


}



//Functions to develop:

//a.- Digit Validation
bool digitcheck(string key)
{
    //Set a counter to verify that all elements are digits
    int counter = 0;

    //Look at every character one by one and check if it is a digit
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isdigit(key[i]))
        {
            counter++;
        }
    }

    //if all are digits, return true. Otherwise, return false
    if (counter == strlen(key))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//b.- Cipher method (rotation)
char rotate(char c, int keynumber)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            //Use function to shift from ASCII index (65+) to alphabetical index (0+), substracting A or a
            char upperc = c - 'A';

            //After obtaining the rotation in the alphabet, take back to ASCII
            return (upperc + keynumber) % 26 + 'A';
        }
        else
        {
            char lowerc = c - 'a';

            return (lowerc + keynumber) % 26 + 'a';
        }
    }
    else
    {
        return c;
    }
}