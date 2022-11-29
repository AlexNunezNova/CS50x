//Libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


//Declared Functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau(int letters, int words, int sentences);



int main(void)
{
    //Obtain text from user
    string text = get_string("Please submit text to analyze: ");
    //Define variables to use with declared functions
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int final_index = coleman_liau(letters, words, sentences);

    //Print index results
    if (final_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", final_index);
    }

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


int coleman_liau(int letters, int words, int sentences)
{
    //Calculate index, converting int into floats
    float letters_f = (float)letters;
    float words_f = (float)words;
    float sentences_f = (float)sentences;

    float index = ((letters_f * 100 / words_f) * 0.0588) - ((sentences_f * 100 / words_f) * 0.296) - 15.8;

    //round index
    int round_index = round(index);

    return round_index;
}