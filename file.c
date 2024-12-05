/*
This is assignment 8
Done by Timofei Podkorytov
for Operating systems course
in fall 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <ctype.h>
#include "file.h"

//GET INPUT--------------------------------------------------------------------
int getInput(int argc, char* argv[], file** files){
    int file_count=0;
    if (argc==1){
        //we need to allocate memory
        *files = (file*) malloc(sizeof(file));
        if(files==NULL){
            fprintf(stderr,"mwc: Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        //we save the file as stdin
        (*files)[0].name="-";
        file_count=1;
    } else {
        //we allocate memory
        *files = (file*) malloc(sizeof(file)*(argc-1));
        if(*files==NULL){
            fprintf(stderr,"mwc: Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        file_count=argc-1;
        //we transfer names
        for(int i=0;i<file_count;i++){
            file temp;
            temp.name=argv[i+1];
            (*files)[i]=temp;
        }
    }
    //default values are set
    for (int i=0;i<file_count;i++){
        (*files)[i].words=0;
        (*files)[i].lines=0;
        (*files)[i].size=0;
    }
    return file_count;
}

//COUNT REGULAR----------------------------------------------------------------
int count_reg(file* inp){
    FILE* input;
    int c;
    int hadWord=0;
    //we open the appropriate file
    if (strcmp(inp->name, "-")==0){
        input=stdin;
    } else {
        input= fopen(inp->name, "r");
        if (input==NULL){
            fprintf(stderr,"mwc: Error opening file while counting\n");
            return -1;
        }
    }
    //we process contents
    while ((c = getc(input)) != EOF) {
        inp->size++;
        if(isspace(c) && hadWord){
            inp->words++;
            hadWord=0;
        } else if(!isspace(c)) {
            hadWord=1;
        }
        if(c=='\n'){
            inp->lines++;
        }
    }
    //was the last character a non space? Need to count that word
    if(hadWord){
        inp->words++;
    }
    //we check for errors in stream 
    if (ferror(input)) {
        fprintf(stderr,"mwc: Error in input stream\n");
        return -1;
    }
    //we close if needed
    if(input!=stdin){
        fclose(input);
    }
    return 0;
}

//COUNT MAP--------------------------------------------------------------------
int count_map(file* inp){
    int hadWord=0;
    int fd;
    char *base;
    struct stat buf;
    //we try to obtain the file descriptor
    fd=open(inp->name, O_RDONLY);
    if(fd == -1){
        fprintf(stderr,"Error opening file\n");
        return -1;
    }
    //We check for error and whether it is regular
    if (fstat(fd, &buf) == -1 || ! S_ISREG(buf.st_mode)) {
        close(fd);
        count_reg(inp);
        return -2;
    }
    base = mmap(0, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    //we check if mapping was successful
    if (base == MAP_FAILED) {
        close(fd);
        count_reg(inp);
        return -2;
    }
    //we process contents
    inp->size=buf.st_size;
    for(int j=0; j<buf.st_size;j++) {
        int c=base[j];
        if(isspace(c) && hadWord){
            inp->words++;
            hadWord=0;
        } else if(!isspace(c)) {
            hadWord=1;
        }
        if(c=='\n'){
            inp->lines++;
        }
    }
    //was the last character a non space? Need to count that word
    if(hadWord){
        inp->words++;
    }
    //we unmapp the memory and close the file descriptor
    (void) munmap(base, buf.st_size);
    close(fd);
    return 0;
}

//PROCESS FILES----------------------------------------------------------------
void processFiles(file* files, int file_count){
    for(int i=0;i<file_count;i++){
        //are we using stdin?
        if(strcmp(files[i].name,"-")==0){
            count_reg(&files[i]);
            break;
        }
        count_map(&files[i]);
    }
    //we count total
    file total;
    total.name="total";
    total.words=0;
    total.lines=0;
    total.size=0;
    //we print the outputs
    for(int i=0;i<file_count;i++){
        printFile(&files[i]);
        total.lines+=files[i].lines;
        total.words+=files[i].words;
        total.size+=files[i].size;
    }
    //print total if needed
    if(file_count>1){
        printFile(&total);
    }
}

//PRINT FILE-------------------------------------------------------------------
void printFile(file* inp){
    printf("%-7d %-7d %-7d ", inp->lines, inp->words, inp->size);
    if (strcmp(inp->name,"-")!=0){
        printf("%-7s", inp->name);
    }
    printf("\n");
}