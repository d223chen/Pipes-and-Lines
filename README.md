# Pipes-and-Lines

A terminal program written in C++ which generates random maps/graphs using the classic "Box Builder" characters from Code Page 437.
Code Page 437 is the original IBM PC character set.

Note that, because this program uses windows.h as a header file, it is only functional on a machine running Windows.

I have yet to find a portable "SetConsoleOutputCP" function in C. It looks like this is stuck on Windows for now.
