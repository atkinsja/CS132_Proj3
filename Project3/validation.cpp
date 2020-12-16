/**************************************************************************************************
*
*   File name :			validation.cpp
*
*	Programmer:  		Jeremy Atkins
*
*   Implementation of the validation functions as defined in validation.h
*
*   Date Written:		in the past
*
*   Date Last Revised:	12/2/2018
****************************************************************************************************/
#include <iostream>
#include <string>

/*******************************************************************************************
*	Function Name:			validatedInput
*	Purpose:				Validates two inputs with an upper and a lower bound
*	Input Parameters:		input1, input2, lowerBound, upperBound
*	Output Parameters:		input1, input2
*	Return value:			none
********************************************************************************************/
void validatedInput(int& input1, int&input2, int lowerBound, int upperBound)
{
	std::cin >> input1;

	if (input1 == -1)
		return;

	std::cin >> input2;

	if (input2 == -1)
		return;

	//prompt the user while the input is not an integer or is not in between the lower and upper bounds
	while (std::cin.fail() || std::cin.peek() != '\n' || input1 < lowerBound || input1 > upperBound || input2 < lowerBound || input2 > upperBound)
	{
		std::cin.clear();
		std::cin.ignore(200, '\n');
		std::cout << "Incorrect input.\nPlease enter a valid integer " << lowerBound << " to " << upperBound << " or -1 to cancel" << std::endl;

		std::cin >> input1;
		if (input1 == -1)
			return;

		std::cin >> input2;

		if (input2 == -1)
			return;
	}
}

/*******************************************************************************************
*	Function Name:			validatedInput
*	Purpose:				Validates a single input
*	Input Parameters:		input
*	Output Parameters:		input
*	Return value:			none
********************************************************************************************/
void validatedInput(int& input)
{
	
	std::cin >> input;

	//prompt the user while the input is not an integer or is not in between the lower and upper bounds
	while (std::cin.fail() || std::cin.peek() != '\n')
	{
		std::cin.clear();
		std::cin.ignore(200, '\n');
		std::cout << "Incorrect input.\nPlease enter an valid integer: " << std::endl;

		std::cin >> input;
	}
}