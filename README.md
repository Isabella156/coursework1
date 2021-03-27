# Code and basic functions
This is a small book management 📕 system written in C language, the main function is to provide services such as borrowing and returning books for the users. New user can user the library by registering 📲, and after logging in, they are able to view books, search for books, borrow books, return books and so on. The system also has a built-in librarian account 👩, who can add or remove books. There will corresponding error message if the user’s input is illegal🙅️.

# Environment
GCC 8.1.0<br/>
Cmake 2.8.12

# Directions for use
## Linux
under project1 folder
```
mkdir build
```


```
cd build
```


```
cmake ..
```


```
make
```


```
./project1
```
## Windows
Generate executable files with the help of **Cmake**

# Code directory structure
project:.<br/>
│ 　books.txt<br/>
│ 　CMakeLists.txt<br/>
│ 　list.txt<br/>
│ 　users.txt<br/>
│ 　storeBook.c<br/>
│<br/>
├─ include<br/>
│ 　book_management.h<br/>
│ 　display.h<br/>
│ 　global.h<br/>
│ 　interface.h<br/>
│ 　user.h<br/>
│<br/>
└─ src<br/>
　　book_management.c<br/>
　　display.c<br/>
　　interface.c<br/>
　　main.c<br/>
　　user.c<br/>
　　lala.c<br/>

This project contains four parts, **header files** are in the **include** folder, which consists of declaration of variables and functions. global.h is used for macro definition in the program, book_management.h is for book management, user.h is for user management, display.h is used for displaying the search results, and interface.h is the interface of the program.The **src** folder is the **source file**. <br/>
The complication and run of the program involves in multiple files, and the **CMakeList.txt** will be helpful for the compiling instead of manually compiling. **books.txt** is the initial library, and the **users.txt** is the initial user library<br/>
**lala.c** is the program single file source code, if you have a problem with multi-file debugging can use this file to try single file debugging
# Frequently Asked Questions
Please **do not modify** books.txt and users.txt file under Windows if the program is run under Linux virtual machine. Because of the different coding methods in the two operating system, the program may not read the file correctly and crash. If it really happens, before the program running, compile and run **storeBook.c** in Linux and uncomment “**storeUserInFile();**” to generate correct text file, then comment off the “storeUserInFile():” and recompile and rerun the program, this program will work fine;
# Version control
- 3.17-3.18<br/>
fix bugs in book management
- 3.19<br/>
output error message when illegally entered
implement modular programming
- 3.20<br/>
fix bugs in multiple files complications
- 3.21<br/>
fix bugs while running in Linux
- 3.23<br/>
pass all test and improve the code style
- 3.24<br/>
add user's name and initial copies of the book
- 3.25<br/>
add free memory function

# Copyright
Copyright © 2019 Bamboo. All rights reserved.

# Reference
XJCO1921 Programming Project, University of Leeds

# Project leader
bambooliulala@gmail.com

# Git repository url
https://github.com/Isabella156/coursework1/tree/main
# Commit history
![avatar](https://i.niupic.com/images/2021/03/27/9fdE.png)
![avatar](https://i.niupic.com/images/2021/03/27/9fdF.png)</br>
This is the first relatively complete programming project that the author has done independently 👀, everyone is welcome to contact me to submit a bug post🤪, although most of the time I am busy with my homework👨‍💻
