/*
General:
	This library is to make pattern display on a 3x3x3 LED cube
	using the Arduino system easier.  The cube is constructed
	using a common cathode for each level of the cube, connected 
	to pins 1, 2, and 3.  The cathodes that are stacked ontop of
	eachother are shared, and take up pins 4 through 12.  Pin 13 
	is used for error reporting via the LED.
	
Pinout:
	digital 0: anode 1
	digital 1: anode 2
	digital 2: anode 3
	digital 3: interrupt 
	digital 4: cathode 1
	digital 5: cathode 2
	digital 6: cathode 3
	digital 7: cathode 4
	digital 8: cathode 5
	digital 9: cathode 6
	digital 10: cathode 7
	digital 11: cathode 8
	digital 12: cathode 9
	digital 13: error LED
	analog 0: not connected
	analog 1: not connected
	analog 2: not connected
	analog 3: not connected
	analog 4: not connected
	analog 5: option variable resistor to change delay time
	
Use:
	setDelay(int t) accepts an interger which sets the time
		between each LED display in microseconds
		
	pixel(int x, int y, int z) displays a single pixel based
		on x,y,z position.  values between 0 and 2
		
	print(byte map, boolean overflow, int y) displays the LEDs
		defined by a bitmap in byte map.  1 will light up
		the LED.  Overflow is for the 9th cathode since the 
		arduino uses an 8 bit processor.  Y represensts the 
		horizontal layer to display the bitmap on, range from 
		0 to 2.  
		
	displayPlane(int y)  lights up the whole horizontal plane defined
		by y.  value between 0 and 2.
		
	displayColumn(int x, int z)  lights up a vertical column at location
		x,z.  values between 0 and 2 for x and z.  

Scott P. Powers
6-10-2009
last modified: 6-14-2009
*/

#ifndef LEDcube_h
#define LEDcube_h
#include "WProgram.h"

class Cube{
	public:
		Cube();
		void setDelay(int t);
		void pixel(int x, int y, int z);
		void print(byte map, boolean overflow, int y);
		void displayPlane(int y);
		void displayColumn(int x, int z);
		
	private:
		int _cathode[9];
		int _anode[3];
		int _anodeCnt;
		int _cathodeCnt;
		int _delayTime;
		int _errorLED;
		
		void setHigh();
		void setLow();
		void error(int e);
	};
	
#endif
