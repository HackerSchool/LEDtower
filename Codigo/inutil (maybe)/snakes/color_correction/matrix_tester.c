#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "matrix_tester.h"

void create_matrix(char matriz[][verticalmax+1]){

	
	int i,j;

	for(i=0; i<horizontalmax+1; i++)
	{
		matriz[i][verticalmax]='-';
	}
	for(j=0; j<verticalmax+1; j++)
	{
		matriz[horizontalmax][j]='|';
	}
			
	return;
}

void printmatrix(char matriz[][verticalmax+1])
{
	
	/*- testing purposes -*/
	
	FILE * fd = fopen("zpath_superrandom", "a");
	/*-*/
	
	
	int i, j;	
	system("clear");	
	for(j=verticalmax-1; j>=0; j--)
	{
		for(i=0; i<horizontalmax+1; i++)
		{
			printf("%c ", matriz[i][j]);
			fprintf(fd, "%c ", matriz[i][j]);  /*- testing purposes -*/
			
		}
		printf("\n");
		fprintf(fd, "\n");  /*- testing purposes -*/
	
	}
	for(i=0; i<horizontalmax+1; i++)
	{
		printf("%c ", matriz[i][verticalmax]);
	}
	printf("\n");
	
	/*- testing purposes -*/

	fprintf(fd, "\n\n\n");  /*- testing purposes -*/
	fclose(fd);

	/*-*/
	
	return;
}





