#include <cs50.h>
#include <math.h>
#include <stdio.h>

int card_length(long);
int calculate_luhn_sum(int, long);
void verify(int, long, int);

int main(void)
{
    long card_number = get_long("Number: ");
    int length = card_length(card_number);
    /* Implementing and printing the required output */
    int sum = calculate_luhn_sum(length, card_number);
    verify(sum, card_number, length);
}

int card_length(long card_number)
{
    /* Finding the number of digits in the card_number */
    int length = 0;
    long temp1 = card_number;
    while (temp1 != 0)
    {
        length++;
        temp1 /= 10;
    }
    return length;
}

int calculate_luhn_sum(int length, long card_number)
{
    /* Implementing Luhn's Algorithm */
    int sum = 0;

    while (card_number > 0)
    {
        sum += card_number % 10;
        card_number /= 10;
        int temp = (card_number % 10) * 2;
        while (temp > 0)
        {
            sum += temp % 10;
            temp /= 10;
        }
        card_number /= 10;
    }
    return sum;
}

void verify(int sum, long card_number, int length)
{
    /*
        Validity of cards according to the following facts provided in the problem statement:
    1. American Express - 15 digits and starts with 34,37
    2. MasterCard - 16 digits and starts with 51,52,53,54,55
    3. VISA - 13 and 16 digits and starts with 4
    */
    /*
    while (card_number > 100)
     {
         card_number /= 10;
     }
         can be used to reduce card_number into the first two digits of the card_number.
    */
    int first_two_digits = card_number / pow(10, length - 2);
    int first_digit = card_number / pow(10, length - 1);
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return;
    }
    else
    {
        if (first_digit == 4 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else if ((first_two_digits == 34 || first_two_digits == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if ((first_two_digits >= 51 && first_two_digits <= 55) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
