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
int cathodecolumn=0;//this increments through the anode levels
int BAM_Bit, BAM_Counter=0; // Bit Angle Modulation variables to keep track of things

//These variables can be used for other things
unsigned long start;//for a millis timer to cycle through the animations


void setup(){

  SPI.setBitOrder(MSBFIRST);//Most Significant Bit First
  SPI.setDataMode(SPI_MODE0);// Mode 0 Rising edge of data, keep clock low
  SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz

  //finally set up the Outputs
  pinMode(latch_pin, OUTPUT);//Latch
  pinMode(data_pin, OUTPUT);//MOSI DATA
  pinMode(clock_pin, OUTPUT);//SPI Clock
  //pinMode(blank_pin, OUTPUT);//Output Enable  important to do this last, so LEDs do not flash on boot up
  SPI.begin();//start up the SPI library
  //interrupts();//let the show begin, this lets the multiplexing start

}//***end setup***end setup***end setup***end setup***end setup***end setup***end setup***end setup***end setup***end setup


void loop(){//***start loop***start loop***start loop***start loop***start loop***start loop***start loop***start loop***start loop

    //Each animation located in a sub routine
  // To control an LED, you simply:
  // LED(level you want 0-7, row you want 0-7, column you want 0-7, red brighness 0-15, green brighness 0-15, blue brighness 0-15);
  int i;
  for(i=255; i>=0; i--){
    SPI.transfer(i);
    PORTD |= 1<<latch_pin;//Latch pin HIGH
    PORTD &= ~(1<<latch_pin);//Latch pin LOW
    PORTD &= ~(1<<blank_pin);//Blank pin LOW to turn on the LEDs with the new data
    SPI.transfer(~0);
    delay(50);
  }
    SPI.transfer(~B10000000);
    delay(5000000);
 
}
