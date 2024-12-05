This file has the solutions to tasks 1 and 2 for homework 8 for Operating systems course submitted by Timofei Podkorytov.
# Task 1
We know that:
***Physical memory size:  1024 KiB***
***Logical address space page limit: 32***
***Page size: 2048 B***

## A)
We know the total size of the physical memory and the page size. If we divide one by the other we would get the number of frames.
$$1024 * 1024 / 2048 = 512$$
So, the answer would be ***512 frames***.
## B)
How many bits has the address in the logical and physical address spaces?

Here in both cases we have the page offset, which we can calculate. Each page has 2048 bytes and thus if we want to map each byte to a number we would need 2048 different numbers that can be produced by at least logarithm of 2 of that number bits.
$$\log_{2}(2048)=11$$
Thus for page offset we would need 11 bits.

Now we have a difference between the physical and logical memory as while physical memory has 512 frames the logical can only get up to 32 pages. A similar logic can be applied here.  We take logarithms of both numbers.
$$
\log_{2}(512)=9, 
\log_{2}(32)=5
$$
To sum up, logical addressing would require 11+5=***16 bits***, and the physical would need at least 9+11=***20 bits***.

## C)
Based on the previous calculations we can conclude that:
#### Logical memory
- ***5 for page number***
- ***11 for offset***
#### Physical memory
- ***9  for frame number***
- ***11 for offset***

# Task 2
### Process P 1

| page  | logical address | segment |
| ----- | --------------- | ------- |
| p 1,0 | 0x000-0x0FF     | text    |
| p 1,1 | 0x100-0x1FF     | text    |
| p 1,2 | 0x200-0x2FF     | data    |
| p 1,5 | 0x500-0x5FF     | heap    |
| p 1,6 | 0x600-0x6FF     | stack   |
| p 1,8 | 0x800-0x8FF     | stack   |

### Process P 2

| page  | logical address | segment |
| ----- | --------------- | ------- |
| p 2,0 | 0x000-0x0FF     | text    |
| p 2,1 | 0x100-0x1FF     | text    |
| p 2,4 | 0x400-0x4FF     | data    |
| p 2,5 | 0x500-0x5FF     | data    |
| p 2,6 | 0x600-0x6FF     | heap    |
| p 2,8 | 0x800-0x8FF     | stack   |

## A)
Here I wrote the page tables for 2 process in accordance with the descriptions given. The text segments are read only and can be executed, while other segments can be written to and read from. All the pages are valid.
### Process 1
| logical memory | address range | additional bits | frame |
| -------------- | ------------- | --------------- | ----- |
| p 1,0          | 0x800-0x8FF   | r-x-v           | 8     |
| p 1,1          | 0x600-0x6FF   | r-x-v           | 6     |
| p 1,2          | -             | rw-dv           | -     |
| p 1,5          | -             | rw-dv           | -     |
| p 1,6          | 0xB00-0xBFF   | rw-dv           | 11    |
| p 1,8          | 0x300-0x3FF   | rw-dv           | 3     |


### Process 2

| logical memory | address range | additional bits | frame |
| -------------- | ------------- | --------------- | ----- |
| p 2,0          | 0x900-0x9FF   | r-x-v           | 9     |
| p 2,1          | 0xC00-0xCFF   | r-x-v           | 12    |
| p 2,4          | 0x400-0x4FF   | rw-dv           | 4     |
| p 2,5          | 0x100-0x1FF   | rw-dv           | 1     |
| p 2,6          | -             | rw-dv           | -     |
| p 2,8          | -             | rw-dv           | -     |

## B)
Process 1 is executed and a global variable is modified as well as a dynamically allocated string. The string resides in Heap segment as it is allocated dynamically, while the statically allocated global variable is in Data.

Neither data or heap is loaded. Thus **page faults** occur and they are loaded into the first free frame in memory.
### Process 1:

| logical memory | address range | additional bits | frame |
| -------------- | ------------- | --------------- | ----- |
| p 1,0          | 0x800-0x8FF   | r-x-v           | 8     |
| p 1,1          | 0x600-0x6FF   | r-x-v           | 6     |
| p 1,2          | 0x200-0x2FF   | rw-dv           | 2     |
| p 1,5          | 0x500-0x5FF   | rw-dv           | 5     |
| p 1,6          | 0xB00-0xBFF   | rw-dv           | 11    |
| p 1,8          | 0x300-0x3FF   | rw-dv           | 3     |

After the context switch we try to access heap segment of process 2. However, it is not loaded yet. Thus a **page fault**.  We load heap into first free frame. Also, a function call requires the stack segment.

### Process 2

| logical memory | address range | additional bits | frame |
| -------------- | ------------- | --------------- | ----- |
| p 2,0          | 0x900-0x9FF   | r-x-v           | 9     |
| p 2,1          | 0xC00-0xCFF   | r-x-v           | 12    |
| p 2,4          | 0x400-0x4FF   | rw-dv           | 4     |
| p 2,5          | 0x100-0x1FF   | rw-dv           | 1     |
| p 2,6          | 0xA00-0xAFF   | rw-dv           | 10    |
| p 2,8          | 0x700-0x7FF   | rw-dv           | 7     |
## C)
This new segment is read and write to allow memory exchange.

| logical memory | address range | additional bits | frame |
| -------------- | ------------- | --------------- | ----- |
| p 1,0          | 0x800-0x8FF   | r-x-v           | 8     |
| p 1,1          | 0x600-0x6FF   | r-x-v           | 6     |
| p 1,2          | 0x200-0x2FF   | rw-dv           | 2     |
| p 1,4          | 0xD00-0xDFF   | rw-dv           | 13    |
| p 1,5          | 0x500-0x5FF   | rw-dv           | 5     |
| p 1,6          | 0xB00-0xBFF   | rw-dv           | 11    |
| p 1,8          | 0x300-0x3FF   | rw-dv           | 3     |

| logical memory | address range | additional bits | frame |
| -------------- | ------------- | --------------- | ----- |
| p 2,0          | 0x900-0x9FF   | r-x-v           | 9     |
| p 2,1          | 0xC00-0xCFF   | r-x-v           | 12    |
| p 2,2          | 0xD00-0xDFF   | rw-dv           | 13    |
| p 2,4          | 0x400-0x4FF   | rw-dv           | 4     |
| p 2,5          | 0x100-0x1FF   | rw-dv           | 1     |
| p 2,6          | 0xA00-0xAFF   | rw-dv           | 10    |
| p 2,8          | 0x700-0x7FF   | rw-dv           | 7     |

#### Physical memory:

| Frame | Physical Addresses | Loaded page |
| ----- | ------------------ | ----------- |
| 0     | 0x000-0x0FF        | OS          |
| 1     | 0x100-0x1FF        | p 2,5       |
| 2     | 0x200-0x2FF        | p 1,2       |
| 3     | 0x300-0x3FF        | p 1,8       |
| 4     | 0x400-0x4FF        | p 2,4       |
| 5     | 0x500-0x5FF        | p 1,5       |
| 6     | 0x600-0x6FF        | p 1,1       |
| 7     | 0x700-0x7FF        | p2,8        |
| 8     | 0x800-0x8FF        | p 1,0       |
| 9     | 0x900-0x9FF        | p 2,0       |
| 10    | 0xA00-0xAFF        | p 2,6       |
| 11    | 0xB00-0xBFF        | p 1,6       |
| 12    | 0xC00-0xCFF        | p 2,1       |
| 13    | 0xD00-0xDFF        | p 1,4/p 2,2 |
| 14    | 0xE00-0xEFF        |             |
| 15    | 0xF00-0xFFF        |             |

