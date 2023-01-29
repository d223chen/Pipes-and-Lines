A terminal program written in C++ which tiles the console screen using the classic "Box Builder" characters from Code Page 437. See: https://en.wikipedia.org/wiki/Box-drawing_character
Code Page 437 is the original IBM PC character set.

Note that, because this program uses windows.h as a header file, it is only functional on a machine running Windows.

I have yet to find a portable "SetConsoleOutputCP" function in C. This function is responsible for changing the code page of the console to 437. 
...It looks like this is stuck on Windows for now. :(
