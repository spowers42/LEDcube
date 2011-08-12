/*
  LED_CUBE v2
 
 This program runs a cube of LEDs creating various patterns.  
 The patterns are also found in stand alone programs with identical code.
 v2:
 This version of the software uses byte data types to store the pattern, 
 and a common function to draw the pattern onto the cube.  This allows
 all patterns to take the same amount of time to excecute, since they all
 will write to each location.  The previous version of the software used
 a different function for each pattern, all of which took a different 
 amount of time to excecute.
 The setup, setHigh, and setLow functions are unchanged from v1.
 
 The Circuit:
 A cube of LEDs, each column shares a common cathode and each horizontal
 plane shares a common anode.  220 ohm resistors are used to prevent 
 damage to the LEDs
 
 Created: 06-30-2009
 Scott P. Powers 
 and
 Matt Lagro
 
 last modified: 7-15-2009
 
 Copyright (c) 2009 Scott P. Powers and Matt Lagro

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include <LEDcube.h>

Cube cube;
volatile int pat=5;
int x=0, y=0, z=0;
static int patMax=6;

//patterns
byte xPattern=B01010101; 
boolean xPatternOverflow=1;
byte sideToSide[6]={B00000000, B00000001, B00011011, B11111111, B11111110,
  B11100100, }; 
byte Burst[4]={B00010000, B11111111, B11101111, B00000000}; 
boolean SideToSideOverflow[6]={0,0,0,1,1,1 };
boolean BurstOverflow[4]={0,1,1,0};

byte BitMapTemp;
boolean BitMapTemp_overflow;//for the 9th cathode value


//////////////////////////////////////////////////////////////////////
// set an interrupt on pin 3
//////////////////////////////////////////////////////////////////////
void setup() {
//  Serial.begin(9600);
//  Serial.println("Starting...");
  pinMode(3, INPUT);
  attachInterrupt(1, nextPattern, RISING);
}

//////////////////////////////////////////////////////////////////////
//main loop
//////////////////////////////////////////////////////////////////////
void loop(){

  interrupts();
  
  if(pat>=patMax){
   pat=0;
 }
  
  
  switch(pat){
    case(0):                  //plane bounce
       bounce();
       break; 
    case(1):                  //column display
       column();
       break;
    case(2):                  //X pattern
      xpat();
      break;
    case(3):
      sidetoside();
      break;
    case(4):
      glow();
      break;
    case(5):
      burst();
      break;
  }

}

void nextPattern(){
    //Serial.println("next pattern!");
    pat++;
    return;
}

void bounce(){
     cube.setDelay(200);
         for(y=0; y<3; y++){
           for(int cnt=0; cnt<200; cnt++){
            cube.displayPlane(y);
           }
          }
        for(y=2; y>=0; y--){
          for(int cnt=0; cnt<200; cnt++){
            cube.displayPlane(y);
            }
          }
}

void column(){
  cube.setDelay(100);
        for(x=0; x<3; x++){
          for(z=0; z<3; z++){
            for(int cnt=0; cnt<200; cnt++){
            cube.displayColumn(x,z);
            }
          }
        }
}

void xpat(){
  cube.setDelay(200);
      for(int cnt=0; cnt<250; cnt++){
        for(y=0; y<3; y++){
          cube.print(xPattern, xPatternOverflow, y);
        }
      }
      xPattern= ~xPattern;
      xPatternOverflow= !xPatternOverflow;
}

void sidetoside(){
  cube.setDelay(200);
      for(int cnt=0; cnt<6; cnt++){
        for(int i=0; i<100; i++){
          for(y=0; y<3; y++){
            cube.print(sideToSide[cnt], SideToSideOverflow[cnt], y);
          }
        }
      }
}

void glow(){
  cube.setDelay(100);
      for(int cnt=0; cnt<500; cnt++){
        for(y=0; y<3; y++){
          cube.print(B11111111, 1, y);
        }
      }
}


void burst(){
  cube.setDelay(500);
  for(int stage=0; stage<4; stage++){
     for(int cnt=0; cnt<50; cnt++){
        for(int y=0; y<3; y++){
      cube.print(Burst[stage], BurstOverflow[stage], y);
      }
    }
  }
}
