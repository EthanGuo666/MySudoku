#include "stdafx.h"
#include "SudokuOperation.h"
#include <string.h>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

SudokuOperation::SudokuOperation() noexcept
{
	memset(move_step_matrix, 0, sizeof(move_step_matrix));
	memset(result_matrix, 0, sizeof(result_matrix));
	num_now = 0;
	success_sign = false;
}

void SudokuOperation::move_step_generate()
{
	int move_dictionary1[2][3] = { { 0,3,6 },{ 0,6,3 } };
	int move_dictionary2[6][3] = { { 1,4,7 },{ 1,7,4 },{ 4,1,7 },{ 4,7,1 },{ 7,4,1 },{ 7,1,4 } };
	int move_dictionary3[6][3] = { { 2,5,8 },{ 2,8,5 },{ 5,2,8 },{ 5,8,2 },{ 8,2,5 },{ 8,5,2 } };
	int i, j, k, count = 0;
	int step[10];
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 6; j++)
		{
			for (k = 0; k < 6; k++)
			{
				memcpy_s(&step[0], 3 * sizeof(int), &move_dictionary1[i][0], 3 * sizeof(int));
				memcpy_s(&step[3], 3 * sizeof(int), &move_dictionary2[j][0], 3 * sizeof(int));
				memcpy_s(&step[6], 3 * sizeof(int), &move_dictionary3[k][0], 3 * sizeof(int));
				memcpy_s(&move_step_matrix[count], 9 * sizeof(int), &step[0], 9 * sizeof(int));
				/*
				memcpy(&step[0], &move_dictionary1[i][0], 3*sizeof(int));
				memcpy(&step[3], &move_dictionary2[j][0], 3*sizeof(int));
				memcpy(&step[6], &move_dictionary3[k][0], 3*sizeof(int));
				memcpy(&move_step_matrix[count], &step[0], 9*sizeof(int));
				*/
				count++;
			}
		}
	}
}

void SudokuOperation::generate_ending(int num)
{
	errno_t err;
	FILE *file;
	err = fopen_s(&file, "sudoku.txt", "w");
	if (err != 0)
		printf("file doesn't exist\n");

	move_step_generate();
	int first_line[9] = { 9,1,2,3,4,5,6,7,8 };
	//for the convenience of operation, joint_line is double first_line
	int joint_line[18];
	while (next_permutation(&first_line[1], &first_line[9]))
	{
		//If we have already generated enough game ending, break
		if (num_now >= num)
			break;
		//use the same permutation for 72 times
		int circle = 72;
		while (circle--)
		{
			//If we have already generated enough game ending, break
			if (num_now >= num)
				break;
			else
			{
				//joint_line is double first_line connected with each other
				memcpy(joint_line, first_line, sizeof(first_line));
				memcpy(&joint_line[9], first_line, sizeof(first_line));
				int i = num_now % 72;
				for (int j = 0; j < 9; j++)
				{
					int step = move_step_matrix[i][j];
					memcpy(&result_matrix[j], &joint_line[step], 9 * sizeof(int));
				}
				if (file != 0)//just for eliminate the warning
				{
					for (int j = 0; j < 9; j++)
					{
						fprintf(file, "%d %d %d %d %d %d %d %d %d\n", result_matrix[j][0], result_matrix[j][1], result_matrix[j][2], result_matrix[j][3], result_matrix[j][4], result_matrix[j][5], result_matrix[j][6], result_matrix[j][7], result_matrix[j][8]);
					}
					fprintf(file, "\n");
				}
				num_now++;
			}
		}
	}
	if(file!=0)
		fclose(file);
}

void SudokuOperation::search_solution(int i, int j, int (&matrix)[9][9])
{
	//if search has come to an end, return.
	if (success_sign == true)
		return;
	else
	{
		//if we have finished searching the last line, return 
		if (i > 8)
		{
			success_sign = true;
			return;
		}
		//if j > 8, which means current line is done, we have two options.
		if (j > 8)
		{
			//if the current line isn't the last line, search for the next line
			if (i < 8)
				search_solution(i + 1, 0, matrix);
			//If the current line is the last line, return
			if (i == 8)
			{
				success_sign = true;
				return;
			}
		}
		else 
		//if current position is not vacant, jump it
		if (matrix[i][j] != 0)
			search_solution(i, j + 1, matrix);
		else
		{
			//if i <= 8 && j <= 8, search in the current line.
			if (i <= 8 && j <= 8)
			{
				//try each number from 1~9 at current position(i,j).
				for (int n = 1; n <= 9; n++)
				{
					if (check(i, j, n, matrix))
					{
						matrix[i][j] = n;
						search_solution(i, j + 1, matrix);
						//If we successfully find a solution at the end of searching, return
						if (success_sign == true)
							return;
						else
							matrix[i][j] = 0;
					}
				}
			}
		}
	}
}

bool SudokuOperation::check(int i, int j, int n, int matrix[9][9])
{
	int col, row;
	//check the numbers in the same horizontal column before we put n at matrix[i][j]
	for (col = 0; col < 9; col++)
	{
		if (matrix[i][col] == n)
			return false;
	}
	//check the numbers in the same vertical row before we put n at matrix[i][j]
	for (row = 0; row < 9; row++)
	{
		if (matrix[row][j] == n)
			return false;
	}
	//check the numbers in the same 3*3 square
	int base_row = (i / 3) * 3;
	int base_col = (j / 3) * 3;
	for (row = base_row; row < base_row + 3; row++)
	{
		for (col = base_col; col < base_col + 3; col++)
		{
			if (matrix[row][col] == n)
				return false;
		}
	}
	//If obey the sudoku rules, return true
	return true;
}

void SudokuOperation::solve_sudoku(char *filename)
{
	errno_t err, erw;
	FILE *rfile, *wfile;
	err = fopen_s(&rfile, filename, "r");
	erw = fopen_s(&wfile, "sudoku.txt", "w");
	if (err != 0 || erw != 0)
		printf("the input or output file doesn't exist\n");
	else
	{
		//Read the file, and get the puzzle matrix in the file
		int puzzle_matrix[9][9];

		//*blank_or_enter is used for engulfing two kinds of characters, ' ' and '\n'
		char blank_or_enter;
		int i, j;

		//this decision is just to eliminate the warnings
		if (rfile != 0 && wfile != 0)
		{
			do
			{
				for (i = 0; i < 9; i++)
				{
					for (j = 0; j < 9; j++)
					{
						fscanf_s(rfile, "%d%c", &puzzle_matrix[i][j], &blank_or_enter, sizeof(int) + sizeof(char));
					}
				}

				//search for one solution in puzzle_matrix[][], fill the puzzle_matrix from puzzle_matrix[0][0]
				search_solution(0, 0, puzzle_matrix);
				success_sign = false;

				for (i = 0; i < 9; i++)
				{
					fprintf(wfile, "%d %d %d %d %d %d %d %d %d\n", puzzle_matrix[i][0], puzzle_matrix[i][1], puzzle_matrix[i][2], puzzle_matrix[i][3], puzzle_matrix[i][4], puzzle_matrix[i][5], puzzle_matrix[i][6], puzzle_matrix[i][7], puzzle_matrix[i][8]);
				}
				fprintf(wfile, "\n");

			} while (fscanf_s(rfile, "%c", &blank_or_enter, sizeof(char)) != EOF);//engulf the '\n' between two sudoku matrixs
		}
	}
	if(rfile!=0)
		fclose(rfile);
	if(wfile!=0)
		fclose(wfile);
}
