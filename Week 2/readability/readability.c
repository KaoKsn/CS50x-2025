#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLEMAN_LIAU_L 0.0588
#define COLEMAN_LIAU_S 0.296
#define COLEMAN_LIAU_CONSTANT 15.8

int calculateReadingLevel(string);
void displayReadingLevel(int);

int main(void)
{
    string text = get_string("Text: ");

    /* Assessing the input text */
    int readingLevel = calculateReadingLevel(text);

    displayReadingLevel(readingLevel);
}

int calculateReadingLevel(string text)
{
    /* readingLevel = 0.0588 * L - 0.296 * S - 15.8
     * L - average number of letters per 100 words
     * S- average number of sentences per 100 words. */
    float L = 0, S = 0;

    int totalWords = 0, totalLetters = 0, totalSentences = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            totalLetters++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            totalSentences++;
        }
        else if (text[i] == ' ')
        {
            totalWords++; /* Acutally counting the total number of spaces */
        }
    }

    /* Total words is total spaces + 1*/
    totalWords++;

    /* totalLetters/totalWords = number of letters per words*/
    L = (float) totalLetters / totalWords * 100;
    /* Typecasting is an absolute necessity (fear of 0.xx ~ 0)*/
    S = (float) totalSentences / totalWords * 100;

    float readingLevel = COLEMAN_LIAU_L * L - COLEMAN_LIAU_S * S - COLEMAN_LIAU_CONSTANT;

    return round(readingLevel);
}

void displayReadingLevel(int readingLevel)
{
    if (readingLevel < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (readingLevel >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", readingLevel);
    }
}
