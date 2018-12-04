#pragma once
#include<fstream>
#include<string.h>

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
	friend int tranStringToInt(char *string);

private:
	int argc;
	char **argv;
	int num;
	char type;
	char* filename;
};

Input::Input(int argc, char *argv[])
{
	this->argc = argc;
	this->argv = argv;
}

void Input::inputTypeAnalyse()
{
	if (argc == 3)
	{
		if (strcmp(argv[1], "-c"))
		{
			type = 'c';
			num = tranStringToInt(argv[2]);
		}
		if (strcmp(argv[1], "-s"))
		{
			type = 's';
			filename = argv[2];
		}
		if (strcmp(argv[2], "-c"))
		{
			type = 'c';
			num = tranStringToInt(argv[1]);
		}
		if (strcmp(argv[2], "-s"))
		{
			type = 's';
			filename = argv[1];
		}
		else  printf("cmd input is anomalous!\n");
	}
	else  printf("the number of parameter in cmd is not 3!\n");
}

int tranStringToInt(char *string)
{
	int len = strlen(string);
	int temp_num = 0;
	for (int i = 0; i < len; i++)
	{
		if(string[i]>='0'&&string[i]<='9')
			temp_num = temp_num * 10 + (string[i] - '0');
		else  printf("error found in parameter, you should input only integar\n");
	}
	return temp_num;
}