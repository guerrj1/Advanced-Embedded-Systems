//Lab9 Task 1
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

#ifndef M_PI
#define M_PI  3.14159265358979323846 //pi equation 
#endif

#define SERIES_LENGTH 100 //array size 

float gSeriesData[SERIES_LENGTH]; //an array of floats SERIES_LENGTH long

int32_t i32DataCount = 0;  //a counter for our computation loop

int main(void)
{
    float fRadians; //float variable to store equation 

    ROM_FPULazyStackingEnable(); //enables the lazy stacking of floating point integers
    ROM_FPUEnable(); //enables floating point unit 

	//clock initialization 
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    fRadians = ((2 * M_PI) / SERIES_LENGTH); //setting equation to the variable 

	//while loop to loop while i32DataCount is less than SERIES_LENGTH
    while(i32DataCount < SERIES_LENGTH)
    {
        gSeriesData[i32DataCount] = sinf(fRadians * i32DataCount); //data array 

        i32DataCount++; //increment i32DataCount
    }

    while(1)
    {
    }
}
