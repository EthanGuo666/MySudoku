#pragma once
#include<fstream>
#include<string.h>
using namespace std;

//class Input is used for processing the input
class Input
{
public:
	//initialize the Input class, the parameter "argc" and "argv" are used for 
	//fetching the input data from command line
	Input(int argc, char *argv[]);
	
	//the command should be in format like "soduku.exe xxx(argv[1]) xxx(argv[2])".
	//recall this function to analyse the type of command: "-c" or "-s"
	void inputTypeAnalyse();

	//transform a string to integar
	int tranStringToInt(char string[]);

	//get the input type:'-c' or '-s', in order to pass these values to SudokuOperation class
	char getType();

	//get how many Sudoku endings if "-c" command is input, in order to pass these values to SudokuOperation class
	int getNum();

	//get the input filename if "-s" command is input, in order to pass these values to SudokuOperation class
	char* getFilename();

private:
	int argc;
	char **argv;
	int num;
	char type;
	char* filename;
};
