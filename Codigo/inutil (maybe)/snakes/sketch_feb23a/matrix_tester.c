#include <stdio.h>
#include <stdlib.h>

#include "matrix_tester.h"
/*
void create_matrix(char matriz[][verticalmax]){

	
	int i,j;

	for(i=0; i<horizontalmax; i++)
	{
		matriz[i][verticalmax]='-';
	}
	for(j=0; j<verticalmax; j++)
	{
		matriz[horizontalmax][j]='|';
	}
			
	return;
}*/

void printmatrix(int matriz[][verticalmax][3])
{	
	int i, j;		
	for(j=verticalmax-1; j>=0; j--)
	{
		for(i=0; i<horizontalmax; i++)
		{
			LED(i,j,matriz[i][j][0]);
                        LED(i,j,matriz[i][j][1]);
                        LED(i,j,matriz[i][j][2]);			
		}
	
	}	
	return;
}





