
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPE.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/Keypad/KEY_Interface.h"
#include"CALCULATION_PROJECT/Calculation_Interface.h"
#include <util/delay.h>
int main(void) {
LcdInit();
KeypadInit();

	while(1)
			{

	KeyPad_Calculator();

			}
		}






















