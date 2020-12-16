/**************************************************************************************************
*
*   File name :			driver.cpp
*
*	Programmer:  		Jeremy Atkins
*
*   Driver file initializing a Maze object and setting up a menu allowing the user to either
*	input a maze from a file or use a randomly generated maze
*
*   Date Written:		in the past
*
*   Date Last Revised:	12/02/2018
****************************************************************************************************/

#include <iostream>
#include <string>
#include "validation.h"
#include "maze.h"

using namespace std;

void printTitle();

//main function
int main()
{
	int input;		//menu input
	char resolve;	//new starting position
	Maze maze;		//maze object
	string inFileName;		//file name holding the maze data
	bool initialized = false;	//maze has data or not
	printTitle();
	
	//main menu loop
	do
	{
		cout << "1. Use maze from a file." << endl;
		cout << "2. Generate a maze." << endl;
		cout << "9. Quit." << endl;
		cout << "Enter your option: ";

		validatedInput(input);		//menu input validation

		//menu
		switch (input)
		{
		//maze from a file
		case 1:
			
			cout << "Enter the name of the file with the maze: " << endl;
			cin >> inFileName;
			
			do {
				initialized = maze.mazeFromFile(inFileName);
				if (!initialized)
					break;

				//solve the maze from the file
				maze.solveMaze();

				cout << "Would you like to try a different starting position? (y/n): ";
				cin >> resolve;
				while (resolve != 'y' && resolve != 'Y' && resolve != 'n' && resolve != 'N')
				{
					cout << "Invalid input. Please enter y for yes or n for no: ";
					cin.clear();
					cin.ignore(200, '\n');
					cin >> resolve;
				}
			} while (resolve == 'y' || resolve == 'Y');
			break;

		//maze from the maze generator
		case 2:
			maze.generateMaze();
			maze.solveMaze();
			break;

		//exit
		case 9:
			return 0;

		default:
			cout << "Incorrect input.\nPlease enter a valid menu option: " << endl;
			break;
		}

	} while (input != 9);

		
	return 0;

}

/*******************************************************************************************
*	Function Name:			printTitle
*	Purpose:				Prints out some ascii art for the title
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void printTitle()
{
	cout << "\t __    __   ______   ______   ______                      " << endl;
	cout << "\t/\\ \"-./  \\ /\\  __ \\ /\\___  \\ /\\  ___\\                     " << endl;
	cout << "\t\\ \\ \\-./\\ \\\\ \\  __ \\\\/_/  /__\\ \\  __\\                     " << endl;
	cout << "\t \\ \\_\\ \\ \\_\\\\ \\_\\ \\_\\ /\\_____\\\\ \\_____\\                   " << endl;
	cout << "\t  \\/_/  \\/_/ \\/_/\\/_/ \\/_____/ \\/_____/                   " << endl;

	cout << " ______   __  __   __   __   __   __   ______   ______    " << endl;
	cout << "/\\  == \\ /\\ \\/\\ \\ /\\ \"-.\\ \\ /\\ \"-.\\ \\ /\\  ___\\ /\\  == \\   " << endl;
	cout << "\\ \\  __< \\ \\ \\_\\ \\\\ \\ \\-.  \\\\ \\ \\-.  \\\\ \\  __\\ \\ \\  __<   " << endl;
	cout << " \\ \\_\\ \\_\\\\ \\_____\\\\ \\_\\\\\"\\_\\\\ \\_\\\\\"\\_\\\\ \\_____\\\\ \\_\\ \\_\\ " << endl;
	cout << "  \\/_/ /_/ \\/_____/ \\/_/ \\/_/ \\/_/ \\/_/ \\/_____/ \\/_/ /_/ " << endl << endl;

	cout << "\t\t\\                           /" << endl;
	cout << "\t\t \\                         /" << endl;
	cout << "\t\t  \\                       /" << endl;
	cout << "\t\t   ]                     [    ,'|" << endl;
	cout << "\t\t   ]                     [   /  |" << endl;
	cout << "\t\t   ]___               ___[ ,'   |" << endl;
	cout << "\t\t   ]  ]\\             /[  [ |:   |" << endl;
	cout << "\t\t   ]  ] \\           / [  [ |:   |" << endl;
	cout << "\t\t   ]  ]  ]         [  [  [ |:   |" << endl;
	cout << "\t\t   ]  ]  ]__     __[  [  [ |:   |" << endl;
	cout << "\t\t   ]  ]  ] ]\\ _ /[ [  [  [ |:   |" << endl;
	cout << "\t\t   ]  ]  ] ] (#) [ [  [  [ :===='" << endl;
	cout << "\t\t   ]  ]  ]_].nHn.[_[  [  [" << endl;
	cout << "\t\t   ]  ]  ]  HHHHH. [  [  [" << endl;
	cout << "\t\t   ]  ] /   `HH(\"N  \\ [  [" << endl;
	cout << "\t\t   ]__]/     HHH  \"  \\[__[" << endl;
	cout << "\t\t   ]         NNN         [" << endl;
	cout << "\t\t   ]         N/\"         [" << endl;
	cout << "\t\t   ]         N H         [" << endl;
	cout << "\t\t  /          N            \\" << endl;
	cout << "\t\t /           q,            \\" << endl;
	cout << "\t\t/                           \\" << endl;
	cout << endl << endl;
}