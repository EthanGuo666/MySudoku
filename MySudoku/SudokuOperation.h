#pragma once
#include <fstream>

class SudokuOperation
{
public:
	//initialize the SudokuOperation class
	SudokuOperation();

	//generate the end of the game if '-c' and an integar are fetched from cmd window
	void generateEnding(int num);

	//solve the Sudoku game if '-s' and filename is fetched from cmd window
	void solveSudoku();

private:

};
