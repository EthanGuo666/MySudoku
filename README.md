# MySudoku

    BITCS, foundmentals of software engineering, personal project
    --developed by Yixuan Guo.

#使用说明：
    
    1.生成数独终局:
      powershell命令：“./sudoku.exe -c 100000” (在sudoku.exe所在的文件夹中“shift+鼠标右键”打开powershell输入)
      cmd命令：“sudoku.exe -c 100000” (在文件相对路径下打开cmd命令行)
    
    2.求解数独:
      powershell命令：“./sudoku.exe -s puzzle.txt
      cmd命令：“sudoku.exe -s puzzle.txt”
                        
    3.因为项目中有读取txt文件的操作，所以在命令行中输入待读取的数独题目的时候，最好输入绝对路径。
      否则sudoku.exe将从同一路径下读取输入的文件名。
    
    4.在读取txt文件前，请确保题目所在的txt是存在的，否则本程序检测到此异常会打印出温馨提示
    
    

#项目结构：

    ├──README.md
    ├──MySudoku
    |    ├──sudoku.cpp
    |    ├──Input.h
    |    ├──Input.cpp
    |    ├──SudokuOperation.h
    |    └──SudokuOperation.cpp
    ├──sudoku_unit_test
    |    ├──README.md
    |    └──unittest1.cpp
    └──BIN
         └──sudoku.exe
