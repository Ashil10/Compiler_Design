#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void main()
{
    char code[10][30], str[20], opr[10];
    int i = 0,k=0;
    FILE *fp1,*fp2;
    fp1=fopen("input.txt","r");
    printf("file opened\n");
    fp2=fopen("result.txt","w");
    char op,fir[10],sec[10],res[10];
    while(!feof(fp1)){

    	fscanf(fp1,"%c%s%s%s\n",&op,fir,sec,res);
    	printf("%c %s %s %s\n",op,fir,sec,res);
    
    	switch (op){
		case '+':    
		    	strcpy(opr, "ADD ");
		    	i=0;
		    	break;
	    	case '-':
			strcpy(opr, "SUB");
			i=0;
			break;
		case '*':
			strcpy(opr, "MUL ");
			i=1;
			break;
		case '/' :
		    	strcpy(opr, "DIV");
			i=1;
			break;
	    }
	    if(strlen(fir)==2)
    	    {	
    	    	if (fir[1]=='1')
    	    		fprintf(fp2,"MOV AX,CH\n");
    	    	else if (fir[1]=='2')
    	    		fprintf(fp2,"MOV BX,CL\n");
    	    	else if (fir[1]=='3')
    	    		fprintf(fp2,"MOV CX,DH\n");
    	    	else if (fir[1]=='4')
    	    		fprintf(fp2,"MOV DX,DL\n");
    	    }
    	    else
    	    fprintf(fp2,"MOV AX,[%s]\n", fir);
    	    if(strlen(sec)==2)
    	    {	
    	    	if (sec[1]=='1')
    	    		fprintf(fp2,"MOV BX,CH\n");
    	    	else if (sec[1]=='2')
    	    		fprintf(fp2,"MOV BX,CL\n");
    	    	else if (sec[1]=='3')
    	    		fprintf(fp2,"MOV BX,DH\n");
    	    	else if (sec[1]=='4')
    	    		fprintf(fp2,"MOV BX,DL\n");
    	    }
    	    else
    	    	fprintf(fp2,"MOV BX,[%s]\n",sec);
    	    if (i==0)
	    fprintf(fp2,"%sAX,BX\n", opr);
	    else
	    fprintf(fp2,"%s BX\n", opr);
	    if(strlen(res)==2)
    	    {	
    	    	if (res[1]=='1')
    	    		fprintf(fp2,"MOV CH,AX\n");
    	    	else if (res[1]=='2')
    	    		fprintf(fp2,"MOV CL,AX\n");
    	    	else if (res[1]=='3')
    	    		fprintf(fp2,"MOV DH,AX\n");
    	    	else if (res[1]=='4')
    	    		fprintf(fp2,"MOV DL,AX\n");
    	    }
    	    
	    k++;
	    
    }
}
