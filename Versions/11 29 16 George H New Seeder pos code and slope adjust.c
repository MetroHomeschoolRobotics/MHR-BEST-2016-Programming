#pragma config(Motor,  port2,           driveL,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           driveR,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           arm,           tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawL,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           clawR,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           seedDispense,  tmotorServoStandard, openLoop)
#pragma config(Motor,  port8,           extender,      tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*! leftX stands for the X axis of the left joystick on the controller*/
int leftX = 0;

/*! leftY stands for the Y axis of the left joystick on the controller*/
int leftY = 0;

/*! rightX stands for the X axis of the right joystick on the controller*/
int rightX = 0;

/*! rightY stands for the Y axis of the right joystick on the controller*/
int rightY = 0;

/*! thresh stands for the variable that the joystick
has to be greater than in order to move a motor*/
int thresh = 6;

/*! slope is the is the variable that controlls the robot's
acceleration depending on how far the joystick is pushed
...basically it controlls the sensitivity of the joystick*/
int slope = 1;

/*! slope2  is annother variable that makes the robot
more controllable making the joystick way less sensative
...basically this too controlls the sensitivity of the robot*/
int slope2 = 2.5;

/*! on is a boolean value, which means that the variable is
either true of false, in this case we made one that is true*/
const bool on = true;

task drive()
/*! Port 2 is the port for the motor that controls the left wheel*/
/*! Port 3 is the port for the motor that controls the right wheel*/
{
	while(on)
	{
		if (vexRT[Btn6D])
		{
			motor[driveL] = ((-rightY - rightX)/slope2)^2;
			motor[driveR] = ((+rightY - rightX)/slope2)^2;
		}
		else
		{
			motor[driveL] = ((-rightY - rightX)/slope)^2;
			motor[driveR] = ((+rightY - rightX)/slope)^2;
		}
	}
}

task manipulator()
/*! Port 4 is the port for the motor that raises and lowers the arm*/
/*! Port 5 is the port for the servo that controls the left servo for the claw*/
/*! Port 6 is the port for the servo that controls the right servo for the claw*/
/*! Port 7 is the port for the servo that controls the servo for the despenser*/
{
	motor [clawL] = 127;
	motor [clawR] = -127;
	motor [seedDispense] = -90;

	while(on)
	{
		motor[arm] = -leftY;

		if(vexRT[Btn7R])//close left claw
		{
			motor[clawL] = -127;
		}
		else if(vexRT[Btn7L])//open left claw
		{
			motor[clawL] = 127;
		}

		if(vexRT[Btn5D])//extend the arm
		{
			motor[extender] = 127;
	  }
	  else if(vexRT[Btn5U])
	  {
	  	motor[extender] = -127;
	  }
	  else
	  {
	  	motor[extender] = 0;
	  }

	  if(vexRT[Btn6U])//close both claws
	  {
	  	motor[clawL] = -127;
	  	motor[clawR] = 127;
	  }

		if(vexRT[Btn8L])//close right claw
		{
			motor[clawR] = 127;
		}

		if(vexRT[Btn8R])//open right claw
		{
			motor[clawR] = -127;
		}

		if(vexRT[Btn7D])
		{
			motor[seedDispense] = -90;
		}
		else if (vexRT[Btn7U])
		{
			motor[seedDispense] = -28;
		}
	}
}

task main()
/*!This holds the main tasks the robot initially starts
with, such as the drive and the manipulator tasks.*/
{
	// This starts the drive task
	startTask(drive);
	// This starts the manipulator task
	startTask(manipulator);
	// This loop continues until the robot is turned off
	while(on)
	{
		rightX = vexRT(Ch1);
		//This adds a deadzone in the controller's right X axis
		if(abs(rightX)<thresh)
		{
			rightX = 0;
		}
		rightY = vexRT(Ch2);
		//This adds a deadzone in the controller's right Y axis
		if(abs(rightY)<thresh)
		{
			rightY = 0;
		}
		leftY = vexRT(Ch3);
		//This adds a deadzone in the controller's left Y axis
		if(abs(leftY)<thresh)
		{
			leftY = 0;
		}
		leftX = vexRT(Ch4);
		//This adds a deadzone in the controller's left X axis
		if(abs(leftX)<thresh)
		{
			leftX = 0;
		}
	}
}