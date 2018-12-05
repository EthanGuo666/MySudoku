#include "stdafx.h"
#include "SudokuOperation.h"
#include <string.h>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

SudokuOperation::SudokuOperation()
{
	memset(move_step_matrix, 0, sizeof(move_step_matrix));
	memset(result_matrix, 0, sizeof(result_matrix));
	num_now = 0;
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
				memcpy(&move_step_matrix[count], step, 9*sizeof(int));
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
		if (num_now >= num)
			break;
		//use the same permutation for 72 times
		int circle = 72;
		while (circle--)
		{
			//If we have already generate enough game ending, break
			if (num_now >= num)
				break;
			else
			{
				memcpy(joint_line, first_line, sizeof(first_line));
				memcpy(&joint_line[9], first_line, sizeof(first_line));
				int i = num_now % 72;
				for (int j = 0; j < 9; j++)
				{
					int step = move_step_matrix[i][j];
					memcpy(&result_matrix[j], &joint_line[step], 9 * sizeof(int));
				}
				fprintf(file, "**************************%d\n", num_now + 1);
				for (int j = 0; j < 9; j++)
				{
					for (int k = 0; k < 8; k++)
					{
						fprintf(file, "%d ", result_matrix[j][k]);
					}
					fprintf(file,"%d\n", result_matrix[j][8]);
				}
				fprintf(file,"\n");
				num_now++;
			}
		}
	}
	fclose(file);
}

void SudokuOperation::solve_sudoku(char *filename)
{
	errno_t err, erw;
	FILE *rfile, *wfile;
	err = fopen_s(&rfile, filename, "r");
	erw = fopen_s(&wfile, "C:\\Users\\Administrator\\Desktop\\MySudoku\\MySudoku\\Debug\\sudoku.txt", "w");
	if (err != 0 || erw != 0)
		printf("the input or output file doesn't exist\n");
	else
	{
		//解一个数独的情况
		int origin_matrix[9][9];
		int i, j;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				//*blank_or_enter is used for engulfing two kinds of characters, ' ' and '\n'
				char blank_or_enter;
				fscanf_s(rfile, "%d%c", &origin_matrix[i][j], &blank_or_enter, sizeof(int) + sizeof(char));
			}
		}
		/*for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				fprintf(wfile, "%d", origin_matrix[i][j]);
			}
			fprintf(wfile, "\n");
		}*/


	}
	fclose(rfile);
	fclose(wfile);
}
