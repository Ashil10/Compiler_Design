%{
#include<stdio.h>
int flag=0;
%}
%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%%
ArithmeticExpression: E{printf("output:%d\n",$$);return 0;};
E:E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'/'E {$$=$1/$3;}
|E'%'E {$$=$1%$3;}
|'('E')' {$$=$2;}
| NUMBER {$$=$1;}
;
%%
void main()
{
printf("\nEnter the input:\n");
yyparse();
if(flag==0)
printf("Expression is Valid\n");
}
void yyerror()
{
printf("Expression is invalid\n");
flag=1;
}









//yacc -d Pg13.y
//lex Pg13.l
//gcc lex.yy.c y.tab.c -w
//./a.out



