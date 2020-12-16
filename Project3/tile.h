/**************************************************************************************************
*
*   File name :			tile.h
*
*	Programmer:  		Jeremy Atkins
*
*	A Tile struct representing a current location within the maze
*
*   Date Written:		in the past
*
*   Date Last Revised:	12/2/2018
*
*	Struct Name:		Tile
*
*	Data Members:
*		int x			-	the horizonatal position of the tile
*		int y			-	the vertical position of the tile
*		bool visited	-	whether the tile has been visited or not
*		Tile* above		-	tile pointer pointing to the above neighbor of the current tile
*		Tile* below		-	tile pointer pointing to the below neighbor of the current tile
*		Tile* left		-	tile pointer pointing to the left neighbor of the current tile
*		Tile* right		-	tile pointer pointing to the right neighbor of the current tile
****************************************************************************************************/
#ifndef TILE_H_
#define TILE_H_

struct Tile
{
	int x;
	int y;
	bool visited;
	Tile* above;
	Tile* below;
	Tile* left;
	Tile* right;
};
#endif // !TILE_H_
