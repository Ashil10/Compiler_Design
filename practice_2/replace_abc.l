%{
#include <stdio.h>
%}

%%
abc     { printf("ABC"); }  // Replace "abc" with "ABC"
.       { putchar(yytext[0]); }  // Print other characters as they are

%%

int main(void) {
    yylex();  // Start scanning
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}



