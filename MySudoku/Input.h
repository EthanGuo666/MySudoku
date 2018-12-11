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
	void input_type_analyse();

	//transform a string to integar
	int tran_string_to_int(char string[]);

	//get the input type:'-c' or '-s', in order to pass these values to SudokuOperation class
	char get_type();

	//get how many Sudoku endings if "-c" command is input, in order to pass these values to SudokuOperation class
	int get_num();

	//get the input filename if "-s" command is input, in order to pass these values to SudokuOperation class
	char* get_filename();

	//If any abnormal command is input and cause an error, this function return true;
	bool found_error();

private:
	int argc;
	char **argv;
	int num;
	char type;
	char* filename;
	bool input_error;
};
