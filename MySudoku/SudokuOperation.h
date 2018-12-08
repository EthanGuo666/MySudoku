#pragma once
#include <fstream>
#include <algorithm>

/*
 When generating the ending of game, revoke the method:generate_ending(). 
 This method will call move_step_generate() during its process.

 When solving the sudoku puzzle, revoke the method:solve_sudoku(). 
 This method will call search_solution() and check() during its process.
*/
class SudokuOperation
{
public:
	//Initialize the SudokuOperation class
	SudokuOperation();

	//Generate the end of the game if '-c' and an integar are fetched from cmd window
	void generate_ending(int num);

	//Generate how many steps each line move, put the result into move_step_matrix
	void move_step_generate();

	//Solve the Sudoku game if '-s' and filename is fetched from cmd window
	void solve_sudoku(char *filename);

	//Method search_solution() is called in solve_sudoku() to search for answer of a given Sudoku puzzle
	void search_solution(int i, int j, int (&matrix)[9][9]);

	//Method check() is based on sudoku rules. It is called when we need to check the validation if we put integar n(1<=n<=9) at matrix[i][j]
	bool check(int i, int j, int n, int matrix[9][9]);

private:
	//The number of game ending now
	int num_now;

	//Record the steps each line need to move
	int move_step_matrix[72][9];

	//Record the game ending
	int result_matrix[9][9];

	//The default value of success_sign is false. But if we successfully find one solution, it will be set as True.
	bool success_sign;
};
