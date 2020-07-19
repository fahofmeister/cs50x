#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool checkCycle(int start, int end);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
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
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
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
    // Search the candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the name is valid
        if (strcmp(name, candidates[i]) == 0)
        {
            // Assign the candidate index to ranks
            ranks[rank] = i;
            return true;
        }
    }

    // No candidate name found
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Highest rank candidate
    for (int i = 0; i < candidate_count; i++)
    {
        int highest = ranks[i];

        // Lowest rank candidate
        for (int j = i + 1; j < candidate_count; j++)
        {
            int lowest = ranks[j];
            preferences[highest][lowest]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Candidate rows
    for (int i = 0; i < candidate_count; i++)
    {
        // Candidate columns
        for (int j = 0; j < candidate_count; j++)
        {
            // Check if preference of candidate i over j
            // is higher than j over i
            if (preferences[i][j] > preferences [j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Flag if a swap occurred in the loop
    bool hasSwap = true;

    while (hasSwap)
    {
        hasSwap = false;

        // Iterates all pairs in order
        for (int i = 1; i < pair_count; i++)
        {
            // Atributes the votes to variables strength
            int strength1 = preferences[pairs[i - 1].winner][pairs[i - 1].loser];
            int strength2 = preferences[pairs[i].winner][pairs[i].loser];

            // If the second value is higher, swap positions
            if (strength2 > strength1)
            {
                hasSwap = true;
                pair temp = pairs[i - 1];
                pairs[i - 1] = pairs[i];
                pairs[i] = temp;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!checkCycle(loser, winner))
        {
            locked[winner][loser] = true;
        }
    }

    return;
}

// Checks if there is a circuit between the start and end
bool checkCycle(int start, int end)
{
    // Iterate over locked array
    for (int j = 0; j < candidate_count; j++)
    {
        // If there is an edge
        if (locked[start][j])
        {
            // Base case
            if (j == end)
            {
                return true;
            }

            // Recursive function
            if (checkCycle(j, end))
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Benchmark of minimum number of edges
    int minEdges = candidate_count;

    // Save the candidate with least number of edges
    int winnerIndex;

    // Sums the number of edges for each candidate
    for (int j = 0; j < candidate_count; j++)
    {
        int edgesSum = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
            {
                edgesSum++;
            }
        }

        // Checks if the current candidate has the minimum edges
        if (edgesSum < minEdges)
        {
            minEdges = edgesSum;
            winnerIndex = j;
        }
    }

    // Finds the candidate with lowest number of edges
    printf("%s\n", candidates[winnerIndex]);
    return;
}

