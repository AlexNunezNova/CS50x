//libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//declared functions
bool digitcheck(string key);
char rotate(char c, int keynumber);

int main (void)
{
    char c = get_char("insert your char: ");
    int keynumber = 28;
    if(isalpha(c))
    {
        printf("%c\n", c + keynumber%26);
    }
    else
    {
        printf("%c", c);
    }
}