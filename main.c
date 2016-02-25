#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  FlywheelSensor, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           FlywheelLeft,  tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           FlywheelRight, tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port4,           DriveFrontRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           DriveFrontLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           DriveBackLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           DriveBackRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           ElevatorRight, tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           ElevatorLeft,  tmotorVex393TurboSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "pid.c"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

static PIDControlled flywheel;



void pre_auton() {
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

task autonomous() {
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol() {
	PIDInit(flywheel,
		// PID variables (Kp, Ki, Kd)
		0, 0, 0,
		// IMEMotor
		FlywheelLeft,
		// Motor Gearings
		VEX393Turbo
	);


	while (true) {
		PIDUpdate(&flywheel);

		flywheel.target = motorPowerToRPM(80);
	  	writeDebugStreamLine("flywheel.drive: %d", flywheel.drive);

	  	// We use deltaTime so this doesn't matter, but it will ease calculations
	  	wait1Msec(20);
	}
}
