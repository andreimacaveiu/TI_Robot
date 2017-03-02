/*
 * screenTask.c
 *
 *  Created on: Nov 18, 2016
 *      Author: Morty
 */

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>

/* Board Header files */
#include "Sharp96x96.h"
#include <stdio.h>

/*
 *  screenTaskFxn
 */
double MdistL;
double MdistR;

double speedL;
double speedR;

double infoR;
double infoL;

void screenTaskFxn (UArg arg0, UArg arg1)
{
	Graphics_Context g_sContext;

	char test1_string[20];
    char test2_string[20];

    const uint8_t LHS =  10;
    const uint8_t RHS = 210;
    uint8_t y;

    Sharp96x96_LCDInit();

    Graphics_initContext(&g_sContext, &g_sharp96x96LCD);
    Graphics_setForegroundColor(&g_sContext, ClrBlack);
    Graphics_setBackgroundColor(&g_sContext, ClrWhite);
    Graphics_setFont(&g_sContext, &g_sFontCm20b);
    Graphics_clearDisplay(&g_sContext);
    Graphics_flushBuffer(&g_sContext);

    while (1) {
        Graphics_clearBuffer(&g_sContext);
    	y = 0;

    	sprintf(test1_string,"MotorR = %4.1f", speedR) ;//%4.1f
        Graphics_drawString(&g_sContext, test1_string, GRAPHICS_AUTO_STRING_LENGTH, LHS, y, GRAPHICS_TRANSPARENT_TEXT);
    	sprintf(test2_string,"MotorL = %4.1f", speedL) ;
		Graphics_drawString(&g_sContext, test2_string, GRAPHICS_AUTO_STRING_LENGTH, RHS, y, GRAPHICS_TRANSPARENT_TEXT);
    	y += 20;

    	sprintf(test1_string,"DistR = %6.1f",MdistR) ;
        Graphics_drawString(&g_sContext, test1_string, GRAPHICS_AUTO_STRING_LENGTH, LHS, y, GRAPHICS_TRANSPARENT_TEXT);
    	sprintf(test2_string,"DistL = %6.1f",MdistL) ;
		Graphics_drawString(&g_sContext, test2_string, GRAPHICS_AUTO_STRING_LENGTH, RHS, y, GRAPHICS_TRANSPARENT_TEXT);
    	y += 20;

		Graphics_flushBuffer(&g_sContext);
    	Task_sleep((UInt)arg0);
    }
}

