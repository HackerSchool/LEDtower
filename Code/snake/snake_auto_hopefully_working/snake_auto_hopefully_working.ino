

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>

typedef struct body
{
    int column, row;
    struct body *previous;
}body;

#define verticalmax 16
#define horizontalmax 8

#define _true 1
#define _false 0

body* add(body* head, int column, int row);
body* delete_(body* head);
void printmatrix(int matriz[][verticalmax][3]);
void snake(int horizontallimit, int verticallimit, int sizelimit, int grouthrate, int speed, int speedup_rate);
void endgame(int matriz[][verticalmax][3], int background_color[3]);
void LED(int column, int row, byte red, byte green, byte blue);



    /* mega awesome function */
struct body* add(struct body* head, int column, int row)
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

struct body* delete_(struct body* head)
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



void printmatrix(int matriz[][verticalmax][3])
{	
	int i, j;		
	for(j=verticalmax-1; j>=0; j--)
	{
		for(i=0; i<horizontalmax; i++)
		{
			LED(i,j,matriz[i][j][0],matriz[i][j][1],matriz[i][j][2]);		
		}
	
	}	
	return;
}

int snake(int horizontallimit, int verticallimit, int sizelimit, int grouthrate, int speed, int speedup_rate, int game_number)
{
	int background_color[3] = {5,0,5};
        int body_color[3] = {0,7,0}; 
	int head_color[3] = {15,15,0};
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
	srand(game_number);
	do{
		food_h = rand()%horizontalmax;
		food_v = rand()%verticalmax;		
	} while(
		(  matriz[food_h][food_v][0] == body_color[0] 
		&& matriz[food_h][food_v][1] == body_color[1] 
		&& matriz[food_h][food_v][2] == body_color[2]) 
		|| 
		(  matriz [food_h][food_v][0] == head_color[0] 
		&& matriz [food_h][food_v][1] == head_color[1] 
		&& matriz [food_h][food_v][2] == head_color[2])
		);
		
	matriz [food_h][food_v][0] = food_color[0];
    matriz [food_h][food_v][1] = food_color[1];
    matriz [food_h][food_v][2] = food_color[2];

	printmatrix(matriz);
	delay(1000);

			/* game! :D */
			
			int counter = 0;
	while(1)
	{
		delay(300);
		
		/* decision */
		int safe = _false;
		body* newhead = NULL;
		int attempts[4] = {0,0,0,0};
		int gameover = _true;
		
		while(safe == _false)
		{	
			gameover = _true;
			for(i=0; i<4; i++)
			{
				/*attempts[i] = 1;*/
				if(attempts[i] == 0) gameover = _false;
			}
			
			if (gameover == _true)
			{
				endgame(matriz, background_color);
				return rand();
			} 
				
			int direction, new_direction;
			if(head->row > head->previous->row)			
				{direction = 0; attempts[2]=1;}			/*north*/
			if(((head->column > head->previous->column) 
				&& !(head->column == 7 && head->previous->column == 0)) 
				|| (head->column == 0 && head->previous->column == 7))	
				{direction = 1;  /*east*/	attempts[3]=1;}
			if(head->row < head->previous->row)			
				{direction = 2; attempts[0]=1;}			/*south*/
			if(((head->column < head->previous->column) 
				&& !(head->column == 0 && head->previous->column == 7)) 
				|| (head->column == 7 && head->previous->column == 0))	
				{direction = 3;  /*west*/	attempts[1]=1;}
			
			
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
						if(matriz[head->column][head->row+1][0] != body_color[0] 
						|| matriz[head->column][head->row+1][1] != body_color[1] 
						|| matriz[head->column][head->row+1][2] != body_color[2])
						{						
							newhead = add(newhead, head->column, head->row+1);
							newhead->previous = head;
							matriz[last->column][last->row][0] = background_color[0];
                            matriz[last->column][last->row][1] = background_color[1];
                            matriz[last->column][last->row][2] = background_color[2];  

							if(matriz[newhead->column][newhead->row][0] == food_color[0] 
							&& matriz[newhead->column][newhead->row][1] == food_color[1] 
							&& matriz[newhead->column][newhead->row][2] == food_color[2])
							{
								matriz[last->column][last->row][0] = body_color[0];
                                                                matriz[last->column][last->row][1] = body_color[1];
                                                                matriz[last->column][last->row][2] = body_color[2];												
								last = add(head, last->column, last->row);
								do{
									food_h = rand()%horizontalmax;
									food_v = rand()%verticalmax;		
								} while(((matriz [food_h][food_v][0] == body_color[0] 
									   && matriz [food_h][food_v][1] == body_color[1] 
									   && matriz [food_h][food_v][2] == body_color[2]) 
									   || 
										 (matriz [food_h][food_v][0] == head_color[0] 
									   && matriz [food_h][food_v][1] == head_color[1] 
									   && matriz [food_h][food_v][2] == head_color[2] )) 
									   || (last->column == food_v && last->row == food_h));
									   
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
							last = delete_(head);				
							safe = _true;
						}
						else attempts[0]=1;
					}
					else attempts[0]=1;
					break;
				
				case 1:	
					if(((matriz[head->column+1][head->row][0] != body_color[0] 
					  || matriz[head->column+1][head->row][1] != body_color[1] 
					  || matriz[head->column+1][head->row][2] != body_color[2])) 
					&& !((head->column+1 == 8) 
					  && !(matriz[0][head->row][0] != body_color[0] 
					    || matriz[0][head->row][1] != body_color[1] 
					    || matriz[0][head->row][2] != body_color[2])))
					{
						if(head->column+1 == 8) newhead = add(newhead, 0, head->row);
						else newhead = add(newhead, head->column+1, head->row);
						newhead->previous = head;
						matriz[last->column][last->row][0] = background_color[0];
                        matriz[last->column][last->row][1] = background_color[1];
                        matriz[last->column][last->row][2] = background_color[2];
						
						if(matriz[newhead->column][newhead->row][0] == food_color[0] 
						&& matriz[newhead->column][newhead->row][1] == food_color[1] 
						&& matriz[newhead->column][newhead->row][2] == food_color[2])
						{
							matriz[last->column][last->row][0] = body_color[0];
                                                        matriz[last->column][last->row][1] = body_color[1];
                                                        matriz[last->column][last->row][2] = body_color[2];												
							last = add(head, last->column, last->row);
							do{
								food_h = rand()%horizontalmax;
								food_v = rand()%verticalmax;		
							} while(((matriz [food_h][food_v][0] == body_color[0] 
								   && matriz [food_h][food_v][1] == body_color[1] 
							       && matriz [food_h][food_v][2] == body_color[2]) 
								|| 
									  (matriz [food_h][food_v][0] == head_color[0] 
									&& matriz [food_h][food_v][1] == head_color[1] 
									&& matriz [food_h][food_v][2] == head_color[2])) 
								|| 
									(last->column == food_v && last->row == food_h));
										
							matriz [food_h][food_v][0] = food_color[0];
                            matriz [food_h][food_v][1] = food_color[1];
                            matriz [food_h][food_v][2] = food_color[2];					
		
						}
						matriz[head->column][head->row][0] = body_color[0];
						matriz[head->column][head->row][1] = body_color[1];
                        matriz[head->column][head->row][2] = body_color[2];
						head = newhead;
						matriz[head->column][head->row][0] = head_color[0];
                        matriz[head->column][head->row][1] = head_color[1];
                        matriz[head->column][head->row][2] = head_color[2];
						last = delete_(head);				
						safe = _true;
					}
					else attempts[1]=1;
					break;
				
				case 2:
					if(head->row>0)
					{
						if(matriz[head->column][head->row-1][0] != body_color[0] 
						|| matriz[head->column][head->row-1][1] != body_color[1] 
						|| matriz[head->column][head->row-1][2] != body_color[2])
						{	
							newhead = add(newhead, head->column, head->row-1);
							newhead->previous = head;
							matriz[last->column][last->row][0] = background_color[0];
                            matriz[last->column][last->row][1] = background_color[1];
                            matriz[last->column][last->row][2] = background_color[2]; 
							if(matriz[newhead->column][newhead->row][0] == food_color[0] 
							&& matriz[newhead->column][newhead->row][1] == food_color[1] 
							&& matriz[newhead->column][newhead->row][2] == food_color[2])
							{
								matriz[last->column][last->row][0] = body_color[0];
                                                                matriz[last->column][last->row][1] = body_color[1];
                                                                matriz[last->column][last->row][2] = body_color[2];												
								last = add(head, last->column, last->row);								
								do{
									food_h = rand()%horizontalmax;
									food_v = rand()%verticalmax;		
								} while((( matriz [food_h][food_v][0] == body_color[0] 
										&& matriz [food_h][food_v][1] == body_color[1] 
										&& matriz [food_h][food_v][2] == body_color[2]) 
									|| 
										(  matriz [food_h][food_v][0] == head_color[0] 
										&& matriz [food_h][food_v][1] == head_color[1] 
										&& matriz [food_h][food_v][2] == head_color[2])) 
									|| 
									(last->column == food_v && last->row == food_h));
									
								matriz [food_h][food_v][0] = food_color[0];
								matriz [food_h][food_v][1] = food_color[1];
								matriz [food_h][food_v][2] = food_color[2];
														
							}
							matriz[head->column][head->row][0] = body_color[0];
                            matriz[head->column][head->row][1] = body_color[1];
                            matriz[head->column][head->row][2] = body_color[2];
							head = newhead;
							matriz[head->column][head->row][0] = head_color[0];
                            matriz[head->column][head->row][1] = head_color[1];
                            matriz[head->column][head->row][2] = head_color[2];
							last = delete_(head);				
							safe = _true;
						}
						else attempts[2]=1;
					}
					else attempts[2]=1;
					break;
					
				case 3:
					if((matriz[head->column-1][head->row][0] != body_color[0] 
					 || matriz[head->column-1][head->row][1] != body_color[1] 
					 || matriz[head->column-1][head->row][2] != body_color[2]) 
					&& 
						!((head->column-1 == 8) 
						&& !(matriz[0][head->row][0] != body_color[0] 
						|| 	 matriz[0][head->row][1] != body_color[1] 
						|| 	 matriz[0][head->row][2] != body_color[2])))
					{		
						if(head->column-1 == -1) newhead = add(newhead, 7, head->row);
						else newhead = add(newhead, head->column-1, head->row);
						newhead->previous = head;
						matriz[last->column][last->row][0] = background_color[0];
                        matriz[last->column][last->row][1] = background_color[1];
                        matriz[last->column][last->row][2] = background_color[2];
						
						if(matriz[newhead->column][newhead->row][0] == food_color[0] 
						&& matriz[newhead->column][newhead->row][1] == food_color[1] 
						&& matriz[newhead->column][newhead->row][2] == food_color[2])
						{
							matriz[last->column][last->row][0] = body_color[0];
                                                        matriz[last->column][last->row][1] = body_color[1];
                                                        matriz[last->column][last->row][2] = body_color[2];												
							last = add(head, last->column, last->row);
							do{
								food_h = rand()%horizontalmax;
								food_v = rand()%verticalmax;		
							} while((( matriz [food_h][food_v][0] == body_color[0] 
									&& matriz [food_h][food_v][1] == body_color[1] 
									&& matriz [food_h][food_v][2] == body_color[2]) 
								|| 
									(  matriz [food_h][food_v][0] == head_color[0] 
									&& matriz [food_h][food_v][1] == head_color[1] 
									&& matriz [food_h][food_v][2] == head_color[2] )) 
								|| (last->column == food_v && last->row == food_h));
							
							matriz [food_h][food_v][0] = food_color[0];
                            matriz [food_h][food_v][1] = food_color[1];
                            matriz [food_h][food_v][2] = food_color[2];
													
						}
						matriz[head->column][head->row][0] = body_color[0];
                        matriz[head->column][head->row][1] = body_color[1];
                        matriz[head->column][head->row][2] = body_color[2];
						head = newhead;
						matriz[head->column][head->row][0] = head_color[0];
                        matriz[head->column][head->row][1] = head_color[1];
                        matriz[head->column][head->row][2] = head_color[2];
						last = delete_(head);				
						safe = _true;
					}
					else attempts[3]=1;
					break;			
			}
		
		}
		
		
		printmatrix(matriz);
		/*getchar();*/
			
	}
	return rand();
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
		delay(500);
		printmatrix(matriz);
		delay(500);
	}

	printmatrix(matriz_off);
	delay(500);
	return;
}

