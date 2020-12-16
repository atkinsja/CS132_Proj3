/**************************************************************************************************
*
*   File name :			maze.cpp
*
*	Programmer:  		Jeremy Atkins
*
*   Implementation of the functions defined in maze.h. Contains the Maze class, which stores
*	and solves a maze either from a file input by the user or from the maze generator also
*	implemented here
*
*   Date Written:		in the past
*
*   Date Last Revised:	12/2/2018
****************************************************************************************************/

//#define DEBUG		turns on debug mode to print the maze and stack each step
#include "maze.h"
#include "validation.h"
#include <stack>
#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

/*******************************************************************************************
*	Function Name:			Maze()	-	the constructor
*	Purpose:				This constructor creates a Maze object and initialized a 
*							boolean determining whether the maze has data in it or not
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
Maze::Maze()
{
	init = false;	//maze has no data to start
}

//not debug mode, only prints the starting maze and the finished maze
#ifndef DEBUG
/*******************************************************************************************
*	Function Name:			mazeFromFile
*	Purpose:				Opens up an input file and gets the maze data and stores it in
*							a two dimensional array
*	Input Parameters:		string inFileName	-	the name of the input file
*	Output Parameters:		none
*	Return value:			bool init	-	whether the maze has been succesfully 
*											initialized or not
********************************************************************************************/
bool Maze::mazeFromFile(string inFileName)
{
	
	ifstream inFile;
	inFile.open(inFileName);

	//can't open input file
	while (!inFile)
	{
		//return that the maze has no data in it
		init = false;
		cout << "Error opening " << inFileName << endl;
		return init;
	}

	//initializes positions in the maze from the file 
	for (int i = 0; i < SIZ; i++)
	{
		for (int j = 0; j < SIZ; j++)
		{

			if (i == 0 || j == 0 || i == SIZ - 1 || j == SIZ - 1)
				board[i][j] = '1';
			else
				inFile >> board[i][j];
		}
	}

	inFile.close();

	//return that the maze has been initialized
	init = true;
	return init;
}

