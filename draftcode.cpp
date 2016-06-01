#include <Arduino.h>

#define ax0 12
#define ax1 3
#define ax2 4
#define ax3 11
#define ay0 5
#define ay1 6
#define ay2 10
#define cs1 7
#define cs2 8
#define data 9
#define strobe 2
#define RST A0//CHANGE THIS
//returns

#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define R5 4
#define R6L 5
#define R6R 6
#define R7L 7
#define R7R 8
#define R8L 9
#define R8R 10
#define R9L 11
#define R9R 12
#define GTR_in 13
#define AUX1 14
#define AUX2 15
//sends
#define S1 0
#define S2 1
#define S3 2
#define S4 3
#define S5 4
#define S6L 5
#define S6R 6
#define S7L 7
#define S7R 8
#define S8L 9
#define S8R 10
#define S9L 11
#define S9R 12
#define A1 13
#define A2 14
#define A3 15

#define LOOPNUMBER 5

int loopCount = 0;
int loopOrder[LOOPNUMBER] = {0, 0, 0, 0, 0,};
bool progMode = false;

void setSwitch(bool dataVal, int x, int y, int chip);
void changeLoop(bool dataVal, int x, int y);
void setOrder(int order[LOOPNUMBER]);
void timerISR();

void setup() 
{

 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(22, A0);

 for(int i = 2; i > 13; i++)
 {
 	digitalWrite(i, LOW);

 }

	//Timer1.initialize(1000);
	//Timer1.attachInterrupt(timerISR);
}

void loop() 
{
	/*

	if(progMode)
	{
		digitalWrite(13, HIGH);
	}
	//wait for long press
	//enter programming loop
	//read in which buttons are pressed
	//call setOrder based on pressed buttons

	digitalWrite(strobe, LOW);

	digitalWrite(ay0, HIGH);
	digitalWrite(ay1, LOW);
	digitalWrite(ay2, LOW);
	digitalWrite(cs1, HIGH);
	digitalWrite(cs2, HIGH);
	digitalWrite(data, HIGH);
	digitalWrite(ax2, HIGH);
	digitalWrite(ax0, HIGH);
	digitalWrite(ax1, LOW);
	digitalWrite(ax3, LOW);
	digitalWrite(strobe, HIGH);
	delay(1);
	digitalWrite(strobe, LOW);
	delay(10000);
	*/
	digitalWrite(RST, LOW);
	changeLoop(true, R2, A1);
	digitalWrite(13, HIGH);
	delay(3000);
	digitalWrite(RST, HIGH);
	changeLoop(true, R3, A1);
	digitalWrite(RST, LOW);
	
	digitalWrite(13, LOW);
	delay(3000);
	

}

//in order array, call changeloop with array and array - 1

void timerISR()
{
	if(loopCount > LOOPNUMBER /*|| longpress*/)
	{
		//setOrder(loopOrder[loopCount]); fix
		progMode = false;

		loopCount = 0;
		for(int i = 0; i <LOOPNUMBER; i ++)
		{
			loopOrder[i] = 0;
		}
	}
	//if button Zero
	{
		loopOrder[loopCount] = 0;
		loopCount ++;
	}

	//if button One
	{
		loopOrder[loopCount] = 1;
		loopCount ++;
	}

	//if button Two
	{
		loopOrder[loopCount] = 2;
		loopCount ++;
	}

	//if button Three
	{
		loopOrder[loopCount] = 3;
		loopCount ++;
	}

	//if button Four
	{
		loopOrder[loopCount] = 4;
		loopCount ++;
	}


}





void setOrder(int order[LOOPNUMBER])
{
	digitalWrite(RST, HIGH);
	digitalWrite(RST, LOW);

	for(int i = 0; i < LOOPNUMBER; i ++)
	{
		if(i == 0)
		{
			changeLoop(true, GTR_in, order[i]);
		}

		else while(order[i] != 0)
		{
			changeLoop(true, order[i-1], order [i]);
		}

		{
			i = LOOPNUMBER;
			changeLoop(true, order [i-1], A1);
		}
	}

}