#include <SPI.h>// SPI Library used to clock data out to the shift registers

#define latch_pin 2// can use any pin you want to latch the shift registers
#define blank_pin 4// same, can use any pin you want for this, just make sure you pull up via a 1k to 5V
#define data_pin 11// used by SPI, must be pin 11
#define clock_pin 13// used by SPI, must be 13

//***variables***variables***variables***variables***variables***variables***variables***variables
//These variables are used by multiplexing and Bit Angle Modulation Code
int shift_out;//used in the code a lot in for(i= type loops
byte cathode[8];//byte to write to the anode shift register, 8 of them, shifting the ON level in each byte in the array

//This is how the brightness for every LED is stored,  
//Each LED only needs a 'bit' to know if it should be ON or OFF, so 64 Bytes gives you 512 bits= 512 LEDs
//Since we are modulating the LEDs, using 4 bit resolution, each color has 4 arrays containing 64 bits each
byte red0[16], red1[16], red2[16], red3[16];
byte blue0[16], blue1[16], blue2[16], blue3[16];
byte green0[16], green1[16], green2[16], green3[16];
//notice how more resolution will eat up more of your precious RAM

int column=0;//keeps track of which coluna we are shifting data to
//int cathodecolumn=0;//this increments through the anode levels
int BAM_Bit, BAM_Counter=0; // Bit Angle Modulation variables to keep track of things

