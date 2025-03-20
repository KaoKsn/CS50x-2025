#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string);
void result(int, int);

int main(void)
{
    /* Taking the string inputs of both the players */
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    /* Calculating the scores and printing the result */
    int score1 = calculate_score(player1);
    int score2 = calculate_score(player2);
    result(score1, score2);
}

int calculate_score(string player)
{
    int playerScore = 0;

    for (int i = 0, length = strlen(player); i < length; i++)
    {
        if (isalpha(player[i]))
        {
            char alpha = toupper(player[i]);
            if (alpha == 'A' || alpha == 'E' || alpha == 'U' || alpha == 'I' || alpha == 'L' ||
                alpha == 'N' || alpha == 'O' || alpha == 'R' || alpha == 'S' || alpha == 'T')
            {
                playerScore += 1;
            }
            else if (alpha == 'D' || alpha == 'G')
            {
                playerScore += 2;
            }
            else if (alpha == 'B' || alpha == 'C' || alpha == 'M' || alpha == 'P')
            {
                playerScore += 3;
            }
            else if (alpha == 'F' || alpha == 'H' || alpha == 'V' || alpha == 'W' || alpha == 'Y')
            {
                playerScore += 4;
            }
            else if (alpha == 'K')
            {
                playerScore += 5;
            }
            else if (alpha == 'J' || alpha == 'X')
            {
                playerScore += 8;
            }
            else
            {
                playerScore += 10;
            }
        }
    }
    return playerScore;
}

void result(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
