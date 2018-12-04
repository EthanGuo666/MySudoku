#pragma once
#include <fstream>

class SudokuOperation
{
public:
	//initialize the SudokuOperation class
	SudokuOperation();

	//generate the end of the game if '-c' and an integar are fetched from cmd window
	void generate_ending(int num);

	//solve the Sudoku game if '-s' and filename is fetched from cmd window
	void solve_sudoku();

private:

};
