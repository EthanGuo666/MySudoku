// MySudoku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Input.h"
#include "SudokuOperation.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	Input input(argc, argv);
	input.inputTypeAnalyse();
	char type = input.getType();
	int num = input.getNum();
	char* filename = input.getFilename();
	
	SudokuOperation operation;
	if (type == 'c')
		operation.generateEnding(num);
	else
	{
		if (type == 's')
			operation.solveSudoku();
	}

	Output output;



    return 0; 
}