%{
#include <stdio.h>
	int no=1;
%}
lite [0-9][0-9]*
inv [0-9][a-zA-Z0-9]*
ident [a-zA-Z][a-zA-Z0-9]*
lite2 \"[a-zA-Z][a-zA-Z0-9]*\"
rel <=|<|>=|>
key int|void|char|if|main|printf
%%
{lite} {printf("%s\t%i\tInteger\n",yytext,no);}
{lite2} { char aa[10],bb[10];
	strcpy(aa,yytext);
	for(int i=1;i<strlen(aa)-1;i++){
		bb[i-1]=aa[i];
	}
	printf("%s\t%i\tLiteral\n",bb,no);
		 		
	}
{inv} {printf("Invalid:\t%s\n",yytext);}
{rel} {
	printf("%s\t%i\tRelational Operator, \t",yytext,no);
	if(strcmp(yytext,"<=")==0){printf("LE");}
	if(strcmp(yytext,"<")==0){printf("LT");}
	if(strcmp(yytext,">=")==0){printf("LE");}
	if(strcmp(yytext,">")==0){printf("LT");}	
	printf("\n");
      }
"+"|"-"|"*"|"/" {printf("%s\t%i\tArithmetic opeator, ",yytext,no);
		if(strcmp(yytext,"+")==0){printf("ADD");}
		if(strcmp(yytext,"-")==0){printf("SUB");}
		if(strcmp(yytext,"/")==0){printf("DIV");}
		if(strcmp(yytext,"*")==0){printf("MUL");}
		printf("\n");	
		}
"=" {printf("%s\t%i\tAssignment operator, EQ\n",yytext,no);}
{key} {printf("%s\t%i\tkeyword\n",yytext,no);}
{ident} { printf("%s\t%i\tIdentifier\n",yytext,no);}
"\n" {no++;}
. {}
%%
int main()
{
	yyin=fopen("input.txt","r");
	printf("Lexeme\tLine\tToken\n");
	yylex();
}
