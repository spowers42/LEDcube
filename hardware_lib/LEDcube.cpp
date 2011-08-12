//This library is for the Arduino to run a 3x3x3 LED cube that
//uses common cathode columns and common anode horizontal planes
//
//Scott P.Powers
//6-10-2009
//last modified: 6-15-2009

#include "WProgram.h"
#include "LEDcube.h"


Cube::Cube(){
	int x;
	for(x=0; x<3; x++){
  		_anode[x]=x;
  	}
  	for(x=0; x<9; x++){
  		_cathode[x]=x+4;
  	}
  	
	for (_anodeCnt = 0; _anodeCnt < 3; _anodeCnt++) {
		pinMode(_anode[_anodeCnt], OUTPUT);
	}
	
  	for (_cathodeCnt = 0; _cathodeCnt < 9; _cathodeCnt++) {
  		pinMode(_cathode[_cathodeCnt], OUTPUT);
  	}
  	
  	_errorLED=13;
  	
  	pinMode(_errorLED, OUTPUT);
  	digitalWrite(_errorLED, LOW);
  	
  	setHigh();
  	setLow();
  	setDelay(250);
}


void Cube::setHigh(){
	for(_cathodeCnt=0; _cathodeCnt<9; _cathodeCnt++){
		digitalWrite(_cathode[_cathodeCnt],HIGH);
	}
}


void Cube::setLow(){
	for (_anodeCnt=0; _anodeCnt<3; _anodeCnt++){
		digitalWrite(_anode[_anodeCnt],LOW);
	}
}

void Cube::error(int e){
	digitalWrite(_errorLED, HIGH);
	delay(2000);
	digitalWrite(_errorLED, LOW);
}

void Cube::setDelay(int t){
	_delayTime=t;
}


void Cube::pixel(int x, int y, int z){
	if(x>3||y>3||z>3){
		error(1);
		return;
	}
	 digitalWrite(_cathode[3*x+y], LOW); 	// select column
	 digitalWrite(_anode[z], HIGH); 		// select plane
	 delayMicroseconds(_delayTime);         // momentary illumination
	 digitalWrite(_cathode[3*x+y], HIGH); 	// deselect column
	 digitalWrite(_anode[z], LOW);    	// deselect plane
}


void Cube::print(byte map, boolean overflow, int y){
	if(y>2){
		error(2);
		return;
	}
	
	boolean result[9];
	for(int i=0; i<8; i++){
		result[i]=bitRead(map, i);
	}
	result[8]= overflow;
	
		digitalWrite(_anode[y],HIGH);

			for(_cathodeCnt=0; _cathodeCnt<9; _cathodeCnt++){
				if(result[_cathodeCnt]==1){
					digitalWrite(_cathode[_cathodeCnt],LOW);
					delayMicroseconds(_delayTime);
					digitalWrite(_cathode[_cathodeCnt],HIGH);
				}
				else{ 
					digitalWrite(_cathode[_cathodeCnt],HIGH);
					delayMicroseconds(_delayTime);
				}
			}

			digitalWrite(_anode[y],LOW);
}	


void Cube::displayPlane(int y){
	if(y>2){
		error(3);
		return;
	}
	byte b=B11111111;
	bool o=1;

	print(b, o, y);
}
	
void Cube::displayColumn(int x, int z){
	byte b=B00000001;
	bool o=0;
	int cnt;
	
	b= b<<x*3;
	b= b<<z;
	if(x==2&&z==2){
		b=B00000000;
		o=1;
	}
	
	for(cnt=0; cnt<3; cnt++){
		print(b, o, cnt);
	}
}