//These variables can be used for other things
unsigned long start;//for a millis timer to cycle through the animations

//****setup****setup****setup****setup****setup****setup****setup****setup****setup****setup****setup****setup****setup
void setup(){

  SPI.setBitOrder(MSBFIRST);//Most Significant Bit First
  SPI.setDataMode(SPI_MODE0);// Mode 0 Rising edge of data, keep clock low
  SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz

  //Serial.begin(115200);// if you need it?
  noInterrupts();// kill interrupts until everybody is set up

  //We use Timer 1 to refresh the cube
  TCCR1A = B00000000;//Register A all 0's since we're not toggling any pins
  TCCR1B = B00001011;//bit 3 set to place in CTC mode, will call an interrupt on a counter match
  //bits 0 and 1 are set to divide the clock by 64, so 16MHz/64=250kHz
  TIMSK1 = B00000010;//bit 1 set to call the interrupt on an OCR1A match
  OCR1A=30; // you can play with this, but I set it to 30, which means:
  //our clock runs at 250kHz, which is 1/250kHz = 4us
  //with OCR1A set to 30, this means the interrupt will be called every (30+1)x4us=124us, 
  // which gives a multiplex frequency of about 8kHz

  // here I just set up the anode array, this is what's written to the anode shift register, to enable each level
  cathode[0]=B00000001;
  cathode[1]=B00000010;
  cathode[2]=B00000100;
  cathode[3]=B00001000;
  cathode[4]=B00010000;
  cathode[5]=B00100000;
  cathode[6]=B01000000;
  cathode[7]=B10000000;
  // don't hate on how I assigned the values to this register! haha

  //finally set up the Outputs
  pinMode(latch_pin, OUTPUT);//Latch
  pinMode(data_pin, OUTPUT);//MOSI DATA
  pinMode(clock_pin, OUTPUT);//SPI Clock
  //pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
  SPI.begin();//start up the SPI library
  interrupts();//let the show begin, this lets the multiplexing start
  
}//***end setup***end setup***end setup***end setup***end setup***end setup***end setup***end setup***end setup***end setup


