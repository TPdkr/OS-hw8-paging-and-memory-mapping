/*
This is assignment 8
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>

#ifndef FILE_H
#define FILE_H
//here we store the data about a file
typedef struct {
    //input
    char* name;
    //the output data
    int size;
    int lines;
    int words;
} file;

/*
GET INPUT
Gets the number of arguments and array of strings. It also receives
a pointer to an array of files.
*/
int getInput(int argc, char* argv[], file** files);

/*
COUNT REGULAR
Peform counting on a file with normal I/O
*/
int count_reg(file* inp);

/*
COUNT MAP
Perform counting on a file with memory mapping.
*/
int count_map(file* inp);

/*
PROCESS FILES
Process a list of files.
*/
void processFiles(file* files, int file_count);

/*
PRINT FILE
Print the contents of a singular file.
*/
void printFile(file* inp);
#endif