/*
 *  ======== main.c ========
 */
/* XDCtools Header files */
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
#include "motors.h"


extern double dutyR1;
extern double dutyR2;
extern double dutyL1;
extern double dutyL2;

extern int indexL;
extern int indexR;

extern double infoR;
extern double infoL;

extern double MdistL;
extern double MdistR;

extern double speedL;
extern double speedR;


//int distR[4];
//int distL[4];



/*
 *  ======== global system state variables ========
 */
uint8_t	state = 1;

//#define TASKSTACKSIZE 640//500 for motor task?

/*
Task_Struct taskI2CStruct;
Task_Struct motortskStruct;
UInt8 motortskStack[TASKSTACKSIZE];
Char taskI2CStack[TASKSTACKSIZE];

Task_Handle task;
*/

int index1;
int index2;

/*
 *  ======== taskFxn ========
 *  Task for this function is created statically. See the project's .cfg file.
 */


/*
 *  ======== main ========
 */

/*
void pwm_reset()//resets PWM handles such that the motor parameters (mainly direction) can be changed
{
	PWM_close(pwm0);
	PWM_close(pwm1);
	PWM_close(pwm2);
	PWM_close(pwm3);
}
*/

int main(void)
{   /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initPWM();
    Board_initI2C();

    GPIO_setCallback(Board_BUTTON0, gpioButtonFxn0);
    GPIO_enableInt(Board_BUTTON0);
    GPIO_setCallback(Board_BUTTON1, gpioButtonFxn1);
    GPIO_enableInt(Board_BUTTON1);

    // Switch on the LEDs
    GPIO_write(Board_LED0, Board_LED_ON);	// LH LED
    GPIO_write(Board_LED1, Board_LED_ON);	// RH LED, Red
    GPIO_write(Board_LED2, Board_LED_ON);	// RH LED, Green
    GPIO_write(Board_LED3, Board_LED_ON);	// RH LED, Blue



    GPIO_write(MSP_EXP432P401R_P3_0,1); //set pin such that motors work

	/* Switch the distance sensors on */
	    GPIO_write(MSP_EXP432P401R_P5_2, 1);
	    GPIO_write(MSP_EXP432P401R_P4_6, 1);

	    indexL=0;
	    indexR=0;

	    infoR=0;
	    infoL=0;

	    MdistL=0;
	    MdistR=0;



   //GPIO_write(MSP_EXP432P401R_PWM_TA1_1,1);
    //GPIO_write(MSP_EXP432P401R_PWM_TA1_2,0);

    //motorcontrol(1,0,0,0,500);//recommended minimum speed

    //delay_s(2);//delay by 2 seconds
    //pwm_reset();//reset pwm initiation , necesary for changing motor parameters




    /*Task_Params tskParams;

    Task_Params_init(&tskParams);
    tskParams.stackSize = TASKSTACKSIZE;
    tskParams.stack = &motortskStack;
    tskParams.RF = 1;
    Task_construct(&motortskStruct, (Task_FuncPtr)motorcontrol, &tskParams, NULL);
        //obtain instance handle

    task = Task_handle(&motortskStruct);
    */

     GPIO_setCallback(MSP_EXP432P401R_P6_1, RHMotorChannelAFallingFxn);
     GPIO_enableInt(MSP_EXP432P401R_P6_1);
     GPIO_setCallback(MSP_EXP432P401R_P4_0, RHMotorChannelARisingFxn);
     GPIO_enableInt(MSP_EXP432P401R_P4_0);

     GPIO_setCallback(MSP_EXP432P401R_P4_5, LHMotorChannelAFallingFxn);
     GPIO_enableInt(MSP_EXP432P401R_P4_5);
     GPIO_setCallback(MSP_EXP432P401R_P4_7, LHMotorChannelARisingFxn);
     GPIO_enableInt(MSP_EXP432P401R_P4_7);

    /*// Construct i2c task thread
    Task_Params i2cTaskParams;
    Task_Params_init(&i2cTaskParams);
    i2cTaskParams.stackSize = TASKSTACKSIZE;
    i2cTaskParams.stack = &taskI2CStack;
	Task_construct(&taskI2CStruct, (Task_FuncPtr)I2CtaskFxn, &i2cTaskParams, NULL);
	*/
	    //dutyR1=1000;
	    //dutyR2=0;
	    //dutyL1=1000;
	    //dutyL2=0;

/*
    dutyR1=1000;
    dutyR2=0;

    delay_s(3);

    dutyL1=0;
    dutyL2=1000;
    */
    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();


    return (0);

}

// GPIO_write(MSP_EXP432P401R_P3_0,1); //set pin s.t motors work
