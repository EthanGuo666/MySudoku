#pragma once
#include <fstream>

class SudokuOperation
{
public:
	//initialize the SudokuOperation class
	SudokuOperation();

	//generate how many steps each line move, put the result into move_step_matrix
	void move_step_generate();

	//generate the first line of game ending
	void first_line_generate(int num);

	//generate the end of the game if '-c' and an integar are fetched from cmd window
	void generate_ending(int num);

	//solve the Sudoku game if '-s' and filename is fetched from cmd window
	void solve_sudoku();


private:
	//The number of Sudoku now
	int skd_num_now;
	int move_step_matrix[72][9];
	int result_matrix[1000000][9][9];

};
