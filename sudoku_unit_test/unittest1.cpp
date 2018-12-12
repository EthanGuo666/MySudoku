#include "stdafx.h"
#include "CppUnitTest.h"
#include "../MySudoku/Input.h"
#include "../MySudoku/Input.cpp"
#include "../MySudoku/SudokuOperation.h"
#include "../MySudoku/SudokuOperation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_Sudoku
{
	TEST_CLASS(UnitTest1)
	{
	public:
		int argc;
		char **argv_c, **argv_s;

		UnitTest1()
		{
			argc = 3;
			argv_c = new char*[3];
			argv_s = new char*[3];

			for (int i = 0; i < 3; i++)
			{
				argv_c[i] = new char[100];
				argv_s[i] = new char[100];
			}

			strcpy_s(argv_c[0], 100, "sudoku.exe");
			strcpy_s(argv_c[1], 100, "-c");
			strcpy_s(argv_c[2], 100, "100");

			strcpy_s(argv_s[0], 100, "sudoku.exe");
			strcpy_s(argv_s[1], 100, "-s");
			strcpy_s(argv_s[2], 100, "puzzle.txt");

		}

		//TestMethod1-6 is for testing the Input class

		//test the reaction of method Input::analyse() when it receives a normal "-c" command
		TEST_METHOD(TestMethod1)
		{
			strcpy_s(argv_c[2], 100, "20");
			Input input(argc, argv_c);
			input.input_type_analyse();

			Assert::AreEqual(input.type == 'c', true);
			Assert::AreEqual(input.get_type() == 'c', true);
			Assert::AreEqual(input.num == 20, true);
			Assert::AreEqual(input.get_num() == 20, true);
		}

		//test the reaction of method Input::analyse() when it receives a normal "-s" command
		TEST_METHOD(TestMethod2)
		{
			Input input(argc, argv_s);
			input.input_type_analyse();

			Assert::AreEqual(input.type == 's', true);
			Assert::AreEqual(input.get_type() == 's', true);
			Assert::AreEqual(!strcmp(input.filename, "puzzle.txt"), true);
			Assert::AreEqual(!strcmp(input.get_filename(), "puzzle.txt"), true);
		}

		TEST_METHOD(TestMethod3)
		{
			strcpy_s(argv_c[1], 100, "20");
			strcpy_s(argv_c[2], 100, "-c");
			Input input(argc, argv_c);
			input.input_type_analyse();

			Assert::AreEqual(input.num == 20, true);
			Assert::AreEqual(input.type == 'c', true);
			Assert::AreEqual(input.get_num() == 20, true);
			Assert::AreEqual(input.get_type() == 'c', true);
			Assert::AreEqual(input.found_error() == false, true);
		}

		TEST_METHOD(TestMethod4)
		{
			strcpy_s(argv_s[1], 100, "puzzle.txt");
			strcpy_s(argv_s[2], 100, "-s");
			Input input(argc, argv_s);
			input.input_type_analyse();

			Assert::AreEqual(!strcmp(input.filename, "puzzle.txt"), true);
			Assert::AreEqual(!strcmp(input.get_filename(), "puzzle.txt"), true);
		}

		//test the reaction of method Input::input_type_analyse() when it receives an abnormal "-c" command
		TEST_METHOD(TestMethod5)
		{
			strcpy_s(argv_c[2], 100, "asasasasasas");
			Input input(argc, argv_c);
			input.input_type_analyse();

			Assert::AreEqual(input.tran_string_to_int(argv_c[2]) == -1, true);
			Assert::AreEqual(input.input_error == true, true);
			Assert::AreEqual(input.found_error() == true, true);
		}

		//test the reaction of method Input::analyse() when it receives an abnormal "-s" command
		TEST_METHOD(TestMethod6)
		{
			strcpy_s(argv_s[2], 100, "asasasasasasas");
			Input input(argc, argv_s);
			input.input_type_analyse();

			Assert::AreEqual(input.input_error == true, true);
			Assert::AreEqual(input.found_error() == true, true);
		}

		TEST_METHOD(TestMethod7)
		{
			strcpy_s(argv_c[1], 100, "cc");
			strcpy_s(argv_c[2], 100, "1asasasas");
			Input input(argc, argv_c);
			input.input_type_analyse();

			Assert::AreEqual(input.tran_string_to_int(argv_c[2]) == -1, true);
			Assert::AreEqual(input.input_error == true, true);
			Assert::AreEqual(input.found_error() == true, true);
		}

		TEST_METHOD(TestMethod8)
		{
			strcpy_s(argv_s[1], 100, "ss");
			strcpy_s(argv_s[2], 100, "asasasasasasas");
			Input input(argc, argv_s);
			input.input_type_analyse();

			Assert::AreEqual(input.input_error == true, true);
			Assert::AreEqual(input.found_error() == true, true);
		}


		//TestMethod  9-10 is for testing the SudokuOperation class


		//test the reaction of method SudokuOperation::move_step_generate()
		TEST_METHOD(TestMethod9)
		{
			SudokuOperation sudoku;
			sudoku.move_step_generate();

			//To make sure each of sudoku game ending are different, each line of move_step_matrix[72][9] must be different
			int(*matrix)[9] = sudoku.move_step_matrix;
			bool exist_same_line = true;

			//check each line, if there are two same lines, raise error
			for (int i = 0; i < 71; i++)
			{
				for (int j = i + 1; j < 72; j++)
				{
					exist_same_line = true;
					for (int k = 0; k < 9; k++)
					{
						if (matrix[i][k] != matrix[j][k])
							exist_same_line = false;
					}
					if (exist_same_line == true)
						break;
				}
				if (exist_same_line == true)
					break;
			}

			//raise error
			if (exist_same_line == true)
				Assert::AreEqual(1 == 2, true);
		}

		//function same() is revoked in TestMethod10
		bool same(int matrix1[9][9], int matrix2[9][9])
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (matrix1[i][j] != matrix2[i][j])
						return false;
				}
			}
			return true;
		}

		//test there are no same matrix in output result
		TEST_METHOD(TestMethod10)
		{
			Input input(argc, argv_c);
			input.input_type_analyse();
			SudokuOperation sudoku;
			sudoku.generate_ending(input.get_num());
			FILE *rfile;
			errno_t err;
			err = fopen_s(&rfile, "sudoku.txt", "r");
			if (err != 0)
				Assert::AreEqual(1 == 2, true);
			else
			{
				//read the output file and put the results in a very large matrix, then compare each other 
				char blank_or_enter;
				int result_matrix[2000][9][9];
				for (int i = 0; i < input.get_num(); i++)
				{
					for (int j = 0; j < 9; j++)
					{
						for (int k = 0; k < 9; k++)
						{
							fscanf_s(rfile, "%d", &result_matrix[i][j][k]);
						}
					}
				}

				for (int i = 0; i < input.get_num() - 1; i++)
				{
					for (int j = i + 1; j < input.get_num(); j++)
					{
						if (same(result_matrix[i], result_matrix[j]) == true)
							Assert::AreEqual(1 == 2, true);
					}
				}
			}
		}

	};
}