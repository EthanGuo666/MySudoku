# MySudoku
BITCS, foundmentals of software engineering, personal project 
--developed by Yixuan Guo.

#使用说明：
因为项目中有读取txt文件的操作，所以在命令行中输入待读取的数独题目的时候，请输入绝对路径。
例如：powershell命令行在sudoku.exe的文件夹中打开，输入“./sudoku.exe -s C:\\Users\\Administrator\\Desktop\\puzzle.txt”
即可从文件puzzle.txt中读取题目

#项目结构：

    ├──README.md
    ├──MySudoku
    |    ├──sudoku.cpp
    |    ├──Input.h
    |    ├──Input.cpp
    |    ├──SudokuOperation.h
    |    └──SudokuOperation.cpp
    ├──sudoku_unit_test
    |    └──unittest1.cpp
    └──BIN
         └──sudoku.exe