void loop(){//***start loop***start loop***start loop***start loop***start loop***start loop***start loop***start loop***start loop

  //Each animation located in a sub routine
  // To control an LED, you simply:
  // LED(level you want 0-7, row you want 0-7, column you want 0-7, red brighness 0-15, green brighness 0-15, blue brighness 0-15);

  
  //mxclear(15, 15, 15);
  
//  battery(30, 15, 0, 0, 0);
  
//  fullrandom(50);

//curtain(dlay, r,g,b, steps, char faderate, char clockwise)
//  curtain(100, 15, 15, 15, 1000, 2, 0);

//wave(dlay, r,g,b, unsigned int nr_waves, float freq)
//wave(200, 15, 15, 15, 100, 1./4);

//void snake(int horizontallimit, int verticallimit, int sizelimit, int grouthrate, int speed, int speedup_rate)
 int prev_game = rand();
 prev_game = snake(horizontalmax, verticalmax, 12, 2, 1, 200, prev_game);


}//***end loop***end loop***end loop***end loop***end loop***end loop***end loop***end loop***end loop***end loop***end loop***end loop



void LED(int column, int row, byte red, byte green, byte blue){ //****LED Routine****LED Routine****LED Routine****LED Routine
  //This is where it all starts
  //This routine is how LEDs are updated, with the inputs for the LED location and its R G and B brightness levels
  
  // First, check and make sure nothing went beyond the limits, just clamp things at either 0 or 7 for location, and 0 or 15 for brightness
  if(row<0)
    row=0;
  if(row>15)
    row=15;
  if(column<0)
    column=0;
  if(column>7)
    column=7;  
  if(red<0)
    red=0;
  if(red>15)
    red=15;
  if(green<0)
    green=0;
  if(green>15)
    green=15;
  if(blue<0)
    blue=0;
  if(blue>15)
    blue=15;  

  
  //There are 512 LEDs in the cube, so when we write to level 2, column 5, row 4, that needs to be translated into a number from 0 to 511

  //This looks confusing, I know...
  int whichbyte = int(column*2+int(row/8));

  // The first level LEDs are first in the sequence, then 2nd level, then third, and so on
  //the (level*64) is what indexes the level's starting place, so level 0 are LEDs 0-63, level 1 are LEDs 64-127, and so on

  //The column counts left to right 0-7 and the row is back to front 0-7
  //This means that if you had level 0, row 0, the bottom back row would count from 0-7, 

  //so if you looked down on the cube, and only looked at the bottom level
  // 00 01 02 03 04 05 06 07
  // 08 09 10 11 12 13 14 15
  // 16 17 18 19 20 21 22 23
  // 24 25 26 27 28 29 30 31
  // 32 33 34 35 36 37 38 39
  // 40 41 42 43 44 45 46 47  
  // 48 49 50 51 52 53 54 55  
  // 56 57 58 59 60 61 62 63

  //Then, if you incremented the level, the top right of the grid above would start at 64
  //The reason for doing this, is so you don't have to memorize a number for each LED, allowing you to use level, row, column

  //Now, what about the divide by 8 in there?
  //...well, we have 8 bits per byte, and we have 64 bytes in memory for all 512 bits needed for each LED, so
  //we divide the number we just found by 8, and take the integ7er of it, so we know which byte, that bit is located
  //confused? that's ok, let's take an example, if we wanted to write to the LED to the last LED in the cube, we would write a 7, 7, 7
  // giving (7*64)+(7*8)=7 = 511, which is right, but now let's divide it by 8, 511/8 = 63.875, and take the int of it so, we get 63,
  //this is the last byte in the array, which is right since this is the last LED

  // This next variable is the same thing as before, but here we don't divide by 8, so we get the LED number 0-511
  int whichbit=row % 8;
  //This will all make sense in a sec
  
  //This is 4 bit color resolution, so each color contains x4 64 byte arrays, explanation below:
  bitWrite(red0[whichbyte], whichbit, bitRead(red, 0));
  bitWrite(red1[whichbyte], whichbit, bitRead(red, 1));
  bitWrite(red2[whichbyte], whichbit, bitRead(red, 2)); 
  bitWrite(red3[whichbyte], whichbit, bitRead(red, 3)); 

  bitWrite(green0[whichbyte], whichbit, bitRead(green, 0));
  bitWrite(green1[whichbyte], whichbit, bitRead(green, 1));
  bitWrite(green2[whichbyte], whichbit, bitRead(green, 2)); 
  bitWrite(green3[whichbyte], whichbit, bitRead(green, 3));

  bitWrite(blue0[whichbyte], whichbit, bitRead(blue, 0));
  bitWrite(blue1[whichbyte], whichbit, bitRead(blue, 1));
  bitWrite(blue2[whichbyte], whichbit, bitRead(blue, 2)); 
  bitWrite(blue3[whichbyte], whichbit, bitRead(blue, 3));
  
  
  //Are you now more confused?  You shouldn't be!  It's starting to make sense now.  Notice how each line is a bitWrite, which is,
  //bitWrite(the byte you want to write to, the bit of the byte to write, and the 0 or 1 you want to write)
  //This means that the 'whichbyte' is the byte from 0-63 in which the bit corresponding to the LED from 0-511
  //Is making sense now why we did that? taking a value from 0-511 and converting it to a value from 0-63, since each LED represents a bit in 
  //an array of 64 bytes.
  //Then next line is which bit 'wholebyte-(8*whichbyte)'  
  //This is simply taking the LED's value of 0-511 and subracting it from the BYTE its bit was located in times 8
  //Think about it, byte 63 will contain LEDs from 504 to 511, so if you took 505-(8*63), you get a 1, meaning that,
  //LED number 505 is is located in bit 1 of byte 63 in the array

  //is that it?  No, you still have to do the bitRead of the brightness 0-15 you are trying to write,
  //if you wrote a 15 to RED, all 4 arrays for that LED would have a 1 for that bit, meaning it will be on 100%
  //This is why the four arrays read 0-4 of the value entered in for RED, GREEN, and BLUE
  //hopefully this all makes some sense?

}//****LED routine end****LED routine end****LED routine end****LED routine end****LED routine end****LED routine end****LED routine end

