/*
 * Calculation_Interface.h
 *
 *  Created on: Sep 22, 2024
 *      Author: Mahmoud
 */

#ifndef APP_CALCULATION_PROJECT_CALCULATION_INTERFACE_H_
#define APP_CALCULATION_PROJECT_CALCULATION_INTERFACE_H_

#define MAX 100
#define MAX_NUMBERS 10

// Stack structure
typedef struct {
    u32 items[MAX];
    u32 top;
} Stack;
void initStack(Stack *s);
u8 isFull(Stack *s);
u8 isEmpty(Stack *s);
void push(Stack *s, u32 value);
u32 pop(Stack *s);
u32 LAST_DIGIT_ENTERED(Stack *s);
void evaluateTopOperation(Stack *values, Stack *operators);
void PeriortyOfOperator(Stack *values, Stack *operators, u8 op);
void KeyPad_Calculator();


#endif /* APP_CALCULATION_PROJECT_CALCULATION_INTERFACE_H_ */
