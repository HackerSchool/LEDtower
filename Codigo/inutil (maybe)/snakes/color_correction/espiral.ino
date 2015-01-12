#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i,j;
	while(1)
	{
		for(i=0; i<8; i++)
		{
			for(j=0; j<16; i++)
			{
				LED(i,j,0,0,0);
			}
		}
		for(i=0; i<8; i++)
		{
			for(j=0; j<16; i++)
			{
				LED(i,j,15,15,15);
				delay(200);
				LED(i,j,0,0,0);
			}
		}	
}
