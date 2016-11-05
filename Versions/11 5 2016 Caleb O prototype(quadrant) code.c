#pragma config(Motor, port2, driveL,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port3, driveR,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port4, arm,           tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port5, clawL,         tmotorServoStandard, openLoop)
#pragma config(Motor, port6, clawR,         tmotorServoStandard, openLoop)
#pragma config(Motor, port7, seedDispense,  tmotorServoStandard, openLoop)

int leftX = 0;
int leftY = 0;
int rightY = 0;
int rightX = 0;
int thresh = 8;
int slope = 1.35;
const bool on = true;

/*! L R drive*/
task drive()
{
	while(on)
	{
		motor[driveL] = ((-rightY - rightX)/slope)^2;
		motor[driveR] = ((+rightY - rightX)/slope)^2;
	}
	/*! end task drive*/
}

task manipulator()
{
	motor [clawL] = 80;
	motor [clawR] = -80;
	motor [seedDispense] = -127;

	while(on)
	{
		/*! arm motor*/
		motor[arm] = -leftY;

		if(vexRT[Btn7R])//close left claw
		{
			motor[clawL] = -45;
		}
		else if(vexRT[Btn7L])//open left claw
		{
			motor[clawL] = 5;
		}

		if(vexRT[Btn8D])// compliance code pos
		{
			motor[clawL] = 80;
			motor[clawR] = -80;
		}

		if(vexRT[Btn8L])//close right claw
		{
			motor[clawR] = 5;
	  }

	  if(vexRT[Btn8R])//open right claw
	  {
			motor[clawR] = -45;
	  }

		if(vexRT[Btn7U])
		{
			motor[seedDispense] = 127;
		}
		else if (vexRT[Btn7D])
		{
			motor[seedDispense] = -127;
		}
	}
}

/*!This holds the main tasks the robot initially starts with.*/
task main()
{
	/*! This starts the drive task */
	startTask(drive);
	/*! This starts the manipulator task */
	startTask(manipulator);
	/*! This loop continues until the robot is turned off*/
	while(on)
	{
		rightX = vexRT(Ch1);
		/*!This adds a deadzone in the controller's right X axis*/
		if(abs(rightX)<thresh)
		{
			rightX = 0;
		}
		rightY = vexRT(Ch2);
		/*!This adds a deadzone in the controller's right Y axis*/
		if(abs(rightY)<thresh)
		{
			rightY = 0;
		}
		leftY = vexRT(Ch3);
		/*!This adds a deadzone in the controller's left Y axis*/
		if(abs(leftY)<thresh)
		{
			leftY = 0;
		}
		leftX = vexRT(Ch4);
		/*!This adds a deadzone in the controller's left X axis*/
		if(abs(leftX)<thresh)
		{
			leftX = 0;
		}
	}
}
