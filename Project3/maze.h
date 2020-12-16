/**************************************************************************************************
*
*   File name :			maze.h
*
*	Programmer:  		Jeremy Atkins
*
*   Header file for the Maze class, implemented in maze.cpp
*
*   Date Written:		in the past
*
*   Date Last Revised:	12/2/2018
*
*	Class Name:		Maze
*
*	Private data members:
*		Tile* current	-	a pointer to a Tile struct as defined in tile.h which points to the current Tile
*		char[][] board	-	a two dimensional array which holds the data for the maze
*		bool init		-	determines whether a maze has been initialized or not
*
*	Private member function:
*		print			-	prints out the maze and the coordinates along the maze
*		destroy			-	deletes neighboring tiles of the current tile
*							
*	Public member functions:
*		Maze			-	constructor for a Maze object
*		solveMaze		-	solves the current maze using a depth first search algorithm
*		generateMaze	-	generates a random maze to be solved
*		mazeFromFile	-	gets a maze from a user input file
****************************************************************************************************/

#ifndef MAZE_H_
#define MAZE_H_
#define SIZ 12
#include "tile.h"
#include <string>

class Maze
{
public:
	Maze();
	void solveMaze();
	void generateMaze();
	bool mazeFromFile(std::string);
private:
	Tile* current;
	char board[SIZ][SIZ];
	void print();
	void destroy();
	bool init;
};
#endif // !MAZE_H_
