#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 10

typedef struct {
    int transition[MAX_STATES][MAX_SYMBOLS];
    bool is_final[MAX_STATES];
    int num_states;
    int num_symbols;
} DFA;

void initialize_dfa(DFA *dfa) {
    for (int i = 0; i < MAX_STATES; i++) {
        dfa->is_final[i] = false;
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            dfa->transition[i][j] = -1; // Initialize transitions to -1 (undefined)
        }
    }
}

bool equivalent(int state1, int state2, int partition[MAX_STATES], DFA *dfa) {
    if (dfa->is_final[state1] != dfa->is_final[state2]) {
        return false;
    }
    for (int symbol = 0; symbol < dfa->num_symbols; symbol++) {
        if (partition[dfa->transition[state1][symbol]] != partition[dfa->transition[state2][symbol]]) {
            return false;
        }
    }
    return true;
}

void minimize_dfa(DFA *dfa) {
    int partition[MAX_STATES];
    int new_partition[MAX_STATES];
    int num_partitions = 0;

    // Initial partition: final and non-final states
    for (int i = 0; i < dfa->num_states; i++) {
        partition[i] = dfa->is_final[i] ? 1 : 0; // Use 0 for non-final, 1 for final
    }

    bool changed;
    do {
        changed = false;
        int temp_partition[MAX_STATES];
        int temp_num_partitions = 0;

        for (int i = 0; i < dfa->num_states; i++) {
            if (partition[i] == -1) continue; // Skip already merged states
            bool found = false;
            for (int j = 0; j < temp_num_partitions; j++) {
                if (equivalent(i, temp_partition[j], partition, dfa)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                temp_partition[temp_num_partitions++] = i;
            }
        }

        // Update the partition array
        for (int i = 0; i < dfa->num_states; i++) {
            if (partition[i] == -1) continue; // Skip already merged states
            for (int j = 0; j < temp_num_partitions; j++) {
                if (equivalent(i, temp_partition[j], partition, dfa)) {
                    partition[i] = partition[temp_partition[j]]; // Merge
                    break;
                }
            }
        }
        num_partitions = temp_num_partitions;
    } while (changed);

    // Output the minimized DFA
    printf("Minimized DFA states:\n");
    for (int i = 0; i < dfa->num_states; i++) {
        if (partition[i] == 1) { // Print final states
            printf("State: %d (Final)\n", i);
        }
    }
}

int main() {
    DFA dfa;

    printf("Enter number of states: ");
    scanf("%d", &dfa.num_states);
    
    printf("Enter number of symbols: ");
    scanf("%d", &dfa.num_symbols);

    initialize_dfa(&dfa); // Initialize DFA

    printf("Enter transition table (row by row, space-separated):\n");
    for (int i = 0; i < dfa.num_states; i++) {
        for (int j = 0; j < dfa.num_symbols; j++) {
            scanf("%d", &dfa.transition[i][j]);
        }
    }

    printf("Enter final states (space-separated, -1 to end): ");
    int state;
    while (true) {
        scanf("%d", &state);
        if (state == -1) break;
        dfa.is_final[state] = true;
    }

    minimize_dfa(&dfa);

    return 0;
}

/*gcc minimize_dfa.c -o minimize_dfa
./minimize_dfa
Enter number of states: 3
Enter number of symbols: 2
Enter transition table (row by row, space-separated):
1 2 0 1 1 2
Enter final states (space-separated, -1 to end): 0 -1
Minimized DFA states:
State: 0 (Final)
*/
