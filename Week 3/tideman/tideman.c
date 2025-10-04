// Ranked-choice voting system - Tideman

// Add code to handle same name given many times in both command line arguments and as choices.
// Doesn't handle leading and trailing whitespaces as votes.
// Terminates abruptly if an invalid vote is read.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define INVALID_USAGE 1
#define EX_MAX_CANDIDATE 2
#define INVALID_VOTE 3
#define CANDIDATE_DUPLICATION 4

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX] = {0};

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
// Max pairs that can be formed: C(MAX,2).
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void swap_values(int *a, int *b);
void sort_pairs(void);
void lock_pairs(void);
bool not_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    // There should be atleast one candidate participating in the election.
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return INVALID_USAGE;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    // Ensure the maximum number of candidates participating in the elections is <= 9.
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return EX_MAX_CANDIDATE;
    }

    // Check if duplication of candidate name exists while populating the candidates array.
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
        for (int j = 0; j < i; j++)
        {
            // If name duplication exists at any index other than itself, return.
            if (strcmp(candidates[i], candidates[j]) == 0)
            {
                printf("Candidate name duplication spotted!\nAborting....\n");
                return CANDIDATE_DUPLICATION;
            }
        }
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("\nNumber of voters: ");

    /* Query for votes
     * Store the ranks in a temporary array for each voter
     * Use it to change the preferences[][] array values
     */

    for (int i = 0; i < voter_count; i++)
    {
        printf("\nVoter %i\n", i + 1);
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return INVALID_VOTE;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Look for name in the candidates array.
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the name matches with the person's name in the current index.
        if (strcmp(candidates[i], name) == 0)
        {
            // Update ranks[rank] to point to the index of the candidate.
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences array given a voter's ranks array.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // Avoid incrementing diagonal values.
            if (ranks[i] == ranks[j])
                continue;
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate over the preferences matrix and add pairs.
    for (int i = 0, index = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            /* If candidate i wins over candidate j in a head to head fight, add them to pair_count.
             * Declare the winner and the loser.
             */
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[index].winner = i;
                pairs[index].loser = j;
                index++;
            }
        }
    }
    return;
}

void swap_values(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}

/* Sort pairs in decreasing order by strength of victory
 * Strength of victory |preferences[i] - preferences[j]|.
 * Sorting technique - Selection Sort.
 */
void sort_pairs(void)
{
    // Sort the pairs[] in decreasing order of margin.
    for (int i = 0; i < pair_count - 1; i++)
    {
        int highest_margin = preferences[pairs[i].winner][pairs[i].loser] -
                             preferences[pairs[i].loser][pairs[i].winner];
        int h_index = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            int margin = preferences[pairs[j].winner][pairs[j].loser] -
                         preferences[pairs[j].loser][pairs[j].winner];
            // Update index of highest margin if the current pair's margin is greater.
            if (margin >= highest_margin)
            {
                highest_margin = margin;
                h_index = j;
            }
        }
        // Swap the winner.
        swap_values(&pairs[h_index].winner, &pairs[i].winner);

        // Swap the loser.
        swap_values(&pairs[h_index].loser, &pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Check if a cycle exists, else lock the pair.
        if (not_cycle(pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool not_cycle(int winner, int loser)
{
    // Base case, if winner = loser the we are back to the node from where we started.
    if (winner == loser)
    {
        return false;
    }
    // Else just keep pushing the value of loser closer and closer to winner.
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            // If only i is linked to loser, can you find if a cycle exists between winner and
            // loser.
            if (locked[loser][i] == true)
            {
                if (not_cycle(winner, i) == false)
                {
                    return false;
                }
            }
        }
    }
    // If the base condition is not satisified even after looping through all the candidates, a
    // cycle indeed doesn't exist.
    return true;
}
// Print the winner of the election
void print_winner(void)
{
    /* Winner of the election is the one who doesn't have a single false value in their row,
     * Except for their own index (i,i), or if they tied.
     * A false in any other index means that it is being pointed at by some other node, except if
     * they tied. Candidate i would lose to j at in a head to head fight => locked[i][j] = 0 but
     * locked[j][i] != 0.
     */
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;

        for (int j = 0; j < candidate_count; j++)
        {
            // If false exists in the row, except in their own index, the person cannot be the
            // winner. Unless, if they tied.
            if (locked[i][j] == 0 && (i != j) && locked[j][i] != 0)
            {
                is_winner = false;
                break;
            }
        }
        // If you find a row, satisfying the above criteria, print the person in that row as the
        // winner of the election.
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    // If control reaches this part, there is no "single" source to the graph.

    /* Method 2.
     * A person who wins the election is the one with no true values in their column (locked
     * matrix). A true value in their column means They are being pointed at by someone which means
     * they aren't the source of the graph.
     *
     ********              Code                *********
     *
     * for (int i = 0; i < candidate_count; i++)
     * {
     * 		bool is_winner = true;
     * 		for (int j = 0; j < candidate_count; j++)
     * 		{
     *          	if (locked[j][i] == true)
     *          	{
     *          		is_winner = false;
     *          		break;
     *          	}
     *          }
     *          if (is_winner)
     *          {
     *          	printf("%s\n",candidates[i]);
     *          }
     * }
     */

    // Add code to print both winners, right now it only prints the person with the lowest index
    // value.
    return;
}
