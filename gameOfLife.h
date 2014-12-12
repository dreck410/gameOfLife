//gameOfLife.h
#include <array>
#include <vector>
#include <iomanip>
#include <iostream>
#include <stdlib.h>

template <unsigned int N> 
using grid = std::array<std::array<char, N>, N>;


//randomly generates an 'X' or a ' '
template <typename Grid>
void setLife(Grid &theGrid,unsigned int y, unsigned int x)
{
	int n;
	n = rand() % 2;
	if (n == 1){
		//return life
		theGrid[y][x] =  'X';
	} else {
		//return nothing
		theGrid[y][x] =  ' ';
	}
}

//randomly populates the Grid
template <typename Grid>
void populate(Grid &theGrid, unsigned int H, unsigned int W)
{
	unsigned int x, y;
	//go down the side
	for (y=0; y < H; ++y){
		// radomly populate
		x =0;
		setLife(theGrid,y,x);
		//Go across
		for(x=0; x < W; ++x){
			//randomly populate
			setLife(theGrid,y,x);
		}
	}
}




//checks our x and y and determines if we are on the edge
// sets our iterators so we don't go out of bounds
void checkBounds(unsigned int H,unsigned int W,unsigned int x, unsigned int y,  int &U,  int &D, int &L, int &R)
{

	//top edge
	if (y == 0)
		U = 0;

	//bottom Edge 
	if (y == H - 1)			
		D = 0;

	//left edge
	if (x == 0)
		L = 0;

	//right edge
	if (x == W - 1)
		R = 0;
}

//checks to see if the space is alive
bool isAlive(char space)
{
	if (space == ' '){
		//empty
		return false;
	} else{
		//has life
		return true;
	}
}

template <typename Grid>
bool checkForLife(Grid &theGrid, unsigned int H, unsigned int W)
{
	unsigned int x, y;
	//go down the side
	for (y=0; y < H; ++y){
		//checks for life, returns on teh first encounter
		if(isAlive(theGrid[y][0])){
			return false;
		}
		//Go across
		for(x=0; x < W; ++x){
			//checks for life returns on teh first encounter
			if(isAlive(theGrid[y][x])){
				return false;
			}
			
		}
	}
	//never broke out, no life found
	return true;
}

//checks all of the squares around the cell for life
template <typename Grid>
unsigned int countLife(Grid &theGrid,unsigned int H,unsigned int W, unsigned int y, unsigned int x)
{
	int checkUp    =-1;
	int checkDown  = 1;
	int checkLeft  =-1;
	int checkRight = 1;
	
	//bounds checking
	checkBounds(H,W, x, y, checkUp, checkDown, checkLeft, checkRight);
	unsigned int numOfLife = 0;

	// check all the life around us!
	//life above us!
	if (checkUp != 0){
		if(isAlive(theGrid[y + checkUp][x]))
			++numOfLife;
	}

	//life below us!
	if (checkDown != 0){
		if(theGrid[y + checkDown][x] != 32)
			++numOfLife;
	}

	//life right us!
	if (checkRight != 0){
		if(theGrid[y][x + checkRight] != 32)
			++numOfLife;
	}


	//life left us!
	if (checkLeft != 0){
		if(theGrid[y][x + checkLeft] != 32)
			++numOfLife;
	}

	//Diagnols
	//life topLeft us!
	if (checkUp != 0 && checkLeft != 0){
		if(theGrid[y + checkUp][x + checkLeft] != 32)
			++numOfLife;
	}


	//life topRight us!
	if (checkUp != 0 && checkRight != 0){
		if(theGrid[y + checkUp][x + checkRight] != 32)
			++numOfLife;
	}


	//life bottomLeft us!
	if (checkDown != 0 && checkLeft != 0){
		if(theGrid[y + checkDown][x + checkLeft] != 32)
			++numOfLife;
	}


	//life bottom RIght us!
	if (checkDown != 0 && checkRight != 0){
		if(theGrid[y + checkDown][x + checkRight] != 32)
			++numOfLife;
	}



	return numOfLife;

}

//figures out if the cell should: live, die, or be born 
template <typename Grid>
void change(Grid &theGrid, Grid &theCopy, unsigned int H,unsigned int W, unsigned int y, unsigned int x)
{
	unsigned int numOfLife = countLife(theGrid, H,W, y, x);

	if(isAlive(theGrid[y][x]) == true)
	{//we can die or stay.
		if (numOfLife > 3 || numOfLife < 2)
		{	//die
			theCopy[y][x] = ' ';
		}
		//else remain the same
	} else //not alive
	if (numOfLife == 3)
	{//get born
		theCopy[y][x] = 'X';
	}
	//else stay empty

}

//the 'main' function of the grid
//goes through one generation
//returns the previous Grid
template <typename Grid>
Grid generation(Grid &theGrid, unsigned int H, unsigned int W)
{
	unsigned int y;
	unsigned int x;
	Grid copy = theGrid;
	Grid priorGeneration = theGrid;
	unsigned int numOfLife = 0;
	//Goes down
	for (y=0; y < H; ++y)
	{
		change(theGrid, copy, H,W, y, 0);
		//goes across
		for (x=0; x < W; ++x) {

			change(theGrid, copy, H,W, y,x);

		}

	}
	//makes the grid = the new grid

	theGrid = copy;
	
	return priorGeneration;

}

template <typename Grid>
bool compare(Grid past, Grid cur, unsigned int H, unsigned int W)
{	
	unsigned int y;
	unsigned int x;
	for (y=0; y < H; ++y)
	{	
	
		//if it's not teh same just one time
		if (past[y][0] != cur[y][0])
			return false;
		//goes across
		for (x=0; x < W; ++x) {
			
			//if not the same one time
			if (past[y][x] != cur[y][x])
				return false;
		}
	}
	//all the same
	return true;
}


template <typename Grid>
bool checkRepeats(Grid pastGs[], Grid curG, unsigned int H, unsigned int W, unsigned int size)
{

	for (int i = 0; i < size && i < 10; ++i)
	{
		//if there is one that is the same
		if (compare(pastGs[i], curG, H, W))
		{
			return true;
		}

	}

	return false;
}