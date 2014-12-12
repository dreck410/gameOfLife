#include <array>
#include <vector>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include "gameOfLife.h"

//prints the grid out
// cells should look like |__X__|

void printCellLine(std::ostream &os,unsigned int W, char delim, char space){
	for (int cell = 0; cell < W; ++cell)
    	os << delim << space << space << space << space << space;
    os << delim << "\n"; 

    
}

template <typename Grid>
void print(std::ostream &os, Grid &theGrid, unsigned int H, unsigned int W) {
  unsigned int j,k;
  printCellLine(os, W, '+', '_');
  printCellLine(os, W, '|', ' ');
  for (j=0; j < H; ++j) {
    os << "|  ";
    if (theGrid[j][0] == 32){
		os << ' '; 				//it's blank
    } else {
    	os << 'X';				//it's got a creature
    }
    for (k=1; k < W; ++k) {
    	
    	os << "  |  ";  //make space
    	if (theGrid[j][k] == 32){
			os << ' '; 				//it's blank
    	} else {
    		os << 'X';				//it's got a creature
    	}
    }
    os << "  |" << std::endl;
    printCellLine(os, W, '+', '_');
    if (j != H - 1)
    	printCellLine(os, W, '|', ' ');
    
  }
}

int main() {

  unsigned int X; //horizontal axiss
  unsigned int Y; // vertical axis
  unsigned int W; // width
  unsigned int H; // height
  unsigned int K;	// number of generations

	puts("0 or any letter to quit");

	puts("Input Width of Rectangle:");
	std::vector<std::vector<unsigned int>> pastGenerations[10];
	while (std::cin >> W && W > 0) 
	{
		puts("Input Height of Rectangle:");
		std::cin >> H;
		if (H > 0){

	      	std::vector<std::vector<unsigned int>> 
	      	vSquare(H, std::vector<unsigned int>(W, ' '));

	      	populate(vSquare, H,W);
	      	puts("Created Eco-System:");
	      	print(std::cout, vSquare, H,W);
	      	puts("Input Number of Generations:");
	      	std::cin >> K;
	      	if(K > 0){
	      		int c = 0;
		      	for (c = 0; c < K; ++c){
		      		
		      		std::cout << "\n----------Generation " << c << "----------\n";
		      		//Go through a ge
		      		pastGenerations[c % 10]= vSquare;


		      		generation(vSquare, H,W);
		      		
		      		if (checkRepeats(pastGenerations, vSquare, H,W, c))
		      		{
		      			
		      			std::cout << "Generations stabalized at " << c << " generations"<< '\n';
		      			
		      			break;
		      		}


		      		//print
		      	}
				print(std::cout, vSquare, H,W);
				std::cout << "Generations stabalized at " << c << " generations"<< '\n';

				puts("0 or any letter to quit");
				puts("Input Width of Rectangle:");
			}//quit on invalid generations
		}//quit on invalid height
	}//while
  return 0;

}