void changeLoop(bool dataVal, int y, int x)
{
	int xValue;
	int yValue;
	int chipValue;

	switch(x)
	{
		case S1:
		{
			xValue = 14;
			break;
		}
		case S2:
		{
			xValue = 15;
			break;
		}
		case S3:
		{
			xValue = 6;
			break;
		}
		case S4:
		{
			xValue = 7;
			break;
		}
		case S5:
		{
			xValue = 2;
			break;
		}
		case S6L:
		{
			xValue = 8;
			break;
		}
		case S6R:
		{
			xValue = 9;
			break;
		}
		case S7L:
		{
			xValue = 10;
			break;
		}
		case S7R:
		{
			xValue = 11;
			break;
		}
		case S8L:
		{
			xValue = 13;
			break;
		}
		case S8R:
		{
			xValue = 12;
			break;
		}
		case S9L:
		{
			xValue = 1;
			break;
		}
		case S9R:
		{
			xValue = 0;
			break;
		}
		case A1:
		{
			xValue = 5;
			break;
		}
		case A2:
		{
			xValue = 4;
			break;
		}
		case A3:
		{
			xValue = 3;
			break;
		}
	}

	switch(y)
	{
		case GTR_in:
		{
			yValue = 1;
			chipValue = 2;
			break;
		}

		case R1:
		{
			yValue = 3;
			chipValue = 1;
			break;
		}

		case R2:
		{
			yValue = 3;
			chipValue = 2;
			break;
		}

		case R3:
		{
			yValue = 7;
			chipValue = 1;
			break;
		}

		case R4:
		{
			yValue = 7;
			chipValue = 2;
			break;
		}

		case R5:
		{
			yValue = 1;
			chipValue = 1;
			break;
		}

		case R6L:
		{
			yValue = 6;
			chipValue = 1;
			break;
		}

		case R6R:
		{
			yValue = 6;
			chipValue = 2;
			break;
		}
		case R7L:
		{
			yValue = 5;
			chipValue = 1;
			break;
		}
		case R7R:
		{
			yValue = 5;
			chipValue = 2;
			break;
		}
		case R8L:
		{
			yValue = 4;
			chipValue = 2;
			break;
		}
		case R8R:
		{
			yValue = 4;
			chipValue = 1;
			break;
		}
		case R9L:
		{
			yValue = 0;
			chipValue = 2;
			break;
		}
		case R9R:
		{
			yValue = 0;
			chipValue = 1;
			break;
		}
		case AUX1:
		{
			yValue = 2;
			chipValue = 2;
			break;
		}
		case AUX2:
		{
			yValue = 2;
			chipValue = 1;
			break;
		}
	}
	setSwitch(dataVal, xValue, yValue, chipValue);
}

void setSwitch(bool dataVal, int x, int y, int chip)
{
	digitalWrite(strobe, LOW);
	delay(1);
	
	if(dataVal)
		digitalWrite(data, HIGH);
	if(!dataVal)
		digitalWrite(data, LOW);

	if(chip == 1)
	{
		digitalWrite(cs1, HIGH);
		digitalWrite(cs2, LOW);
	}
	
	else if(chip == 2)
	{
		digitalWrite(cs1, LOW);
		digitalWrite(cs2, HIGH);
	}


	switch(x)
	{
		case 0:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, LOW);
			break;
		}
		case 1:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, LOW);
			break;
		}
		case 2:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, LOW);
			break;
		}
		case 3:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, LOW);
			break;
		}
		case 4:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, LOW);
			break;
		}
		case 5:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, LOW);
			break;
		}
		case 6:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 7:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 8:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 9:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, LOW);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 10:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 11:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, LOW);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 12:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, LOW);
			break;
		}
		case 13:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, LOW);
			break;
		}
		case 14:
		{
			digitalWrite(ax0, LOW);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, HIGH);
			break;
		}
		case 15:
		{
			digitalWrite(ax0, HIGH);
			digitalWrite(ax1, HIGH);
			digitalWrite(ax2, HIGH);
			digitalWrite(ax3, HIGH);
			break;
		}
	}

	switch(y)
	{
		case 0:
		{
			digitalWrite(ay0, LOW);
			digitalWrite(ay1, LOW);
			digitalWrite(ay2, LOW);
			break;
		}
		case 1:
		{
			digitalWrite(ay0, HIGH);
			digitalWrite(ay1, LOW);
			digitalWrite(ay2, LOW);
			break;
		}
		case 2:
		{
			digitalWrite(ay0, LOW);
			digitalWrite(ay1, HIGH);
			digitalWrite(ay2, LOW);
			break;
		}
		case 3:
		{
			digitalWrite(ay0, HIGH);
			digitalWrite(ay1, HIGH);
			digitalWrite(ay2, LOW);
			break;
		}
		case 4:
		{
			digitalWrite(ay0, LOW);
			digitalWrite(ay1, LOW);
			digitalWrite(ay2, HIGH);
			break;
		}
		case 5:
		{
			digitalWrite(ay0, HIGH);
			digitalWrite(ay1, LOW);
			digitalWrite(ay2, HIGH);
			break;
		}
		case 6:
		{
			digitalWrite(ay0, LOW);
			digitalWrite(ay1, HIGH);
			digitalWrite(ay2, HIGH);
			break;
		}
		case 7:
		{
			digitalWrite(ay0, HIGH);
			digitalWrite(ay1, HIGH);
			digitalWrite(ay2, HIGH);
			break;
		}
	}

	digitalWrite(strobe, HIGH);
}