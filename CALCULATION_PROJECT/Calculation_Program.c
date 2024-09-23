/*
 * Calculation_Program.c
 *
 *  Created on: Sep 22, 2024
 *      Author:Butcher
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include "../../HAL/Keypad/KEY_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include <util/delay.h>
#include "Calculation_Interface.h"
 // if you use this code read comments delete the lines that has number 1  to 9 comments
void initStack(Stack *s) {
	s->top = -1;
}

u8 isFull(Stack *s) {
	return s->top == MAX - 1;
}

u8 isEmpty(Stack *s) {
	return s->top == -1;
}

void push(Stack *s, u32 value) {
	if (!isFull(s)) {
		s->items[++s->top] = value;
	}


}

u32 pop(Stack *s) {
	if (!isEmpty(s)) {
		return s->items[s->top--];
	} else {return 0;}
}

u32 LAST_DIGIT_ENTERED(Stack *s) {
	if (!isEmpty(s)) {
		return s->items[s->top];
	} else{return 0;}
}


// Function to evaluate the top operation in the stack
void evaluateTopOperation(Stack *values, Stack *operators) {
	u32 val2 = pop(values);
	u32 val1 = pop(values);
	u8 op = pop(operators);
	u32 result = 0;

	switch (op) {
	case '+': result = val1 + val2; break;
	case '-': result = val1 - val2; break;
	case '*': result = val1 * val2; break;
	case '/':
		if (val2 != 0) {
			result = val1 / val2;
		} else {
			// Handle division by zero
			vSetposstion(2, 1);
			vConvertNumbersToString(0);
			return;
		}
		break;
	default:

		vSetposstion(2, 1);
		vConvertNumbersToString(0);
		return;
	}

	push(values, result);
}

// Function to handle operator
void PeriortyOfOperator(Stack *values, Stack *operators, u8 op) {
	while (!isEmpty(operators) && ((LAST_DIGIT_ENTERED(operators) == '*' || LAST_DIGIT_ENTERED(operators) == '/') || (op == '+' || op == '-'))) {
		evaluateTopOperation(values, operators);
	}
	push(operators, op);
}

// Main calculator function using stack
void KeyPad_Calculator() {
	// delete the lines related to DIO  1 to 9
	vSetPinDirection(PORT_D, PIN_3, output); //1
	vSetPinDirection(PORT_C, PIN_7, output); //2
	vSetPinDirection(PORT_C, PIN_2, output); //3

	Stack numberStack;
	Stack operatorStack;
	initStack(&numberStack);
	initStack(&operatorStack);

	u32 num = 0;
	u8 Key = NO_KEY;
	u8 lastDigit = 0;

	while (1) {
		Key = KeypadPressed();

		if (Key != NO_KEY) {
			LcdWriteData(Key);

			if (Key >= '0' && Key <= '9') {
				num = (num * 10) + (Key - '0');
				lastDigit = 1;
			} else {
				if (lastDigit) {
					push(&numberStack, num);
					num = 0;
					lastDigit = 0;
				}

				if (Key == '+' || Key == '-' || Key == '*' || Key == '/') {
					PeriortyOfOperator(&numberStack, &operatorStack, Key);
				} else if (Key == '=') {
					if (lastDigit) {
						push(&numberStack, num);
						num = 0;
					}

					while (!isEmpty(&operatorStack)) {
						evaluateTopOperation(&numberStack, &operatorStack);
					}

					// Display result
					vSetposstion(2, 1);
					vConvertNumbersToString(LAST_DIGIT_ENTERED(&numberStack));

					// Reset hardware pins and variables
					vPinValue(PORT_C, PIN_2, HIGH); _delay_ms(500); //4
					vPinValue(PORT_C, PIN_7, HIGH); _delay_ms(500); //5
					vPinValue(PORT_D, PIN_3, HIGH); //6
					num = 0;
					lastDigit = 0;
					initStack(&numberStack); // Reset stack
					initStack(&operatorStack); // Reset stack
				} else if (Key == 'C') {
					ClearDisplay();
					vPinValue(PORT_C, PIN_2, LOW); _delay_ms(500);//7
					vPinValue(PORT_C, PIN_7, LOW); _delay_ms(500);//8
					vPinValue(PORT_D, PIN_3, LOW);//9
					num = 0;
					lastDigit = 0;
					initStack(&numberStack); // Reset stack
					initStack(&operatorStack); // Reset stack
				}
			}

			_delay_ms(100);
		}
	}
}


