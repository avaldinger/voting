#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

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

    // printf("votes %i ", candidates[0].votes);

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for(int i = 0; i < candidate_count; i++) {
        // printf("candidates names: %s \n", candidates[i].name);
        if (strcmp(candidates[i].name, name) == 0) {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    string winner = "";
    int hihgestVote = 0;
    bool singleWinner = true;
    string winners[MAX];

    // check for the highest number of votes
    for (int i = 0; i < candidate_count; i++) {
         for (int j = 0; j <= i; j++) {
             if (candidates[i].votes >= candidates[j].votes) {
                hihgestVote = candidates[i].votes;
                winner = candidates[i].name;
             }
         }

     }

    // set the first element of the array to the winner with the highest votes
    winners[0] = winner;
    // check if other candidates have the same highest number of votes
    for (int i =0; i < candidate_count; i++){
          if ((candidates[i].votes == hihgestVote) && (candidates[i].name != winner)) {
                winners[i+1] = candidates[i].name;
                singleWinner = false;
          }
      }

    if (singleWinner) {
     printf("%s\n", winner);
    } else {
        for (int i = 0; i < (MAX/2)+1; i++) {
            if (strlen(winners[i]) > 0) {
              printf("%s\n", winners[i]);
            }
        }
    }
    return;
}

