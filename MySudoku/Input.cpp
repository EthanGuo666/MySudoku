#include "stdafx.h"
#include "Input.h"
using namespace std;

Input::Input(int argc, char *argv[])
{
	this->argc = argc;
	this->argv = argv;
	filename = NULL;
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
					}
					else  printf("cmd input is anomalous! error found in method Input::inputTypeAnalyse()\n");
				}
			}
		}
	}
	else  printf("%d\n",argc);
	
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

int Input::tran_string_to_int(char string[])
{
	int len = strlen(string);
	int temp_num = 0;
	for (int i = 0; i < len; i++)
	{
		if (string[i] >= '0'&&string[i] <= '9')
			temp_num = temp_num * 10 + (string[i] - '0');
		else  printf("error found in parameter, you should input only integar\n");
	}
	return temp_num;
}
