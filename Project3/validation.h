/******************************************************************************************************************************
*
*   File name :			validation.h
*
*	Programmer:  		Jeremy Atkins
*
*   Header file for functions used in user input validation
*
*   Date Written:		in the past
*
*   Date Last Revised:	12/2/2018
*
*	Member functions:
*		validatedInput(int& input1, int& input2, int lowerBound, int upperBound)	-	validation for two inputs with an 
*																						upper and a lower bound for valid input
*		validatedInput(int&)														-	validation for a single input
********************************************************************************************************************************/

#ifndef VALIDATION_H_
#define VALIDATION_H_

void validatedInput(int&, int&, int, int);
void validatedInput(int&);
#endif // !VALIDATION_H_
