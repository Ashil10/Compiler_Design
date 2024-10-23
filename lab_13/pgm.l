%{
#include <stdio.h>

int word_count = 0;       // To count words
int char_count = 0;       // To count characters
%}

%%  // Start of rules section

[ \t\n]+          { /* Ignore whitespace */ }
[a-zA-Z]+        { word_count++; char_count += yyleng; }
.                { char_count++; } // Count any other character

%%  // End of rules section

int main() {
    yylex();  // Call the lexer
    printf("Word count: %d\n", word_count);
    printf("Character count: %d\n", char_count);
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

