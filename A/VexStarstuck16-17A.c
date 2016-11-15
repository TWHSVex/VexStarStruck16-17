#pragma config(Sensor, dgtl1,  frontRight,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  frontLeft,      sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  backRight,      sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  backLeft,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  fLimit,         sensorTouch)
#pragma config(Sensor, dgtl10, aLimit,         sensorTouch)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port6,           cTopRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           cTopLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           cMiddle,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           cBottom,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#define C1LX vexRT[Ch4]
#define C1LY vexRT[Ch3]
#define C1RX vexRT[Ch1]
float diameter = 4;
float circum= PI*diameter;


//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void resetSensors(){
	SensorValue(frontLeft) = 0;
	SensorValue(frontRight) = 0;
	SensorValue(backLeft) = 0;
	SensorValue(backRight) = 0;
}
void setSpeed(float speed){
	motor[frontLeft] = speed;
	motor[frontRight] = speed;
	motor[backLeft] = speed;
	motor[backRight] = speed;
}
bool turn(int ticks){
	resetSensors();
	setSpeed(127);
	waitUntil((SensorValue(frontLeft) >= ticks) && (SensorValue(frontRight) >= ticks) && (SensorValue(backRight) >= ticks) && (SensorValue(backLeft) >= ticks));
	return true;
}
/*
void catapult()
{

setSpeed(127);
waitUntil(SensorValue(aLimit)==1);
while(vexRT[Btn5U] == 0){
while(SensorValue(aLimit) == 0){
setSpeed(30);
}
}
//waitUntil(vexRT[Btn5U]==1);

setSpeed(-128);
waitUntil(SensorValue(aLimit)==0);

setSpeed(0);



}*/
//void turnAndFire(int ticks){
//	setSpeed(127);
//	while(turn(ticks)){
//		while(SensorValue(aLimit) == 0){
//			setSpeed(30);
//		}
//	}
//	waitUntil(SensorValue(aLimit)==1);
//}
void fire()
{
	setMultipleMotors(cTopLeft,cTopRight,cMiddle,127);
	waitUntil(SensorValue(aLimit)==1);
	setMultipleMotors(cTopLeft,cTopRight,cMiddle,-127);
	waitUntil(SensorValue(aLimit)==0);
	setMultipleMotors(cTopLeft,cTopRight,cMiddle,0);
}

void turnAndFire(int ticks){
	resetSensor();
	while (SensorValue(frontLeft) < ticks)
	{
		setSpeed(127);
	}
	setSpeed(0);
	fire();
}



void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All acti vities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

void equilizeMotors(){
	resetSensors();
	clearTimer(T1);
	wait1Msec(50);
	float speedfl = SensorValue(frontLeft)/time10[T1];  //Rotational Speed of each motor
	float speedfr = SensorValue(frontRight)/time10[T1];
	float speedbl = SensorValue(backLeft)/time10[T1];
	float speedbr = SensorValue(backRight)/time10[T1];

	float smallest = speedfl;

	float shaftSpeeds[4] = {speedfl, speedfr, speedbl, speedbr};
	for(int i = 1; i < 4; i++){ //Compare each motors Speed and set smallest equal to float smallest
		if(smallest > shaftSpeeds[i]){
			smallest = shaftSpeeds[i];
		}
	}
	if(speedfl>smallest)
	{
		motor[frontLeft]= motor[frontLeft]-1;
	}
	if(speedfr>smallest)
	{
		motor[frontRight]= motor[frontRight]-1;
	}
	if(speedbl>smallest)
	{
		motor[backLeft]= motor[backLeft]-1;
	}
	if(speedbr>smallest)
	{
		motor[backRight]= motor[backRight]-1;
	}
}

task autonomous()
{
	setSpeed(127);

	while(SensorValue(fLimit)==0)
	{
		equilizeMotors();
	}
	setSpeed(0);
	turnAndFire(135); //fix this number to be 135 degrees

}

void moveInch(float distance){

resetSensors();
float targetticks = distance / circum * 360 / sqrt(2);
while(abs(SensorValue(frontLeft)) < targetticks)
{
motor[frontLeft]=127;
motor[frontRight]=127;
motor[backLeft]=127;
motor[backRight]=127;

}
motor[frontLeft]=0;
motor[frontRight]=0;
motor[backLeft]=0;
motor[backRight]=0;
}

//task autonomous()
//{
//	moveInch(12);

//}



task usercontrol()
{



	while (true)
	{
		//Forwards and Backwards
		motor[frontRight]=-vexRT[Ch4]+vexRT[Ch1]+vexRT[Ch3];
		motor[frontLeft]=vexRT[Ch4]+vexRT[Ch1]+vexRT[Ch3];
		motor[backLeft]=-vexRT[Ch4]-vexRT[Ch1]+vexRT[Ch3];
		motor[backRight]=vexRT[Ch4]+vexRT[Ch1]+vexRT[Ch3];

		if(vexRT[Btn5D]==1)
		{
			motor[cTopRight]=127;
			motor[cTopLeft]=127;
			motor[cMiddle]=127;
			motor[cBottom]=127;
		}
		else if(vexRT[Btn5U]==1)
		{
			motor[cTopRight]=-127;
			motor[cTopLeft]=-127;
			motor[cMiddle]=-127;
			motor[cBottom]=-127;
		}
		else
		{
			motor[cTopRight]=0;
			motor[cTopLeft]=0;
			motor[cMiddle]=0;
			motor[cBottom]=0;
		}

	}
}