ISR(TIMER1_COMPA_vect){//***MultiPlex BAM***MultiPlex BAM***MultiPlex BAM***MultiPlex BAM***MultiPlex BAM***MultiPlex BAM***MultiPlex BAM
   
  //This routine is called in the background automatically at frequency set by OCR1A
  //In this code, I set OCR1A to 30, so this is called every 124us, giving each level in the cube 124us of ON time
  //There are 8 levels, so we have a maximum brightness of 1/8, since the level must turn off before the next level is turned on
  //The frequency of the multiplexing is then 124us*8=992us, or 1/992us= about 1kHz


  PORTD |= 1<<blank_pin;//The first thing we do is turn all of the LEDs OFF, by writing a 1 to the blank pin
  //Note, in my bread-boarded version, I was able to move this way down in the cube, meaning that the OFF time was minimized
  //do to signal integrity and parasitic capcitance, my rise/fall times, required all of the LEDs to first turn off, before updating
  //otherwise you get a ghosting effect on the previous level

  //This is 4 bit 'Bit angle Modulation' or BAM, There are 8 levels, so when a '1' is written to the color brightness, 
  //each level will have a chance to light up for 1 cycle, the BAM bit keeps track of which bit we are modulating out of the 4 bits
  //Bam counter is the cycle count, meaning as we light up each level, we increment the BAM_Counter
  if(BAM_Counter==8)
    BAM_Bit++;
  else
    if(BAM_Counter==24)
      BAM_Bit++;
    else
      if(BAM_Counter==56)
        BAM_Bit++;

  BAM_Counter++;//Here is where we increment the BAM counter

  switch (BAM_Bit){//The BAM bit will be a value from 0-3, and only shift out the arrays corresponding to that bit, 0-3
    //Here's how this works, each case is the bit in the Bit angle modulation from 0-4, 
    //Next, it depends on which level we're on, so the byte in the array to be written depends on which level, but since each level contains 64 LED,
    //we only shif out 8 bytes for each color
  case 0:
    SPI.transfer(red0[column*2]);
    SPI.transfer(red0[column*2+1]);
    SPI.transfer(green0[column*2]);
    SPI.transfer(green0[column*2+1]);
    SPI.transfer(blue0[column*2]);
    SPI.transfer(blue0[column*2+1]);
    break;
  case 1:
    SPI.transfer(red1[column*2]);
    SPI.transfer(red1[column*2+1]);
    SPI.transfer(green1[column*2]);
    SPI.transfer(green1[column*2+1]);
    SPI.transfer(blue1[column*2]);
    SPI.transfer(blue1[column*2+1]);
    break;
  case 2:
    SPI.transfer(red2[column*2]);
    SPI.transfer(red2[column*2+1]);
    SPI.transfer(green2[column*2]);
    SPI.transfer(green2[column*2+1]);
    SPI.transfer(blue2[column*2]);
    SPI.transfer(blue2[column*2+1]);
    break;
  case 3:
    SPI.transfer(red3[column*2]);
    SPI.transfer(red3[column*2+1]);
    SPI.transfer(green3[column*2]);
    SPI.transfer(green3[column*2+1]);
    SPI.transfer(blue3[column*2]);
    SPI.transfer(blue3[column*2+1]);
    //Here is where the BAM_Counter is reset back to 0, it's only 4 bit, but since each cycle takes 8 counts,
    //, it goes 0 8 16 32, and when BAM_counter hits 64 we reset the BAM
    if(BAM_Counter==120){
      BAM_Counter=0;
      BAM_Bit=0;
    }
    break;
  }//switch_case

  SPI.transfer(cathode[column]);//finally, send out the anode level byte

  PORTD |= 1<<latch_pin;//Latch pin HIGH
  PORTD &= ~(1<<latch_pin);//Latch pin LOW
  PORTD &= ~(1<<blank_pin);//Blank pin LOW to turn on the LEDs with the new data

  column++;//inrement the anode level
  
  if(column==8)//go back to 0 if max is reached
    column=0;
  pinMode(blank_pin, OUTPUT);//moved down here so outputs are all off until the first call of this function
}//***MultiPlex BAM END***MultiPlex BAM END***MultiPlex BAM END***MultiPlex BAM END***MultiPlex BAM END***MultiPlex BAM END***MultiPlex BAM END


