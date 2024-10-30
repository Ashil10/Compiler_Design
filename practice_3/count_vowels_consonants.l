%{
#include <stdio.h>
#include <ctype.h>

int vowel_count = 0;
int consonant_count = 0;
%}

%%
[aeiouAEIOU]     { vowel_count++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { consonant_count++; }
.                { /* Ignore other characters */ }

%%

int main(void) {
    yylex();  // Start scanning
    printf("Total vowels: %d\n", vowel_count);
    printf("Total consonants: %d\n", consonant_count);
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


/*
output:
Hello World

Total vowels: 3
Total consonants: 7
*/
