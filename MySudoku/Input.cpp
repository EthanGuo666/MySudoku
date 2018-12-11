#include "stdafx.h"
#include "Input.h"
using namespace std;

Input::Input(int argc, char *argv[])
{
	this->argc = argc;
	this->argv = argv;
	filename = NULL;
	type = 0;
	num = 0;
	input_error = false;
}

void Input::input_type_analyse()
{
	if (argc == 3)
	{
		if (strcmp(argv[1], "-c") == 0)
		{
			type = 'c';
			num = tran_string_to_int(argv[2]);
		}
		else
		{
			if (strcmp(argv[1], "-s") == 0)
			{
				type = 's';
				filename = argv[2];

				//prevent us from opening a file that doesn't exist
				errno_t err;
				FILE *tryopen;
				err = fopen_s(&tryopen, filename, "r");
				if (err != 0)
				{
					input_error = true;
					printf("The file you want to open doesn't exist\n");
				}
			}
			else
			{
				if (strcmp(argv[2], "-c") == 0)
				{
					type = 'c';
					num = tran_string_to_int(argv[1]);
				}
				else 
				{
					if (strcmp(argv[2], "-s") == 0)
					{
						type = 's';
						filename = argv[1];

						//prevent us from opening a file that doesn't exist
						errno_t err;
						FILE *tryopen;
						err = fopen_s(&tryopen, filename, "r");
						if (err != 0)
						{
							input_error = true;
							printf("The file you want to open doesn't exist\n");
						}
					}
					else
					{
						input_error = true;
						printf("cmd input is anomalous! error found in method Input::inputTypeAnalyse()\n");
					}
				}
			}
		}
	}
	else
	{
		input_error = true;
		printf("Numbers of command parameters are not correct!%d\n", argc);
	}
}

char Input::get_type()
{
	return type;
}

int Input::get_num()
{
	return num;
}

char* Input::get_filename()
{
	return filename;
}

bool Input::found_error()
{
	return input_error;
}

int Input::tran_string_to_int(char string[])
{
	int len = strlen(string);
	int temp_num = 0;
	for (int i = 0; i < len; i++)
	{
		if (string[i] >= '0'&&string[i] <= '9')
			temp_num = temp_num * 10 + (string[i] - '0');
		else
		{
			input_error = true;
			printf("error found in parameter, you should input only integar\n");
			return -1;
		}
	}
	return temp_num;
}
