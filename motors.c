/*
 * motors.c
 *
 *  Created on: Nov 18, 2016
 *      Author: Morty
 */

#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
#include "Board.h"
#include "buttons.h"
#include <stdio.h>

#include "Robot.h"
#include "motors.h"
#include <motors.h>


double dutyR1;
double dutyR2;
double dutyL1;
double dutyL2;

PWM_Handle pwm0;
PWM_Handle pwm1;
PWM_Handle pwm2;
PWM_Handle pwm3;

int indexL;
int indexR;

double infoR;
double infoL;

double MdistL;
double MdistR;

double last_distL;
double last_distR;

double pi=3.1415926535897932384626433832795;

double speedL;
double speedR;

//GPIO_setCallback(MSP_EXP432P401R_P6_1);//(MSP_EXP432P401R_P6_1, RHMotorChannelAFallingFxn)
	//   GPIO_enableInt(MSP_EXP432P401R_P6_1);
	//  GPIO_setCallback(MSP_EXP432P401R_P4_0, RHMotorChannelARisingFxn);
	//   GPIO_enableInt(MSP_EXP432P401R_P4_0);

void RotationFxn(UArg Arg0)
{

	infoR=infoR+indexR;
	infoL=infoL+indexL;
	last_distR=(6*pi*indexR)/1500;
	last_distL=(6*pi*indexL)/1500;

	MdistL=MdistL+last_distL;
	MdistR=MdistR+last_distR;

	speedR=last_distR*100;
	speedL=last_distL*100;

	indexL=0;
	indexR=0;
	last_distR=0;
	last_distL=0;
}

void motorsFxn()
{
	GPIO_write(MSP_EXP432P401R_P3_0,1);//set pin such that motors work
	PWM_Params params;
	uint16_t   pwmPeriod = 3000;      // Period and duty in microseconds
	//uint16_t   dutyInc = 100;		// sort of a fade out function (speed of fade out)


	PWM_Params_init(&params);//initializez the PWM module with the given parameters
	    params.dutyUnits = PWM_DUTY_US;
	    params.dutyValue = 0;
	    params.periodUnits = PWM_PERIOD_US;
	    params.periodValue = pwmPeriod;

	    //initialize g PWM instances for the 4 motor commands(2 inputs per motor)
	 pwm0 = PWM_open(Board_PWM0, &params);
	 pwm1 = PWM_open(Board_PWM1, &params);
	 pwm2 = PWM_open(Board_PWM2, &params);
	 pwm3 = PWM_open(Board_PWM3, &params);

	 	 // start the specified PWM handles with the (newly) given parameters
	   PWM_start(pwm0);
	   PWM_start(pwm1);
	   PWM_start(pwm2);
	   PWM_start(pwm3);


while(1)
{

	   PWM_setDuty(pwm0, dutyR2);
	   PWM_setDuty(pwm1, dutyR1);
	   PWM_setDuty(pwm2, dutyL2);
	   PWM_setDuty(pwm3, dutyL1);
	   //System_printf("%d   %d   \n",speedR , speedL);
	  	 //  System_flush();

	   Task_sleep(10);
}


	    /*


while(1)//start command for motor
{
	         //PWM_setDuty(pwm0, duty);
	         //PWM_setDuty(pwm1, 0);
	         PWM_setDuty(pwm2, duty);
	         PWM_setDuty(pwm3, 0);

	         if (GPIO_read(MSP_EXP432P401R_P4_2))
	         		        	 index1++;
	         System_printf("%d \n",index1);
	         System_flush();
	         //Task_sleep(10);
}
*/
	     }


void RHMotorChannelAFallingFxn(unsigned int index)
{

	if (GPIO_read(Robot_MotorRIN1f))
		        	 indexR++;
	else
		indexR++;//--

}

void RHMotorChannelARisingFxn(unsigned int index)
{
if (GPIO_read(Robot_MotorRIN1r))
		        	 indexR++;
	else
		indexR++;
}

void LHMotorChannelARisingFxn(unsigned int index)
{
	if (GPIO_read(Robot_MotorLIN1f))
			        	 indexL++;
		else
			indexL++;
}


void LHMotorChannelAFallingFxn(unsigned int index)
{
if (GPIO_read(Robot_MotorLIN1r))
		        	 indexL++;
	else
		indexL++;

}




