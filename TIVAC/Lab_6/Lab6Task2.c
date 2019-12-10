//Lab6 Task 2
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"

#define PWM_FREQUENCY 100

int main(void)
{
	volatile uint32_t ui32Load;
	volatile uint32_t ui32PWMClock;
	volatile uint8_t ui8Adjust;
	ui8Adjust = 1;

	//clock initialization
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

	//peripheral enable 
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	//GPIO config 
	ROM_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1);
	ROM_GPIOPinConfigure(GPIO_PF1_M1PWM5);

	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	ROM_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
	ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	//pwm config 
	ui32PWMClock = SysCtlClockGet() / 64;
	ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;
	ROM_PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);

	ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
	ROM_PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
	ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_2);

	while(1)
	{
	    //when pressing button
		//pwm 10%
		if(ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0x00)
		{
			if(ui8Adjust < 10)
			{
				ui8Adjust = 10;
			}
			ui8Adjust--;
			ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
		}

		//pwm 90% 
		if(ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0x00)
		{
			if(ui8Adjust > 90)
			{
				ui8Adjust = 90;
			}
			ui8Adjust++;
			ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust * ui32Load / 1000);
		}

		ROM_SysCtlDelay(100000);
	}
}
