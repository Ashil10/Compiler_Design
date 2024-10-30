#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 10

typedef struct {
    int transitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES];
    bool is_final[MAX_STATES];
    int num_states;
    int num_symbols;
} ENFA;

// Function to initialize the ENFA structure
void initialize_enfa(ENFA *enfa) {
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            for (int k = 0; k < MAX_STATES; k++) {
                enfa->transitions[i][j][k] = 0;
            }
        }
        enfa->is_final[i] = false;
    }
}

// Function to add ε-transition
void add_epsilon_transition(ENFA *enfa, int from, int to) {
    enfa->transitions[from][MAX_SYMBOLS - 1][to] = 1; // Assume the last symbol is ε (index = num_symbols - 1)
}

// Function to compute ε-closure
void e_closure(int state, bool closure[], ENFA *enfa) {
    closure[state] = true;
    for (int i = 0; i < MAX_STATES; i++) {
        if (enfa->transitions[state][MAX_SYMBOLS - 1][i]) {
            if (!closure[i]) {
                e_closure(i, closure, enfa);
            }
        }
    }
}

// Function to convert ε-NFA to NFA
void convert_enfa_to_nfa(ENFA *enfa) {
    // NFA construction
    int nfa_transitions[MAX_STATES][MAX_SYMBOLS][MAX_STATES] = {0};
    bool nfa_final[MAX_STATES] = {false};
    int state_map[MAX_STATES] = {0}; // Mapping of ENFA to NFA states
    int nfa_state_count = 0;

    // Iterate through each state of ENFA
    for (int i = 0; i < enfa->num_states; i++) {
        bool closure[MAX_STATES] = {false};
        e_closure(i, closure, enfa); // Compute ε-closure

        // Map the ε-closure states to a new NFA state
        int new_state = nfa_state_count++;
        for (int j = 0; j < enfa->num_states; j++) {
            if (closure[j]) {
                state_map[j] = new_state; // Map the original state to the new state
                if (enfa->is_final[j]) {
                    nfa_final[new_state] = true; // Mark as final if any state in closure is final
                }
            }
        }

        // Build transitions for the new NFA state
        for (int symbol = 0; symbol < MAX_SYMBOLS - 1; symbol++) {
            for (int k = 0; k < MAX_STATES; k++) {
                if (enfa->transitions[i][symbol][k]) {
                    int target_state = state_map[k];
                    nfa_transitions[new_state][symbol][target_state] = 1; // Set the transition
                }
            }
        }
    }

    // Print the resulting NFA
    printf("NFA Transitions:\n");
    for (int i = 0; i < nfa_state_count; i++) {
        for (int j = 0; j < MAX_SYMBOLS - 1; j++) {
            for (int k = 0; k < MAX_STATES; k++) {
                if (nfa_transitions[i][j][k]) {
                    printf("State %d --%d--> State %d\n", i, j, k);
                }
            }
        }
        if (nfa_final[i]) {
            printf("State %d is a final state.\n", i);
        }
    }
}

int main() {
    ENFA enfa;

    printf("Enter the number of states in ε-NFA: ");
    scanf("%d", &enfa.num_states);
    printf("Enter the number of symbols (including ε): ");
    scanf("%d", &enfa.num_symbols);

    initialize_enfa(&enfa);

    printf("Enter transition table (from state, symbol, to state):\n");
    printf("Use %d for ε transitions:\n", enfa.num_symbols - 1); // Assume last index is for ε
    for (int i = 0; i < enfa.num_states; i++) {
        for (int j = 0; j < enfa.num_symbols; j++) {
            printf("State %d, Symbol %d (enter state or -1 to skip): ", i, j);
            int to_state;
            while (true) {
                scanf("%d", &to_state);
                if (to_state == -1) break;
                enfa.transitions[i][j][to_state] = 1;
            }
        }
    }

    printf("Enter final states (space-separated, -1 to end): ");
    int state;
    while (true) {
        scanf("%d", &state);
        if (state == -1) break;
        enfa.is_final[state] = true;
    }

    convert_enfa_to_nfa(&enfa);

    return 0;
}
/*gcc enfa_to_nfa.c -o enfa_to_nfa
enfa to nfa$ ./enfa_to_nfa
Enter the number of states in ε-NFA: 3
Enter the number of symbols (including ε): 3
Enter transition table (from state, symbol, to state):
Use 2 for ε transitions:
State 0, Symbol 0 (enter state or -1 to skip): 1
-1
State 0, Symbol 1 (enter state or -1 to skip): 1
-1
State 0, Symbol 2 (enter state or -1 to skip): -1
State 1, Symbol 0 (enter state or -1 to skip): 0
-1
State 1, Symbol 1 (enter state or -1 to skip): -1
State 1, Symbol 2 (enter state or -1 to skip): -1
State 2, Symbol 0 (enter state or -1 to skip): -1
State 2, Symbol 1 (enter state or -1 to skip): -1
State 2, Symbol 2 (enter state or -1 to skip): -1
Enter final states (space-separated, -1 to end): 1 -1
NFA Transitions:
State 0 --0--> State 0
State 0 --1--> State 0
State 1 --0--> State 0
State 1 is a final state.
*/
