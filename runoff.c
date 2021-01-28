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
}
candidate;

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
void sort(int array[], int length);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

    voter_count = get_int("Number of voters: ");
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

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        // Eliminate anyone with minimum number of votes
        eliminate(min);
        // Check if the result is a tie
        bool tie = is_tie(min);

        // If tie, everyone wins
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



        // Reset vote counts back to zero
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
    // Assigning the candidate to the selected rank
    for (int candidate_id = 0; candidate_id < candidate_count; candidate_id++) {
        if (strcmp(candidates[candidate_id].name, name) == 0) {
            preferences[voter][rank] = candidate_id;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int candidate_id = 0;
    int firstElement = 0;
    // Add a vote for the first ranked candidate for each voter
    for (int voter = 0; voter < voter_count; voter++) {
            candidate_id = preferences[voter][firstElement];
            if (!candidates[candidate_id].eliminated) {
                candidates[candidate_id].votes += 1;
            }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int candidate_id = 0; candidate_id < candidate_count; candidate_id++) {
        if(candidates[candidate_id].votes > (voter_count/2) ) {
            printf("Winner is: %s\n", candidates[candidate_id].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimumVote = 0;
    int arrayOfVotes[candidate_count];
    // Searching for the minimum number of votes between non-eliminated candidates
    for (int candidate_id = 0; candidate_id < candidate_count; candidate_id++) {
        if (!candidates[candidate_id].eliminated) {
            arrayOfVotes[candidate_id] = candidates[candidate_id].votes;
        }

    }

    // Sorting the array with the votes
    sort(arrayOfVotes, candidate_count);
    minimumVote = arrayOfVotes[0];
    printf("Minimum vote: %i\n", minimumVote);

    return minimumVote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool tie = true;
    int voteScores[candidate_count];
    // Adding all votes per candidate to a list
    for (int candidate_id = 0; candidate_id < candidate_count; candidate_id++) {
        if (!candidates[candidate_id].eliminated) {
        voteScores[candidate_id] = candidates[candidate_id].votes;
        }
    }

    // Checking if there is higher score of votes than the minumum
    for (int i = 0; i < candidate_count; i++) {
        if (voteScores[i] > min) {
            tie = false;
        }
    }

    return tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    int id = 0;
    // TODO
    // checking if everybody has the minimum number of votes
    if (!is_tie(min)) {
        for (int candidate_id = 0; candidate_id < candidate_count; candidate_id++) {
            if(candidates[candidate_id].votes == min) {
            candidates[candidate_id].eliminated = true;
            }
        }
    }

    // updating the preferences if the first option got eliminated
    for (int voter = 0; voter < voter_count; voter++) {
        id = preferences[voter][0];
        if (candidates[id].eliminated) {
                preferences[voter][0] = preferences[voter][1];
        }
    }


    return;
}

void sort(int array[], int length) {

    int temp;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (array[j] > array[i]) {

                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }

    }
}
