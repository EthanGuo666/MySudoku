#pragma once
#include <fstream>
#include <algorithm>

//When generating the ending of game, 
class SudokuOperation
{
public:
	//Initialize the SudokuOperation class
	SudokuOperation();

	//Generate how many steps each line move, put the result into move_step_matrix
	void move_step_generate();

	//Generate the end of the game if '-c' and an integar are fetched from cmd window
	void generate_ending(int num);

	//Solve the Sudoku game if '-s' and filename is fetched from cmd window
	void solve_sudoku();


private:
	//The number of game ending now
	int num_now;

	//Record the steps each line need to move
	int move_step_matrix[72][9];

	//Record the game ending
	int result_matrix[9][9];
};
