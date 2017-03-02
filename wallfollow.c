/*
 * wallfollow.c
 *
 *  Created on: Nov 19, 2016
 *      Author: Morty
 */


#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

#include <stdio.h>

#include "Robot.h"

double dutyR1;
double dutyR2;
double dutyL1;
double dutyL2;

int distR[4];
int distL[4];

double speedL;
double speedR;

double MdistL;
double MdistR;

void delay_s(int n)
{
	 int j;
	 for(j=0;j<=4000000*n;j++)//equivalent to a delay of n seconds
	 {
		  j++;
	 }
}
void wallfollowFxn()
{
	double speed=15;
	dutyL1=700;
	dutyL2=0;
	dutyR1=700*0.8;
	dutyR2=0;
	double errR;
	double errL;
	double err;
	int dist=100;
	while(1)
	{
		if((MdistL+MdistR)/2<dist)
		{
	errR=(speed-speedR)*10;
	errL=(speed-speedL)*10;
	err=(speedL-speedR);
	dutyR1=dutyR1+(errR-err);
	dutyR2=0;
	dutyL1=dutyL1+(errL+err);
	dutyL2=0;
		}
		else
		{
			dutyR1=0;
			dutyL1=0;
		}
	//x=x+200;

	/*while(1)
	{
		//if(distR[0]<=27 || distR[1]<=1 || distR[2]<=22 || distR[3]<=24 || distL[0]<=11 || distL[1]<=43 || distL[2]<=1 || distL[3]<=5)
		if(x==2)
		{
			dutyR1=0;
			dutyR2=0;
			dutyL1=0;
			dutyL2=0;
		}
		else
		{
			dutyR1=800;
			dutyR2=0;
			dutyL1=800;
			dutyL2=0;
		}
		*/
	Task_sleep(1000);
	}
}
