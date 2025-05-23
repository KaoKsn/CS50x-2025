#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    /* Checking for validity of the input */
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    /* To handle a case where there is only one candidate */
    else if (argc == 2)
    {
        printf("%s\n", argv[1]);
        return 0;
    }

    /* Checking if the user has followed the constraints */
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    /* Reading the total number of voters and evalutaing it */
    do
    {
        voter_count = get_int("Number of voters: ");
    }
    while (voter_count <= 0);
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        /* Has anyone won the election? */
        bool won = print_winner();
        if (won)
        {
            break;
        }

        /* If not, does the election tie after removing the candidate with the least number of
         * votes? */
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, after eliminating, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        /* If not even a tie */
        // Eliminate anyone with minimum number of votes
        eliminate(min);

        /* Reset vote counts back to zero
         * This is essential because votes are counted again and again
         */
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        /* There every value of the columns of a particular row must be unique
         * i.e every rank must have a unique candidate name.
         */
        if (strcmp(name, candidates[i].name) == 0)
        {
            for (int j = 0; j < rank; j++)
            {
                if (preferences[voter][j] == i)
                {
                    printf("Redundancy in preference\n");
                    return false;
                }
            }
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

/* Tabulate votes for non-eliminated candidates
 * The same function tabulates the votes intially also
 * Effectively bringing all vote counting to one function(improve readability)
 */
void tabulate(void)
{
    /* Tabluate the votes for a candidate only if they have not been eliminated

    You also have to code here to update the vote values after elimination */
    for (int i = 0; i < voter_count; i++)
    {
        /* If the candidate has been eliminated select his second preference */
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j + 1]].votes++;
            }
        }
        candidates[preferences[i][0]].votes++;
    }
    return;
}

/* Print the winner of the election(return true), if there is one */
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int least_vote_candidate = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes < candidates[least_vote_candidate].votes) &&
            (!candidates[i].eliminated))
        {
            least_vote_candidate = i;
        }
    }
    return least_vote_candidate;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        /* Return false if,
         * All the candidates don't have the same number of votes as that of the candidate with
         * minimum number of votes Else, true.
         */
        if ((!candidates[i].eliminated) && (candidates[i].votes == candidates[min].votes) == 0)
        {
            return false;
        }
    }
    return true;
}

/* Eliminate the candidate (or candidates) in last place */
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    /* Multiple elimiations will not occur when there is a tie because,
     * we break off the runoff loop after printing the joint winners
     */
    return;
}
