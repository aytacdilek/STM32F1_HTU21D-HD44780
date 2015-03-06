/*********************************************************************************************************
*
* File                	: 	main.c
* Datum					: 	2015.03.06
* Version				: 	1.0
* Author				: 	Aytac Dilek
* e-mail				: 	aytacdilek@gmail.com
* Web					:
* Platform				: 	Open103Z-B
* CPU					: 	STM32F103ZET6
* IDE					: 	CooCox CoIDE 1.7.7
* Compiler				: 	GCC 4.8 2014q2
* Module				: 	HTU21D and 1602LCD with HD44780 controller
* Function				: 	Reads temperature and humidity information via HTU21 sensor
* 							and displays it on 1602 character LCD
* Copyright				:	GNU General Public License, version 3 (GPL-3.0)
*
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "stm32f10x_htu21.h"
#include "stm32f10x_hd44780.h"

float temp;


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
	SystemInit(); // Activate settings quartz

	LCD_Init();
	htu21_init();
	systick_init();

	/* Infinite loop */
	while (1)
	{
		LCD_Clear();
		htu21_softwareReset();
		temp = htu21_readTemperature();
		LCD_Goto(1,1);
		LCD_Puts("Temperature:");
		LCD_PutSignedInt((int) temp);
		temp = htu21_readCompensatedHumidity();
		LCD_Goto(1,2);
		LCD_Puts("Humidity:");
		LCD_PutSignedInt((int) temp);
		systick_delayS(2);
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
