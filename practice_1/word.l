%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
%}

%%
[ \t\n]+            ; // Ignore whitespace
[a-zA-Z]+          { word_count++; char_count += yyleng; }
.                  { char_count++; } // Count any single character

%% 

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    yyin = file; // Set the input stream to the file
    yylex();
    fclose(file);

    printf("Word Count: %d\n", word_count);
    printf("Character Count: %d\n", char_count);
    return 0;
}

int yywrap() {
    return 1;
}

