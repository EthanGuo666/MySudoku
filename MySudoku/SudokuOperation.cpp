#include "stdafx.h"
#include "SudokuOperation.h"
#include <string.h>
using namespace std;

SudokuOperation::SudokuOperation()
{
	memset(move_step_matrix, 0, sizeof(move_step_matrix));
	memset(result_matrix, 0, sizeof(result_matrix));
	memset(first_line_permutation, 0, sizeof(first_line_permutation));
}

void SudokuOperation::move_step_generate()
{
	int move_dictionary1[2][3] = { { 0,3,6 },{ 0,6,3 } };
	int move_dictionary2[6][3] = { { 1,4,7 },{ 1,7,4 },{ 4,1,7 },{ 4,7,1 },{ 7,4,1 },{ 7,1,4 } };
	int move_dictionary3[6][3] = { { 2,5,8 },{ 2,8,5 },{ 5,2,8 },{ 5,8,2 },{ 8,2,5 },{ 8,5,2 } };
	int i, j, k, count = 0;
	int step[9];
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = 0; k < 6; k++)
			{
				memcpy(step, move_dictionary1[i], 3*sizeof(int));
				memcpy(&step[3], move_dictionary2[j], 3*sizeof(int));
				memcpy(&step[6], move_dictionary3[k], 3*sizeof(int));
				memcpy(&move_step_matrix[count], step, sizeof(int));
				count++;
			}
		}
	}
}

void SudokuOperation::first_line_generate(int num)
{
	
	next_permutation()
}

void SudokuOperation::generate_ending(int num)
{
	//To test if method generate_ending is recalled.
	//printf("%d endings need to be generated!\n", num);
	move_step_generate();

	//double the first line of first Sudoku output, and joint them together
	int first_line[9] = { 9,1,2,3,4,5,6,7,8 };
	int joint_line[18] = { 9,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8 };
	
	

}

void SudokuOperation::solve_sudoku()
{

}
