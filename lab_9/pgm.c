#include<stdio.h>
#define MAX_STATES 100
#define MAX_SYMBOLS 100
 typedef struct {

int transition[MAX_STATES][MAX_SYMBOLS][MAX_STATES];

int epsilon[MAX_STATES][MAX_STATES];

int numStates;

int numSymbols;

} NFA;


void addTransition(NFA *nfa, int from, int to, int symbol) {

nfa->transition[from][symbol][to] = 1;

}


void addEpsilonTransition(NFA *nfa, int from, int to) {

nfa->epsilon[from][to] = 1;

}



void epsilonClosure(NFA *nfa, int state, int *closure, int *closureSize) {

closure[*closureSize] = state;

(*closureSize)++;

// Check for epsilon transitions

for (int i = 0; i < nfa->numStates; i++) {

if (nfa->epsilon[state][i]) {

// Check if state is already in closure

int alreadyInClosure = 0;

for (int j = 0; j < *closureSize; j++) {

if (closure[j] == i) {

alreadyInClosure = 1;

break;

}

}

if (!alreadyInClosure) {

epsilonClosure(nfa, i, closure, closureSize);

}

}

}

}


int main() {

NFA nfa;

int epsilonClosureResult[MAX_STATES];

printf("Enter the number of states: ");

scanf("%d", &nfa.numStates);

printf("Enter the number of input symbols: ");

scanf("%d", &nfa.numSymbols);


for (int i = 0; i < nfa.numStates; i++) {

for (int j = 0; j < nfa.numSymbols; j++) {

for (int k = 0; k < nfa.numStates; k++) {

nfa.transition[i][j][k] = 0; // No transitions

}

}

for (int k = 0; k < nfa.numStates; k++) {

nfa.epsilon[i][k] = 0; // No epsilon transitions

}

}


for (int i = 0; i < nfa.numStates; i++) {

printf("\nEnter the transitions for state %d\n",i);

for (int j = 0; j < nfa.numSymbols; j++) {

printf("\t for symbol %c: ", j==nfa.numSymbols-1? 35 : j+97);

int toState;

while (1) {

scanf("%d", &toState);

if(toState == -1) break;

if(j==nfa.numSymbols-1) //checking whether epsilon transition or normal input transition

addEpsilonTransition(&nfa, i, toState);

else

addTransition(&nfa, i, toState, j);

}

}

}



for (int i = 0; i < nfa.numStates; i++) {

int closure[MAX_STATES];

int closureSize = 0;

epsilonClosure(&nfa, i, closure, &closureSize);

printf("Epsilon closure of state %d: { ", i);

for (int j = 0; j < closureSize; j++) {

printf("%d ", closure[j]);

}

printf("}\n");

}

return 0;

}
