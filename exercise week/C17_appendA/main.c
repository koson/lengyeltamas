#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char appendA(char testSentence)
{
    char *result = testSentence;
    char *A = "a";
    strcat(result, testSentence);
    strcat(result, A);
    return result;
}

int main()
{
    // Create a program which asks for a string and stores it
    // Create a function which takes a string as a parameter and
    // appends a character 'a' to the end of it and returns the new string

    puts("Tell me something");
    char sentence[100];
    gets(sentence);
    puts(appendA(sentence));

    return 0;
}