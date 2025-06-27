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
} pair;

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
        // ranks[i] is candidate_index of voter's ith preference
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
    // modify ranks array
    for (int i = 0; i < candidate_count; i++){
        if (strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // preferences[i][j] is the number of people who liek i over j
    //len(ranks) = candidate_count

    for (int c1 = 0; c1 < candidate_count-1; c1++){
        for (int c2 = c1+1; c2 < candidate_count; c2++){
            //ranks[c1] is always ranked higher than ranks[c2], since c1 comes before c2

            int i = ranks[c1];
            int j = ranks[c2];
            preferences[i][j]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    // use preferences matrix
    for (int i = 0; i < candidate_count-1; i++){
        for (int j = i+1; j < candidate_count; j++){

            if (preferences[i][j] != preferences[j][i]){
                pair p;
                p.winner = (preferences[i][j] > preferences[j][i]) ? i : j;
                // p.loser = (preferences[i][j] > preferences[j][i]) ? j : i;
                p.loser = (p.winner == i)? j : i;
                pairs[pair_count] = p;
                pair_count ++;
            }

            //original implementatino below:
            // if (preferences[i][j] > preferences[j][i]){
            //     pair p;
            //     p.winner = i;
            //     p.loser = j;
            //     pairs[pair_count] = p;
            //     pair_count++;
            // }
            // else if (preferences[j][i] > preferences[i][j]){
            //     pair p;
            //     p.winner = j;
            //     p.loser = i;
            //     pairs[pair_count] = p;
            //     pair_count++;
            // }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory

int get_pair_diff(pair p){
    return preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
}

void swap(int i, int j, pair arr[]){
    //swaps index i and j in arr
    pair temp = arr[j];
    arr[j] = arr[i];
    arr[i] = temp;
}

void sort_pairs(void)
{
    // since maximum pair_count is MAX(MAX-1)/2 = 9(10)/2 = 45, an O(n^2) algo like bubble sort will suffice

    // len(pairs) is pair_count 
    for (int i = 0; i < pair_count; i++){
        for (int j = 0; j < pair_count-1-i; j++){
            // left_pair = pairs[j].winner, pairs[j].loser
            int ldiff = get_pair_diff(pairs[j]);
            // right_pair = pairs[j+1].winner
            int rdiff = get_pair_diff(pairs[j+1]);

            if (ldiff < rdiff){
                swap(j, j+1, pairs);
            }
        }
    }
    return;
}



// Lock pairs into the candidate graph in order, without creating cycles


//if you can get from current to target by following edges of the graph as in locked
bool leads_to(int current, int target){
    if (target == current){
        return true;
    }

    //for every outward going edge from here check if that destination leads to target

    // locked[i][j] means i is locked in over j. 
    // locked[i] contains all the js that i is locked in over
    int i = current;
    for (int j = 0; j < candidate_count; j++){
        if (locked[i][j] == true){
            // j is a possible destination from i
            if (leads_to(j, target)){
                return true;
            }
        }
    }
    //if none of the options leads to j, return false
    return false;
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++){
        pair p = pairs[i];
        if (!leads_to(p.loser, p.winner)){
            locked[p.winner][p.loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //the winner is the source of the graph
    //a candidate is a source if it has no incoming nodes
    // locked[i][j] means i is locked in over j; there is an edge from i to j; j has an incomming node

    //if any i in locked[i][j] is true, j cannot be the source

    bool is_winner;

    for (int candidate = 0; candidate < candidate_count; candidate++){
        is_winner = true;
        for (int i = 0; i < candidate_count; i++){
            if (locked[i][candidate] == true){
                //candidate has something locked in over it; it has an incoming node
                is_winner = false;
                break;
            }
        }

        if (is_winner){
            printf("%s\n", candidates[candidate]);
            return;
        }
    }

    return;
}
