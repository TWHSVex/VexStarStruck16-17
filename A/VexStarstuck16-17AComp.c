#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           g2,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           g3,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           g4,            tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#define C1LX vexRT[Ch4]
#define C1LY vexRT[Ch3]fv
#define C1RX vexRT[Ch1]
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

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
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

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}


void rotateR(){
	motor[frontRight]= 128;
	motor[frontLeft]=-128;
	motor[backRight]=128;
	motor[backLeft]=-128;
}

void rotateL(){
	motor[frontRight]= -128;
	motor[frontLeft]=128;
	motor[backRight]=-128;
	motor[backLeft]=128;
}

task usercontrol()
{

	while (true)
	{
		//Forwards and Backwords
				motor[frontRight]=-vexRT[Ch1]+vexRT[Ch4]+vexRT[Ch3];
				motor[frontLeft]=vexRT[Ch1]+vexRT[Ch4]+vexRT[Ch3];
				motor[backLeft]=-vexRT[Ch1]-vexRT[Ch4]+vexRT[Ch3];
				motor[backRight]=vexRT[Ch1]+vexRT[Ch4]+vexRT[Ch3];
				if(vexRT[Btn5D]==1){
					rotateR();
				}
				if(vexRT[Btn6D]==1){
					rotateL();
				}

 // Remove this function call once you have "real" code.
	}
}
