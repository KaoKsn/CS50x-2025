/* Implementing a greedy algorithm to
    print the minimum number of coins required to
    form the change during a financial transcation
*/
#include <cs50.h>
#include <stdio.h>

void calculate_coins(int);

int main(void)
{
    int change;
    /* Reading the required amount */
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    /* Evaluting the algorithm for the read amount of change */
    calculate_coins(change);
}

/* Implementation */
void calculate_coins(int change)
{
    /* We are performing integer arithmetic
        So,
            change/naturals will work
    */
    int coin_denominations[4] = {25, 10, 5, 1};
    int coins_required = 0;
    for (int i = 0; change != 0; i++)
    {
        if (change / coin_denominations[i] != 0)
        {
            coins_required += change / coin_denominations[i];
            change %= coin_denominations[i]; /* Update the value of change */
        }
    }
    printf("%i\n", coins_required);

    /* Using a loop is better than using many if statements inside a while loop
    when considering the design aspect
    */
}