/***** Animations *****/

/*mx all of one color*/
void mxclear(char r, char g, char b)
{
  char lev, col;
  for(lev=0; lev<16; lev++)
    for(col=0; col<8; col++)
      LED(col, lev, r, g, b);
}

/*levels light up successively with on color, with
delay dlay between levels*/
void battery(unsigned int dlay, char r, char g, char b, char down)
{
  char lev, col;
  
  if(down==_true)
    lev = 15;
  else
    lev = 0;
    
  while(1)
  {
    if(lev==-1 || lev==16)
      break;
  
    for(col=0; col<8; col++)
      LED(col, lev, r, g, b);

    delay(dlay);
    if(down==_true)
      lev--;
    else
      lev++;
  }
}


void fullrandom(unsigned long dlay)
{
    LED(random()%8,random()%16,random()%11,random()%16,random()%11);
    delay(dlay);
}


void curtain(unsigned int dlay, char r, char g, char b, 
unsigned int steps, char faderate, char clockwise)
{
  char higher, lower;
  char lev, col;
  char r_, g_, b_;
  unsigned int current_step;

  higher = lower = 0;

  if(faderate<=0)
    faderate = 1;

  for(current_step=0; current_step<=steps; current_step++)
  {
    for(col=higher; (col/*+current_step*/)>=lower; col--)
    {

      r_ = positive(r-(higher-col)*faderate);
      g_ = positive(g-(higher-col)*faderate);
      b_ = positive(b-(higher-col)*faderate);
      
      higher++; // do not move down
              
      if(r_+g_+b_==0)
      {
        lower++;
        continue; // or break;
      }
         
      for(lev=0; lev<16; lev++)
      { 
        LED(col%8, lev, r, g, b);
      }
  
    }
    
    delay(dlay);
  }

}

int positive(int nr)
{
  if(nr<0)
    return 0;
  return nr;
}

void wave(unsigned int dlay, char r, char g, char b, unsigned int nr_waves, float freq)
{
  char lev, col;
  unsigned int wave_nr;
  char r_, g_, b_;
  
  for(wave_nr=0; wave_nr<=nr_waves; wave_nr++)
  {
    for(lev=0; lev<16; lev++)
    {
      r_ = 7 + 7*cos((wave_nr+lev)*freq);
      g_ = 7 + 7*cos((wave_nr+lev)*freq);
      b_ = 7 + 7*cos((wave_nr+lev)*freq);
      
      for(col=0; col<8; col++)
        LED(col, lev, r_, g_, b_);

        
      delay(dlay);
    }  
  }
}







/* super animation*/











/*  end of super animation   */

