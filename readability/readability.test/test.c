//Libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


//Declared Functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);



int main(void)
{
    //Obtain text from user
    string text = get_string ("Please submit text to analyze: ");
    //Define a variable with the declared function count_letters
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    printf("Your text has: %i letters\n", letters);
    printf("Your text has: %i words\n", words);
    printf("Your text has: %i sentences\n", sentences);
}



int count_letters(string text)
{
    //set variable to 0
    int letters = 0;

    //Repeat action for the length of the string text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //if it's a letter, add a point
        if (isalpha(text[i]))
        {
            letters++;
        }
        //If it's not a letter, do not add points
        else
        {
            letters += 0;
        }

    }
    //Give me the total
    return letters;
}


int count_words(string text)
{
    //set variable to 0
    int words = 0;

    //a. If first character is alphabetical, add one
    if (isalpha(text[0]))
    {
            words++;
    }
    //If it's not, do not add points
    else
    {
            words += 0;
    }

    //b. Repeat following action for the length of the string text
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //if it's a space, add a point
        if (isspace(text[i]))
        {
            words++;
        }
        //If it's not a space, do not add points
        else
        {
            words += 0;
        }

    }

    //Give me the total
    return words;
}

int count_sentences(string text)
{
    //set variable to 0
    int sentences = 0;

    //Repeat following action for the length of the string text:
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //if it's a question mark or an exclamation point or a period, add one to counter
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            sentences++;
        }
        //If it's not, do not add points
        else
        {
            sentences += 0;
        }

    }

    //Give me the total
    return sentences;
}