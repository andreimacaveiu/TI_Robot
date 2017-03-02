/*
 * distanceSensor.c
 *
 *  Created on: Nov 18, 2016
 *      Author: Morty
 */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>//from pwm_function

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>

/* Board Header files */
#include "Board.h"
#include "buttons.h"
#include <stdio.h>

#include <ti/drivers/I2C.h>
#include "Robot.h"


int distR[4];
int distL[4];


void distanceSensorFxn()//changed UArg arg0, UArg arg1
{
	Board_initGeneral();
	    Board_initGPIO();
	    Board_initPWM();
	    Board_initI2C();
	/* Switch the distance sensors on */
	    GPIO_write(MSP_EXP432P401R_P5_2, 1);
	    GPIO_write(MSP_EXP432P401R_P4_6, 1);

	//System_printf("I2C task Called.\n");

	uint8_t         writeBufferPCA9545A[2], writeBufferSensor[3];
	uint8_t         readBufferPCA9545A[1], readBufferSensor[1];
    I2C_Handle      i2cRight, i2cLeft;
    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction_PCA9545A, i2cTransactionSensor;

    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
	i2cParams.bitRate = I2C_400kHz;

    i2cRight = I2C_open(Board_I2C1, &i2cParams); //i2c2 changes the side
    if (i2cRight == NULL)
    {
        System_abort("Error Initialising I2CRight\n");
    }
    else
    {
        System_printf("I2CRight Initialised!\n");
    }

    i2cLeft = I2C_open(Board_I2C2, &i2cParams);
	if (i2cLeft == NULL)
	{
		System_abort("Error Initialising I2CLeft\n");
	}
	else
	{
		System_printf("I2CLeft Initialised!\n");
	}


	// get model id right
	writeBufferPCA9545A[0] = 0x01;
	i2cTransaction_PCA9545A.slaveAddress = PCA9545A_ADDR; //adress of IC
	i2cTransaction_PCA9545A.writeBuf = writeBufferPCA9545A;
	i2cTransaction_PCA9545A.writeCount = 1;
	i2cTransaction_PCA9545A.readBuf = readBufferPCA9545A;
	i2cTransaction_PCA9545A.readCount = 0;

	I2C_transfer(i2cRight, &i2cTransaction_PCA9545A);
	/*

	writeBufferSensor[0] = 0x00;
	writeBufferSensor[1] = 0x18;
	writeBufferSensor[2] = 0x01;
	i2cTransactionSensor.slaveAddress = 0x29;
	i2cTransactionSensor.writeBuf = writeBufferSensor;
	i2cTransactionSensor.writeCount = 2; //bits to be sent
	i2cTransactionSensor.readBuf = readBufferSensor;
	i2cTransactionSensor.readCount = 1;//bites to be received
	I2C_transfer(i2cRight, &i2cTransactionSensor);
	System_printf("ID_RIGHT: %d\n", readBufferSensor[0]);
	*/
while(1)
{
	writeBufferPCA9545A[0] = 0x01;
	int j;
	for (j = 0; j < 4; j++)
	{

	i2cTransaction_PCA9545A.slaveAddress = PCA9545A_ADDR; //adress of IC
	i2cTransaction_PCA9545A.writeBuf = writeBufferPCA9545A;
	i2cTransaction_PCA9545A.writeCount = 1;
	i2cTransaction_PCA9545A.readBuf = readBufferPCA9545A;
	i2cTransaction_PCA9545A.readCount = 0;

	I2C_transfer(i2cRight, &i2cTransaction_PCA9545A);

	I2C_transfer(i2cLeft, &i2cTransaction_PCA9545A);

		writeBufferSensor[0] = 0x00;
		writeBufferSensor[1] = 0x18;
		writeBufferSensor[2] = 0x01;
		i2cTransactionSensor.slaveAddress = 0x29;
		i2cTransactionSensor.writeBuf = writeBufferSensor;
		i2cTransactionSensor.writeCount = 3;
		i2cTransactionSensor.readBuf = readBufferSensor;
		i2cTransactionSensor.readCount = 0;
		I2C_transfer(i2cRight, &i2cTransactionSensor);

		writeBufferSensor[0] = 0x00;
		writeBufferSensor[1] = 0x62;
		i2cTransactionSensor.slaveAddress = 0x29;
		i2cTransactionSensor.writeBuf = writeBufferSensor;
		i2cTransactionSensor.writeCount = 2;
		i2cTransactionSensor.readBuf = readBufferSensor;
		i2cTransactionSensor.readCount = 1;
		I2C_transfer(i2cRight, &i2cTransactionSensor);
		distR[j]=readBufferSensor[0];

		writeBufferSensor[0] = 0x00;
		writeBufferSensor[1] = 0x18;
		writeBufferSensor[2] = 0x01;
		i2cTransactionSensor.slaveAddress = 0x29;
		i2cTransactionSensor.writeBuf = writeBufferSensor;
		i2cTransactionSensor.writeCount = 3;
		i2cTransactionSensor.readBuf = readBufferSensor;
		i2cTransactionSensor.readCount = 0;
		I2C_transfer(i2cLeft, &i2cTransactionSensor);

		writeBufferSensor[0] = 0x00;
		writeBufferSensor[1] = 0x62;
		i2cTransactionSensor.slaveAddress = 0x29;
		i2cTransactionSensor.writeBuf = writeBufferSensor;
		i2cTransactionSensor.writeCount = 2;
		i2cTransactionSensor.readBuf = readBufferSensor;
		i2cTransactionSensor.readCount = 1;
		I2C_transfer(i2cLeft, &i2cTransactionSensor);
		distL[j]=readBufferSensor[0];
		writeBufferPCA9545A[0] = writeBufferPCA9545A[0]<<1;
	}

	/*
		int k;
		System_printf("L: ");
		for(k=0;k<4;k++)
		{
		System_printf(" %d ",  distL[k]);
		}
		System_printf("\n");
		System_printf("R: ");
		for(k=0;k<4;k++)
			{
			System_printf(" %d ",  distR[k]);
			}
		System_printf("\n");
			System_flush();
*/

	Task_sleep(10);
}

	 /* Closing I2C */
/*
	    I2C_close(i2cRight);
	    System_printf("I2CRight closed.\n");
	    I2C_close(i2cLeft);
		System_printf("I2CLeft closed.\n");
*/

}


