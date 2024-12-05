/*
This is assignment 8
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdlib.h>
#include "file.h"

int main(int argc, char* argv[]){
    //variables
    file* files;
    //we get input
    int file_count = getInput(argc, argv, &files);
    //we process files
    processFiles(files, file_count);
    free(files);
    return 0;
}