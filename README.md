# Assignment 8
## Submitted by Timofei Podkorytov
for operating systems course in fall 2024
## Compiling: Makefile
The following make commands are available:
```
$ make mwc
```

## Running:
These are inputs that are accepted by the prohram
```
./mwc test.txt
./mwc test.txt mwc.c
./mwc <mwc.c
```
## Files:
- Makefile
- README.md
- Tasks 1&2.md
- mwc.c
- file.h
- file.c
- test.txt
- large_test.txt

Task 1&2.md contain tasks 1 and 2.

Makefile provides make commands. README gives the description of the overall homework submission.

The mwc.c contais the main function that calls a function for input processing and file handling.

file.h and file.c contain the other functions needed to process the data. 

Test files are used to test the functionality of the program in small and large sizes of input.
## Output
Here are some examples of output:
```
$ ./mwc large_test.txt test.txt
3023    74088   505007  large_test.txt
2       8       36      test.txt
3025    74096   505043  total   
```

I have tested the code with examples from the file as well as some other inputs and it aligns with wc. Also, below you can find time measurements:

```
$ time ./mwc large_test.txt large_test.txt test.txt
3023    74088   505007  large_test.txt
3023    74088   505007  large_test.txt
2       8       36      test.txt
6048    148184  1010050 total  

real    0m0.022s
user    0m0.020s
```

```
$ time wc large_test.txt large_test.txt test.txt
   3023   74088  505007 large_test.txt
   3023   74088  505007 large_test.txt
      2       8      36 test.txt
   6048  148184 1010050 total

real    0m0.014s
user    0m0.007s
sys     0m0.006s
```