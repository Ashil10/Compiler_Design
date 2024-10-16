#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

char states[100],terms[100],stack[50];
int isfinal[100],resfinal[100];
int ind=0,stacklen=0;
char grams[20];
char rhs[20][50];
int count=0,rescount=0,resind=0;
int sn=0,tn=0;

char resStates[100][20],restable[100][20][10];

char table[50][50][10];
char hasEps[100];
int eind=0;

char eclsr[50];
int clsind=0;

char sstr[30];
int sortString()
{
	int l=strlen(sstr);
	for(int i=0;i<l;i++)
	{
		for(int j=0;j<l-1-i;j++)
		{
			if(sstr[j]>sstr[j+1])
			{
				char tem=sstr[j];
				sstr[j]=sstr[j+1];
				sstr[j+1]=tem;
			}
		}
	}
}

int eclfnl=0;

int eClosure(char c)
{
	for(int i=0;i<sn;i++)
	{
		if(states[i]==c)
		{	eclfnl=eclfnl|isfinal[i];
			if(strcmp(table[i][tn],"-")!=0)
			{
				strcat(eclsr,table[i][tn]);
				clsind+=strlen(table[i][tn]);
				for(int j=0;j<strlen(table[i][tn]);j++)
				{
					eClosure(table[i][tn][j]);
				}
			}
			break;
		}
	}
	return 0;
}


int main()
{
	printf("Number of states\t");
	scanf("%d",&sn);
	printf("Number of terminals\t");
	scanf("%d",&tn);
	getchar();
	printf("Enter States\t");
	for(int i=0;i<sn;i++)
	{
		states[i]=getchar();
		getchar();
		
	}
	printf("Enter terminals\t");
	for(int i=0;i<tn;i++)
	{
		terms[i]=getchar();
		getchar();
	}
	printf("Transition table\n");
	for(int i=0;i<tn;i++)
	{
		printf("\t%c",terms[i]);
	}
	printf("\tepsln\tFinal?\n");
	for(int i=0;i<sn;i++)
	{
		printf("%c\t",states[i]);
		for(int j=0;j<tn+2;j++)
		{
			scanf("%s",table[i][j]);
			if(j==tn&&strcmp(table[i][j],"-")!=0)
			{
				hasEps[eind]=states[i];
				eind++;
			}
			if(j==tn+1)
			{
				if(strcmp(table[i][j],"y")==0)
				{
				isfinal[i]=1;
				}
				else
				isfinal[i]=0;
			}
		}
	}

	for(int i=0;i<eind;i++)
	{
		eclsr[0]='\0';
		clsind=0;
		eClosure(hasEps[i]);
		for(int j=0;j<sn;j++)
		{
			for(int k=0;k<tn;k++)
			{
				for(int l=0;l<strlen(table[j][k]);l++)
				{
					if(table[j][k][l]==hasEps[i])
					{
						for(int p=0;p<clsind;p++)
						{
							int flag=1;
							for(int o=0;o<strlen(table[j][k]);o++)
							{
								if(table[j][k][o]==eclsr[p])
								{
									flag=0;
									break;
								}
							}
							if(flag)
							{
								table[j][k][strlen(table[j][k])]=eclsr[p];
							}
						}
						break;
					}
				}
			}
		}
		int thisind=0,fin=0;
		for(int k=0;k<sn;k++)
		{
			for(int l=0;l<clsind;l++)
			{
				for(int p=0;p<sn;p++)
				{
					if(states[p]==eclsr[l]&&isfinal[p]==1)
					{
						fin=1;
						break;
					}
				}
				if(fin==1)
				break;
			}
			if(states[k]==hasEps[i])
			thisind=k;
		}
		for(int j=0;j<clsind;j++)
		{
			for(int k=0;k<sn;k++)
			{
				if(eclsr[j]==states[k])
				{
					for(int l=0;l<tn;l++)
					{
						for(int o=0;o<strlen(table[k][l]);o++)
						{
							int ffll=0;
							for(int p=0;p<strlen(table[thisind][l]);p++)
							{
								if(table[thisind][l][o]==table[k][l][p])
								{
								ffll=1;
								break;
								}
							}
							if(ffll==0&&table[k][l][o]!='-')
							{
								if(table[thisind][l][0]=='-')
								table[thisind][l][0]=table[k][l][o];
								else
								table[thisind][l][strlen(table[thisind][l])]=table[k][l][o];
							}
						}
					}
				}
			}
		}
		isfinal[thisind]=fin|isfinal[thisind];
	}
	printf("\nThe equivalent DFA\n");
	eclsr[0]='\0';
	clsind=0;
	eclfnl=0;
	if(strcmp(table[0][tn],"-")==0)
	{
		eclsr[0]=states[0];
		eclsr[1]='\0';
		resfinal[0]=isfinal[0];
	}
	else
	{
		eClosure(states[0]);
		resfinal[0]=eclfnl;
	}
	strcpy(resStates[0],eclsr); 
	for(int i=0;i<tn;i++)
	{
		strcpy(restable[0][i],table[0][i]);
	}
	rescount=1;
	resind=0;
	char curres[50];
	int curlen=0;
	while(rescount>resind)
	{
		for(int j=0;j<tn;j++)
		{
			int flgg=0;
			int ri=0;
			flgg=-1;
			curlen=0;
			for(int k=0;k<strlen(resStates[resind]);k++)
			{
				for(int l=0;l<sn;l++)
				{
					if(states[l]==resStates[resind][k])
					{
						resfinal[resind]=resfinal[resind]|isfinal[l];
						flgg=l;
						break;
					}
				}
				if(flgg>=0)
				{	for(int p=0;p<strlen(table[flgg][j]);p++)
					{
						int fff=1;
						for(int l=0;l<curlen;l++)
						{
						
							if(curres[l]==table[flgg][j][p])
							{
								fff=0;
								break;
							}
						}
						if(fff==1&&table[flgg][j][p]!='-')
						{
							curres[curlen]=table[flgg][j][p];
							curlen++;
							resfinal[resind]=isfinal[flgg];
							
						}
					}
				}
			}
			if(curlen==0)
			continue;
			flgg=1;
			strcpy(sstr,curres);
			sortString();
			strcpy(curres,sstr);
			for(int k=0;k<rescount;k++)
			{
				curres[curlen]='\0';
				strcpy(sstr,resStates[k]);
				sortString();
				strcpy(resStates[k],sstr);
				if(strcmp(resStates[k],curres)==0)
				{
					flgg=0;
				}
			}
			if(flgg==1)
			{
				strcpy(resStates[rescount],curres);
				rescount++;
			}
			strcpy(restable[resind][j],curres);
		}
		resind++;
	}
	for(int i=0;i<tn;i++)
	{
		printf("\t%c",terms[i]);
	}
	printf("\tFinal?\n");
	for(int i=0;i<rescount;i++)
	{
	        if(i==0)
	          printf("Start state ");
	        else if(i+1==rescount)
	          printf("Final State ");
	        else
	          printf("            ");
		printf("%c\t",('A'+i));
		for(int j=0;j<tn+1;j++)
		{
			if(j==tn)
			{
				if(resfinal[i])
				{
					printf("YES\n");
				}
				else
					printf("N0\n");
			}
			else if(strcmp(restable[i][j],"")==0||strcmp(restable[i][j],"-")==0)
				printf("NULL\t");
			else
			{
				for(int k=0;k<rescount;k++)
				{
					if(strcmp(resStates[k],restable[i][j])==0)
					{
		      
						printf("%c\t",('A'+k));
						break;
					}
				}
			}	
		}
	}
	printf("\n");
}
