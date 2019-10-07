//task 1
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

//Global Variables for duty cycle 
uint32_t ui32PeriodHigh;
uint32_t ui32PeriodLow;

int main(void)
{
    //clock initialization
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	//GPIO settings
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		//Timer 0 initialization 
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
        TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

        ui32PeriodHigh = (SysCtlClockGet() / 10) / 2.3;  //43% duty cycle
        ui32PeriodLow = (SysCtlClockGet() /10) / 1.75;   
        TimerLoadSet(TIMER0_BASE, TIMER_A, ui32PeriodHigh -1);
        TimerLoadSet(TIMER0_BASE, TIMER_A, ui32PeriodLow -1);

        IntEnable(INT_TIMER0A);
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        IntMasterEnable();

        TimerEnable(TIMER0_BASE, TIMER_A);

        while(1)
        {
        }
}

void Timer0IntHandler(void)
{
        // Clear the timer interrupt
        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

        // Read the current state of the GPIO pin and
        // write back the opposite state
        if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
        {
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32PeriodLow); //57 duty cycle off
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        }
        else
        {
            TimerLoadSet(TIMER0_BASE, TIMER_A, ui32PeriodHigh);  //43 duty cycle on 
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
        }
}


