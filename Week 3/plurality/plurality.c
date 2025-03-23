/* Plurality Voting System */
#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define NO_CANDIDATE 1
#define EXCESS_CANDIDATES 2
#define MAX_CANDIDATES 9

/* Candidates have name and vote count */
typedef struct
{
    string name;
    int votes;
} candidate;

/* Array of candidates */
candidate candidates[MAX_CANDIDATES];

/* Number of candidates */
int candidate_count;

/* Function prototypes */
bool vote(string);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return NO_CANDIDATE;
    }

    /* Populate array of candidates */
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return EXCESS_CANDIDATES;
    }
    else if (candidate_count == 1)
    {
        printf("%s\n", argv[1]);
        return 0;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count;
    do
    {
        voter_count = get_int("Number of voters: ");
    }
    while (voter_count <= 0);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner()
{
    int largest_vote_count_index = 0;

    /* Calculating the index of the candidate with the highest number of votes */
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[largest_vote_count_index].votes < candidates[i].votes)
        {
            largest_vote_count_index = i;
        }
    }
    /* Printing the candidate names with the same number of votes as the candidate of the calculate
     * index
     */
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[largest_vote_count_index].votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
