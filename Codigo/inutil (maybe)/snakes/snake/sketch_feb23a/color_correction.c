



#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "color_correction.h"
#include "matrix_tester.h"

body* add(body* head, int column, int row)
{
    struct body *temp, *aux;
    temp=(struct body *)malloc(sizeof(struct body));
    temp->column=column;
    temp->row=row;
    temp->previous = NULL;
    if (head == NULL)
    {
		head=temp;
    }
    else
    {
		aux=head;
		while(aux->previous != NULL)
		{
			aux=aux->previous;
		}
		aux->previous=temp;
		
    }
    return temp;
}

body* delete(body* head)
{
    struct body *temp, *temp_2;
    temp=head;
    temp_2=temp;
    if(temp != NULL)
    {
		if(temp->previous == NULL)
		{
			free(temp);
			return NULL;
		}
		while(temp_2->previous != NULL)
		{
			temp  = temp_2;
			temp_2 = temp_2->previous;
		}
		temp->previous = NULL;
		free(temp_2);

		return temp;
	}
	return NULL;
}



int mymain()
{
	while(1)
	{
		snake(horizontalmax, verticalmax, 12, 2, 1, 200);
	}
	exit(0);
}

void snake(int horizontallimit, int verticallimit, int sizelimit, int grouthrate, int speed, int speedup_rate)
{
	int background_color[3] = {5,0,5};
        int body_color[3] = {0,7,0}; 
	int head_color[3] = {0,15,0};
	int food_color[3] = {15,0,0};

	int matriz[horizontalmax][verticalmax][3];
	/*create_matrix(matriz);*/
	
	int i,j;
	
	/* set background ~paint*/
	for(i=0; i<horizontalmax; i++)
	{
		for(j=0; j<verticalmax; j++)
		{
			matriz[i][j][0] = background_color[0];
                        matriz[i][j][1] = background_color[1];
                        matriz[i][j][2] = background_color[2];
		}
	}	
		
	/* create snake ~paint*/	
	body* head = NULL;
	body* last = NULL;
	head = add(head, 4, 7); 
	matriz[4][7][0] = head_color[0];
        matriz[4][7][1] = head_color[1];
        matriz[4][7][2] = head_color[2];
	last = add(head, 3, 7); 
	matriz[3][7][0] = body_color[0];
        matriz[3][7][1] = body_color[1];
        matriz[3][7][2] = body_color[2];
	last = add(head, 2, 7); 
	matriz[2][7][0] = body_color[0];
        matriz[2][7][1] = body_color[1];
        matriz[2][7][2] = body_color[2];
	last = add(head, 1, 7); 
	matriz[1][7][0] = body_color[0];
        matriz[1][7][1] = body_color[1];
        matriz[1][7][2] = body_color[2];
	last = add(head, 0, 7); 
	matriz[0][7][0] = body_color[0];
        matriz[0][7][1] = body_color[1];
	matriz[0][7][2] = body_color[2];
        /*last = add(head, 7, 7); 
	matriz[7][7] = body_color;
	last = add(head, 6, 7); 
	matriz[6][7] = body_color;
	*/
	
	/* create food ~paint*/

	int food_h = 0;
	int food_v = 0;
	srand(7);
	do{
		food_h = rand()%horizontalmax;
		food_v = rand()%verticalmax;		
	} while((matriz[food_h][food_v][0] == body_color[0] && matriz[food_h][food_v][1] == body_color[1] && matriz[food_h][food_v][2] == body_color[2]) || (matriz [food_h][food_v][0] == head_color[0] && matriz [food_h][food_v][1] == head_color[1] && matriz [food_h][food_v][2] == head_color[2]));
	matriz [food_h][food_v][0] = food_color[0];
        matriz [food_h][food_v][1] = food_color[1];
        matriz [food_h][food_v][2] = food_color[2];

	printmatrix(matriz);
	_delay_ms(1000000);

			/* game! :D */
			
			int counter = 0;
	while(1)
	{
		_delay_ms(100);
		
		/* decision */
		int safe = false;
		body* newhead = NULL;
		int attempts[4] = {0,0,0,0};
		int gameover = true;
		
		while(safe == false)
		{	
			gameover = true;
			for(i=0; i<4; i++)
			{
				/*attempts[i] = 1;*/
				if(attempts[i] == 0) gameover = false;
			}
			
			if (gameover == true)
			{
				endgame(matriz, background_color);
				return;
			} 
				
			int direction, new_direction;
			if(head->row > head->previous->row)			{direction = 0; attempts[2]=1;}										 /*north*/
			if(((head->column > head->previous->column) && !(head->column == 7 && head->previous->column == 0)) || (head->column == 0 && head->previous->column == 7))	{direction = 1;  /*east*/	attempts[3]=1;}
			if(head->row < head->previous->row)			{direction = 2; attempts[0]=1;}										 /*south*/
			if(((head->column < head->previous->column) && !(head->column == 0 && head->previous->column == 7)) || (head->column == 7 && head->previous->column == 0))	{direction = 3;  /*west*/	attempts[1]=1;}
			
			
			new_direction = direction; /*default to front*/
			
			i = rand()%7;
			/*if((direction == 1 || direction == 3) && food_v != head->row) i = rand()%3;
			if((direction == 0 || direction == 2) && food_h != head->column) i = rand()%3;*/
			
			if(direction == 1 && food_v < head->row){ if(rand()%5 > 1) i=1; }
			if(direction == 1 && food_v > head->row){ if(rand()%5 > 1) i=0; }
			if(direction == 3 && food_v < head->row){ if(rand()%5 > 1) i=0; }
			if(direction == 3 && food_v > head->row){ if(rand()%5 > 1) i=1; }
			if((direction == 0 || direction == 2) && food_h != head->column){ i = rand()%3;  }			

			if(i == 0) new_direction = direction-1; /* left */  if(new_direction == -1) new_direction = 3;
			if(i == 1) new_direction = direction+1;	/* right */ if(new_direction ==  4) new_direction = 0;
			
			/* is valid? */
			switch(new_direction)
			{
				case 0:
					if(head->row+1<verticalmax)
					{
						if(matriz[head->column][head->row+1][0] != body_color[0] && matriz[head->column][head->row+1][1] != body_color[1] && matriz[head->column][head->row+1][2] != body_color[2])
						{						
							newhead = add(newhead, head->column, head->row+1);
							newhead->previous = head;
							matriz[last->column][last->row][0] = background_color[0];
                                                        matriz[last->column][last->row][1] = background_color[1];
                                                        matriz[last->column][last->row][2] = background_color[2];  

							if(matriz[newhead->column][newhead->row][0] == food_color[0] && matriz[newhead->column][newhead->row][1] == food_color[1] && matriz[newhead->column][newhead->row][2] == food_color[2])
							{
								matriz[last->column][last->row][0] = body_color[0];
                                                                matriz[last->column][last->row][1] = body_color[1];
                                                                matriz[last->column][last->row][2] = body_color[2];												
								last = add(head, last->column, last->row);
								do{
									food_h = rand()%horizontalmax;
									food_v = rand()%verticalmax;		
								} while(((matriz [food_h][food_v][0] == body_color[0] && matriz [food_h][food_v][1] == body_color[1] && matriz [food_h][food_v][2] == body_color[2]) || (matriz [food_h][food_v][0] == head_color[0] && matriz [food_h][food_v][1] == head_color[1] && matriz [food_h][food_v][2] == head_color[2] )) || (last->column == food_v && last->row == food_h));
								matriz[food_h][food_v][0] = food_color[0];
                                                                matriz[food_h][food_v][1] = food_color[1];
                                                                matriz[food_h][food_v][2] = food_color[2];
														
							}						
							matriz[head->column][head->row][0] = body_color[0];
                                                        matriz[head->column][head->row][1] = body_color[1];
                                                        matriz[head->column][head->row][2] = body_color[2];
							head = newhead;
							matriz[head->column][head->row][0] = head_color[0];
                                                        matriz[head->column][head->row][1] = head_color[1];
                                                        matriz[head->column][head->row][2] = head_color[2];
							last = delete(head);				
							safe = true;
						}
						else attempts[0]=1;
					}
					else attempts[0]=1;
					break;
				
				case 1:	
					if(((matriz[head->column+1][head->row][0] != body_color[0] && matriz[head->column+1][head->row][1] != body_color[1] && matriz[head->column+1][head->row][2] != body_color[2])) && !((head->column+1 == 8) && !(matriz[0][head->row][0] != body_color[0] && matriz[0][head->row][1] != body_color[1] && matriz[0][head->row][2] != body_color[2])))
					{
						if(head->column+1 == 8) newhead = add(newhead, 0, head->row);
						else newhead = add(newhead, head->column+1, head->row);
						newhead->previous = head;
						matriz[last->column][last->row][0] = background_color[0];
                                                matriz[last->column][last->row][1] = background_color[1];
                                                matriz[last->column][last->row][2] = background_color[2];
						if(matriz[newhead->column][newhead->row][0] == food_color[0] && matriz[newhead->column][newhead->row][1] == food_color[1] && matriz[newhead->column][newhead->row][2] == food_color[2])
						{
							matriz[last->column][last->row][0] = body_color[0];
                                                        matriz[last->column][last->row][1] = body_color[1];
                                                        matriz[last->column][last->row][2] = body_color[2];												
							last = add(head, last->column, last->row);
							do{
								food_h = rand()%horizontalmax;
								food_v = rand()%verticalmax;		
							} while(((matriz [food_h][food_v][0] == body_color[0] && matriz [food_h][food_v][1] == body_color[1] && matriz [food_h][food_v][2] == body_color[2]) || (matriz [food_h][food_v][0] == head_color[0] && matriz [food_h][food_v][1] == head_color[1] && matriz [food_h][food_v][2] == head_color[2] )) || (last->column == food_v && last->row == food_h));
							matriz [food_h][food_v][0] = food_color[0];
                                                        matriz [food_h][food_v][1] = food_color[1];
                                                        matriz [food_h][food_v][2] = food_color[2];					
		
						}
						matriz[head->column][head->row][0] = body_color[0];
                                                matriz[head->column][head->row][1] = body_color[1];
                                                matriz[head->column][head->row][2] = body_color[2];
						head = newhead;
						matriz[head->column][head->row][0] = body_color[0];
                                                matriz[head->column][head->row][1] = body_color[1];
                                                matriz[head->column][head->row][2] = body_color[2];
						last = delete(head);				
						safe = true;
					}
					else attempts[1]=1;
					break;
				
				case 2:
					if(head->row>0)
					{
						if(matriz[head->column][head->row-1][0] != body_color[0] && matriz[head->column][head->row-1][1] != body_color[1] && matriz[head->column][head->row-1][2] != body_color[2])
						{	
							newhead = add(newhead, head->column, head->row-1);
							newhead->previous = head;
							matriz[last->column][last->row][0] = background_color[0];
                                                        matriz[last->column][last->row][1] = background_color[1];
                                                        matriz[last->column][last->row][2] = background_color[2]; 
							if(matriz[newhead->column][newhead->row][0] == food_color[0] && matriz[newhead->column][newhead->row][1] == food_color[1] && matriz[newhead->column][newhead->row][2] == food_color[2])
							{
								matriz[last->column][last->row][0] == body_color[0];
                                                                matriz[last->column][last->row][1] == body_color[1];
                                                                matriz[last->column][last->row][2] == body_color[2];												
								last = add(head, last->column, last->row);								
								do{
									food_h = rand()%horizontalmax;
									food_v = rand()%verticalmax;		
								} while(((matriz [food_h][food_v][0] == body_color[0] && matriz [food_h][food_v][1] == body_color[1] && matriz [food_h][food_v][2] == body_color[2]) || (matriz [food_h][food_v][0] == head_color[0] && matriz [food_h][food_v][1] == head_color[1] && matriz [food_h][food_v][2] == head_color[2] )) || (last->column == food_v && last->row == food_h));
								matriz [food_h][food_v][0] = food_color[0];
                                                                matriz [food_h][food_v][1] = food_color[1];
                                                                matriz [food_h][food_v][2] = food_color[2];
														
							}
							matriz[head->column][head->row][0] = body_color[0];
                                                        matriz[head->column][head->row][1] = body_color[1];
                                                        matriz[head->column][head->row][2] = body_color[2];
							head = newhead;
							matriz[head->column][head->row][0] = body_color[0];
                                                        matriz[head->column][head->row][1] = body_color[1];
                                                        matriz[head->column][head->row][2] = body_color[2];
							last = delete(head);				
							safe = true;
						}
						else attempts[2]=1;
					}
					else attempts[2]=1;
					break;
					
				case 3:
					if((matriz[head->column-1][head->row][0] != body_color[0] && matriz[head->column-1][head->row][1] != body_color[1] && matriz[head->column-1][head->row][2] != body_color[2]) && !((head->column-1 == 8) && !(matriz[0][head->row][0] != body_color[0] && matriz[0][head->row][1] != body_color[1] && matriz[0][head->row][2] != body_color[2])))
					{		
						if(head->column-1 == -1) newhead = add(newhead, 7, head->row);
						else newhead = add(newhead, head->column-1, head->row);
						newhead->previous = head;
						matriz[last->column][last->row][0] = background_color[0];
                                                matriz[last->column][last->row][1] = background_color[1];
                                                matriz[last->column][last->row][2] = background_color[2];
						if(matriz[newhead->column][newhead->row][0] == food_color[0] && matriz[newhead->column][newhead->row][1] == food_color[1] && matriz[newhead->column][newhead->row][2] == food_color[2])
						{
							matriz[last->column][last->row][0] = body_color[0];
                                                        matriz[last->column][last->row][1] = body_color[1];
                                                        matriz[last->column][last->row][2] = body_color[2];												
							last = add(head, last->column, last->row);
							do{
								food_h = rand()%horizontalmax;
								food_v = rand()%verticalmax;		
							} while(((matriz [food_h][food_v][0] == body_color[0] && matriz [food_h][food_v][1] == body_color[1] && matriz [food_h][food_v][2] == body_color[2]) || (matriz [food_h][food_v][0] == head_color[0] && matriz [food_h][food_v][1] == head_color[1] && matriz [food_h][food_v][2] == head_color[2] )) || (last->column == food_v && last->row == food_h));
							matriz [food_h][food_v][0] = food_color[0];
                                                        matriz [food_h][food_v][1] = food_color[1];
                                                        matriz [food_h][food_v][2] = food_color[2];
													
						}
						matriz[head->column][head->row][0] = body_color[0];
                                                matriz[head->column][head->row][1] = body_color[1];
                                                matriz[head->column][head->row][2] = body_color[2];
						head = newhead;
						matriz[head->column][head->row][0] = body_color[0];
                                                matriz[head->column][head->row][1] = body_color[1];
                                                matriz[head->column][head->row][2] = body_color[2];
						last = delete(head);				
						safe = true;
					}
					else attempts[3]=1;
					break;			
			}
		
		}
		
		
		printmatrix(matriz);
		/*getchar();*/
			
	}
	return;
}

void endgame(int matriz[][verticalmax][3], int background_color[3])
{
	int i,j;
	int matriz_off[horizontalmax][verticalmax][3];
	for(i=0; i<horizontalmax; i++)
	{
		for(j=0; j<verticalmax; j++)
		{
			matriz_off[i][j][0] = background_color[0];
                        matriz_off[i][j][1] = background_color[1];
                        matriz_off[i][j][2] = background_color[2];
		}
	}
	
	for(i=0; i<3; i++)
	{
		printmatrix(matriz_off);
		_delay_ms(500);
		printmatrix(matriz);
		_delay_ms(500);
	}

	printmatrix(matriz_off);
	_delay_ms(500);
	return;
}
