#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void find_epsilon(int state,int n,int trans[n],int matrix[n][n]){
    trans[state]=1;
    for (int i=0;i<n;i++)
        if (matrix[state][i]==1 && trans[i]==0)
            find_epsilon(i,n,trans,matrix);
}
void main(){
    int n,k,p,q;
    printf("Enter the number of states in the NFA: ");
    scanf("%d",&n);
    int matrix[n][n],trans[n];
    printf("Enter the number of epsilon transitions: ");
    scanf("%d",&k);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            matrix[i][j]=0;
        }
    }
    for (int i=0;i<k;i++){
        scanf("%d %d",&p,&q);
        matrix[p][q]=1;
    }
    for (int i=0;i<n;i++){
        for (int k=0;k<n;k++){ trans[k]=0; }
        find_epsilon(i,n,trans,matrix);
        printf("\nEpsilon transition of %d : {",i);
        for(int j=0;j<n;j++){
            if (trans[j]==1)
                printf("% d,",j);
        }
        printf(" }");
    }
}
