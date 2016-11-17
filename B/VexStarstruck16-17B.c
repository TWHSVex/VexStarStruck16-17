#pragma config(Sensor, dgtl1,  dwnL,           sensorTouch)
#pragma config(Sensor, dgtl2,  dwnR,           sensorTouch)
#pragma config(Motor,  port1,           leftTop,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftMid,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftBot,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightTop,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightMid,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rightBot,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftDrive,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port8,           rightDrive,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port9,           leftClaw,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightClaw,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//Noah if strafing wheel is put in... click motor and sensor setup button
//then change name of port10 name to strafing *** finally uncomment out the code labeled new wheel code
//delete old right claw code
void off()
{
	motor[leftTop] = 0;
	motor[leftMid]= 0;
	motor[leftBot] = 0;
	motor[rightTop]= 0;
	motor[rightMid]= 0;
	motor[rightBot] = 0;
}

void driveDecimal(float times, float right, float left)
{
	motor[leftDrive]=left*127;
	motor[rightDrive]=right*127;
	wait1Msec (times);
	motor[leftDrive]=0;
	motor[rightDrive]=0;
}
void fireDec(float f)
{
	motor[leftTop] = 127*f;
	motor[leftMid]= 127*f;
	motor[leftBot] = 127*f;
	motor[rightTop]= -127*f;
	motor[rightMid]= -127*f;
	motor[rightBot] = -127*f;
	wait1Msec (1000);
	motor[leftTop] = -127;
	motor[leftMid]= -127;
	motor[leftBot] = -127;
	motor[rightTop]= 127;
	motor[rightMid]= 127;
	motor[rightBot] = 127;
	wait1Msec(1000);
	motor[leftTop] = 0;
	motor[leftMid]= 0;
	motor[leftBot] = 0;
	motor[rightTop]= 0;
	motor[rightMid]= 0;
	motor[rightBot] = 0;
}
void clawBoolean(float timeA, bool OoC)
{
	float np=1;
	if(OoC==false)
	{
		np=-1;
	}
	motor[leftClaw]=np*63;
	motor[rightClaw]=np*63;
	wait1Msec (timeA);
	motor[leftClaw]=0;
	motor[rightClaw]=0;
}
/*
Sam's Practice Code	*/
task autonomous()
{
//	driveDecimal(1000,1,-1);
	//time msec, right, left
//	clawBoolean(750,true);
	//time msec, open
	driveDecimal(15000,.3,.7);
	//time, right, left
//	clawBoolean(750,false);
	//time msec, close
//	fireDec(.75);
	//fire speed
}
/*task autonomous()
{
}*/
task main()
{
	//startTask(autonomous);

	while(true)
	{
	tankControl(Ch2, Ch3);

	/////////Speed Control///////
	int speed= 127;
	bool fast =true;
	if(vexRT(Btn8D)==1 && fast)
	{
		speed=75;
		fast=!fast;
	}
	if(vexRT(Btn8D)==1 && !fast)
	{
		speed=127;
		fast=!fast;
	}
		/////////Bar Lowering///////
	if(vexRT(Btn6D)==1)
	{
	motor[leftTop] = speed;
	motor[leftMid]= speed;
	motor[leftBot] = speed;
	motor[rightTop]= -speed +5;
	motor[rightMid]= -speed +5;
	motor[rightBot] = -speed +5;
  }
  	/////////Bar Lifting///////
	else if(vexRT(Btn6U)==1)
	{
	motor[leftTop] = -speed;
	motor[leftMid]= -speed;
	motor[leftBot] = -speed;
	motor[rightTop]= speed -5;
	motor[rightMid]= speed -5;
	motor[rightBot] = speed -5;
	}
	else
	{
	motor[leftTop] = 0;
	motor[leftMid]= 0;
	motor[leftBot] = 0;
	motor[rightTop]= 0;
	motor[rightMid]=0;
	motor[rightBot] = 0;
	}
	/////////Claw Code////////
	if(vexRT(Btn5D)==1)
	{
	motor[leftClaw]=63;
	motor[rightClaw]=63;
	}
	else if(vexRT(Btn5U)==1)
	{
	motor[leftClaw]=-63;
	motor[rightClaw]=-63;
	}
	else
	{
	motor[leftClaw]=0;
	motor[rightClaw]=0;
	}
	//////Seperate Lift Lower Buttons///////
	if(vexRT(Btn8L)==1)
	{
	while(vexRT(Btn8L)==1)
	{
	motor[leftTop]= 127;
	motor[leftMid]= 127;
	motor[leftBot] = 127;
	}
	off();
}
	if(vexRT(Btn8R)==1)
	{
	while(vexRT(Btn8R)==1)
	{
	motor[rightTop]= -127 +5;
	motor[rightMid]= -127 +5;
	motor[rightBot] = -127 +5;
	}
	off();
}

			/////New Wheel Code
/*
if(vexRT(Btn7L)==1)
{
	motor[strafing]=127;
}
off();
if(vexRT(Btn7R)==1)
{
	motor[strafing]=-127;
}
off();
*/



			///////Expiremental Code/////

		//////Automatic Lift Reset///////
	if(vexRT(Btn7D)==1)
	{
	while(SensorValue(dwnR)==0 && SensorValue(dwnL)==0)
	{
	motor[leftTop] = -127;
	motor[leftMid]= -127;
	motor[leftBot] = -127;
	motor[rightTop]= 127;
	motor[rightMid]= 127;
	motor[rightBot] = 127;
	}
	off();
	while(SensorValue(dwnL)==0)
	{
	motor[leftTop] = -127;
	motor[leftMid]= -127;
	motor[leftBot] = -127;
	}
	off();
	while(SensorValue(dwnR)==0)
	{
	motor[rightTop]= 127;
	motor[rightMid]= 127;
	motor[rightBot] = 127;
	}
	off();

		////Lift Reset Manuel Assist//////
	while(vexRT(Btn6D)==1 && SensorValue(dwnR)==0 && SensorValue(dwnL)==0)
	{
	motor[leftTop] = -127;
	motor[leftMid]= -127;
	motor[leftBot] = -127;
	motor[rightTop]= 127;
	motor[rightMid]= 127;
	motor[rightBot] = 127;
	}
	off();
	while(vexRT(Btn6D)==1 && SensorValue(dwnL)==0)
	{
	motor[leftTop] = -127;
	motor[leftMid]= -127;
	motor[leftBot] = -127;
	}
	off();
	while(vexRT(Btn6D)==1 && SensorValue(dwnR)==0)
	{
	motor[rightTop]= 127;
	motor[rightMid]= 127;
	motor[rightBot] = 127;
	}
	off();
	///////Ends//////

}
}
}