/*******************************************************************************************
*	Function Name:			solveMaze
*	Purpose:				Uses a depth first search strategy along with a stack to 
*							solve a maze
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Maze::solveMaze()
{
	
	stack<Tile*> st;		//stack of tiles used during the search
	int x, y;				//starting position

	//declare a tile and its neighbors
	current = new Tile();
	current->above = new Tile();
	current->below = new Tile();
	current->left = new Tile();
	current->right = new Tile();

	//print the maze
	print();

	//get the starting position from the user
	cout << "Enter the starting position coordinates x and y respectively (-1 to cancel): ";
	validatedInput(x, y, 0, SIZ-1);

	if (x == -1)
		return;

	if (y == -1)
		return;

	//make sure the starting position is not on a wall
	while (board[y][x] == '1')
	{
		cout << "Invalid starting location. Please start on an empty tile." << endl;
		cout << "Enter the starting position: ";
		validatedInput(x, y, 0, SIZ - 1);
	}

	//the starting position is the exit
	if (board[y][x] == 'E')
	{
		cout << "That was the exit!" << endl;
		cout << "I'm free!" << endl;
		return;
	}

	//set up the starting position as the current tile
	current->x = x;
	current->y = y;

	//push the starting position onto the stack
	st.push(current);

	board[current->y][current->x] = 'S';

	//mark the starting position as visited
	current->visited = true;

	//while the stack is not empty, keep looking for an exit
	while (!st.empty())
	{
		//check whether neighboring spaces are empty, if so push that neighbor onto the stack
		//above
		current->above->x = current->x;
		current->above->y = current->y - 1;

		if (board[current->above->y][current->above->x] == '0' || board[current->above->y][current->above->x] == 'E')
			st.push(current->above);
		
		//right
		current->right->x = current->x + 1;
		current->right->y = current->y;

		if (board[current->right->y][current->right->x] == '0' || board[current->right->y][current->right->x] == 'E')
			st.push(current->right);
		
		//below
		current->below->x = current->x;
		current->below->y = current->y + 1;

		if (board[current->below->y][current->below->x] == '0' || board[current->below->y][current->below->x] == 'E')
			st.push(current->below);
		
		//left
		current->left->x = current->x - 1;
		current->left->y = current->y;

		if (board[current->left->y][current->left->x] == '0' || board[current->left->y][current->left->x] == 'E')
			st.push(current->left);

		//make the current tile the top of the stack
		current = st.top();

		//while the current tile is visited and the stack is not empty, keep looking for an exit
		while (current->visited && !st.empty())
		{
			//reset the paths not taken to empty spaces except for the starting position
			if(board[st.top()->y][st.top()->x] != 'S')
				board[st.top()->y][st.top()->x] = '0';

			//remove from the stack
			st.pop();

			//if the stack is empty, no exit could be found
			if (st.empty())
			{
				//delete pointers
				destroy();
				delete current;
				current = NULL;

				//print the maze
				print();
				cout << "I'm trapped!" << endl << endl;
				return;
			}

			//move the current tile to the tile on the top of the stack
			current = st.top();
		}

		//if the current tile is the exit, finish
		if (board[current->y][current->x] == 'E')
		{
			//delete pointers
			destroy();
			delete current;
			current = NULL;

			//print the maze
			print();
			cout << "I'm free!" << endl << endl;
			return;
		}

		//change empty tiles along the path taken
		board[current->y][current->x] = '*';

		//mark the current tile as visited
		current->visited = true;

		//delete all of the pointers
		destroy();

		//declare neighbors for the next current tile
		current->above = new Tile();
		current->right = new Tile();
		current->below = new Tile();
		current->left = new Tile();
	}
}

//Debug option which prints out the maze, stack, and current position at each step
#endif // !DEBUG
#ifdef DEBUG

void Maze::mazeFromFile()
{
	string inFileName = "maze_sample.txt";
	cout << "Enter the name of the file with the maze: " << endl;
	//cin >> inFileName;
	ifstream inFile;
	inFile.open(inFileName);
	if (!inFile)
	{
		cout << "Error opening " << inFileName << endl;
		return;
	}


	for (int i = 0; i < SIZ; i++)
	{
		for (int j = 0; j < SIZ; j++)
		{

			if (i == 0 || j == 0 || i == SIZ - 1 || j == SIZ - 1)
				board[i][j] = '1';
			else
				inFile >> board[i][j];
		}
	}
	

	inFile.close();
}

void Maze::solveMaze()
{
	stack<Tile*> st;
	int x, y;
	current = new Tile();
	current->above = new Tile();
	current->below = new Tile();
	current->left = new Tile();
	current->right = new Tile();
	
	print();

	cout << "Enter the starting position coordinates (-1 to cancel): ";
	cin >> x;

	if (x == -1)
		return;

	cin >> y;

	if (y == -1)
		return;

	while (board[y][x] == '1')
	{
		cout << "Invalid starting location. Please start on a 0." << endl;
		cout << "Enter the starting position: ";
		cin >> x >> y;
	}

	if (board[y][x] == 'E')
	{
		cout << "Exit found" << endl;
		return;
	}
	
	current->x = x;
	current->y = y;

	st.push(current);

	cout << "Pushed start in stack x: " << st.top()->x << " y: " << st.top()->y << endl;

	board[current->y][current->x] = 'S';

	current->visited = true;

	print();


	while (!st.empty())
	{

		cout << "Current x:" << current->x << " y: " << current->y << endl;
		cout << "Above: " << board[current->y - 1][current->x] << endl;
		cout << "Right: " << board[current->y][current->x + 1] << endl;
		cout << "Below: " << board[current->y + 1][current->x] << endl;
		cout << "Left: " << board[current->y][current->x - 1] << endl;

		current->above->x = current->x;
		current->above->y = current->y - 1;

		if (board[current->above->y][current->above->x] == '0' || board[current->above->y][current->above->x] == 'E')
		{
			st.push(current->above);
			cout << "Pushed above in stack x: " << st.top()->x << " y: " << st.top()->y << endl;
		}

		current->right->x = current->x + 1;
		current->right->y = current->y;

		if (board[current->right->y][current->right->x] == '0' || board[current->right->y][current->right->x] == 'E')
		{

			st.push(current->right);
			cout << "Pushed right in stack x: " << st.top()->x << " y: " << st.top()->y << endl;
		}

		current->below->x = current->x;
		current->below->y = current->y + 1;

		if (board[current->below->y][current->below->x] == '0' || board[current->below->y][current->below->x] == 'E')
		{

			st.push(current->below);
			cout << "Pushed below in stack x: " << st.top()->x << " y: " << st.top()->y << endl;
		}

		current->left->x = current->x - 1;
		current->left->y = current->y;

		if (board[current->left->y][current->left->x] == '0' || board[current->left->y][current->left->x] == 'E')
		{
			st.push(current->left);
			cout << "Pushed left in stack x: " << st.top()->x << " y: " << st.top()->y << endl;
		}

		current = st.top();

		cout << "Current Value: " << board[current->y][current->x] << endl;

		while (current->visited && !st.empty())
		{

			cout << "Popped x: " << st.top()->x << " y: " << st.top()->y << endl;
			board[st.top()->y][st.top()->x] = '0';




			st.pop();

			if (st.empty())
			{
				cout << "I'm trapped!" << endl;
				destroy();
				delete current;
				current = NULL;
				return;
			}
			current = st.top();
		}

		if (board[current->y][current->x] == 'E')
		{
			cout << "I'm free!" << endl;
			destroy();
			delete current;
			current = NULL;
			
			print();
			return;
		}



		board[current->y][current->x] = '*';


		current->visited = true;
		cout << "Current x:" << current->x << " y: " << current->y << endl;

		print();

		destroy();
		current->above = new Tile();
		current->right = new Tile();
		current->below = new Tile();
		current->left = new Tile();
		//system("pause");

	}

}

#endif // DEBUG


/*******************************************************************************************
*	Function Name:			generateMaze
*	Purpose:				Generates a random maze which can be solved
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Maze::generateMaze()
{
	//random number genration
	srand((unsigned int)time(NULL));

	//generates data for a random maze
	for (int i = 0; i < SIZ; i++)
	{
		for (int j = 0; j < SIZ; j++)
		{
			if (i == 0 || j == 0 || i == SIZ - 1 || j == SIZ - 1)
				board[i][j] = '1';
			else
			{
				if (rand() % 4 == 2)
					board[i][j] = '1';
				else
					board[i][j] = '0';
			}
		}
	}

	//place an exit at a random location
	board[rand() % 10 + 1][rand() % 10 + 1] = 'E';

}

/*******************************************************************************************
*	Function Name:			print
*	Purpose:				Prints out the maze and the coordinates around the maze
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Maze::print()
{
	//characters used to print the maze
	char wallChar = (char)219;
	char groundChar = (char)240;
	char exitChar = (char)234;
	char startChar = (char)227;

	//print out coordinates
	cout << setw(3) << " ";
	for (int i = 0; i < SIZ; i++)
		cout << setw(3) << i;
	cout << endl;

	//prints out maze
	for (int i = 0; i < SIZ; i++)
	{
		cout << setw(3) << i << " ";
		for (int j = 0; j < SIZ; j++)
		{
			//walls
			if (board[i][j] == '1')
				cout << wallChar << wallChar << wallChar;

			//exit
			else if (board[i][j] == 'E')
				cout << " " << exitChar << " ";

			//empty tiles
			else if (board[i][j] == '0')
				cout << " " << groundChar << " ";

			//starting position
			else if (board[i][j] == 'S')
				cout << " " << startChar << " ";
			else
				cout << " " << board[i][j] << " ";

		}
		cout << endl;
	}

	//the legend for the maze
	cout << "\nLegend:" << endl;
	cout << wallChar << " - Walls" << endl;
	cout << groundChar << " - Empty space" << endl;
	cout << startChar << " - Starting position" << endl;
	cout << exitChar << " - Exit" << endl;
	cout << "* - Path taken\n" << endl;
}


/*******************************************************************************************
*	Function Name:			destroy
*	Purpose:				Deletes all of the neighbor pointers of the current tile
*	Input Parameters:		none
*	Output Parameters:		none
*	Return value:			none
********************************************************************************************/
void Maze::destroy()
{
	//delete neighbors for the current tile
	delete current->above;
	current->above = NULL;

	delete current->right;
	current->right = NULL;
	
	delete current->below;
	current->below = NULL;
	
	delete current->left;
	current->left = NULL;		
}