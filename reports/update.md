# Making a File System with C
Camille Xue, April 22, 2019

## Project Description
For my second Software Systems project, I will be using C to create a file system. My lower bound for the project is to create a simple file system that can create, read, and write data on the disk, incorporates data structures like inodes and directories. I will explore different algorithms for implementing allocation, directories, and free space management. For my stretch goal I would want to make a more robust file system that is capable of protecting against certain errors or failures, such as data loss. I would also explore ways to improve the performance of my file system, which could involve caching and buffering.

## Learning Goals
I want to solidify my understanding of how file systems work and how specific data structures are used to keep track of information. I also want to learn about more about interacting with data in memory versus disk storage. Additionally, I want to build on my understanding of blocks and allocation from my first project.

## Current Progress

### File System Design
I created a diagram of how the file system is structured based on Resource 2, the University of Notre Dame File System Lab. The disk is divided into 4KB blocks, which can then be used for different purposes. 

![FileSystemDesign](https://i.ibb.co/9rgBrhp/fs-design.png)

The **superblock** is the first block in the disk, and it contains meta information about the file system. The `magic_number` is used to validate whether or not things are working properly. The `blocks` field describes the total number of blocks on the disk. Next, `inodeBlocks` indicates how many blocks are used for storing inodes. The last field, `inodes` is the number of inodes in each of the inode blocks.

**Inodes** contain the location of the data blocks through direct and indirect pointers. The `indirect` pointer points to an indirection block that contains pointers to data blocks. 


### Disk Library Interface
The first step was to create the library for the disk with all of the appropriate operations necessary for the file system. I decided to follow the MIT lab in addition to the UND lab for the disk interface, which Resource 1. 
* `int openDisk(char *filename)` will open the file that will be used for reading or writing.
* `int readBlock(int blocknum, void *data)` will read the block given by the block number into the buffer pointed to by `data`.
* `int writeBlock(int blocknum, void *data)` writes the the data pointed from `data` into the indicated block. 

### File Operations
This section will be completed once the implementation has been completed.
#### Creating a File
#### Growing & Shrinking a File
#### Deleting a File

## Next Steps
I am behind where I wanted to be in terms of progress, but I will definitely try to work harder in the next week. My next steps are to finish implementing the file operations now that the disk interface is done. For the create operation, I need to allocate and create a new inode and write the new data to the disk. For resizing, I need to load the current inode into memory, remove or add disk block pointers from the inode, and modify the disk blocks accordingly. I also need to create the tests for these functions in order and debug the file system once I start running those tests. 


## Resources
[MIT File System Lab](http://web.mit.edu/6.033/1997/handouts/html/04sfs.html)
* Resource given from project page
* Gives cursory overview of disk and file system implementation
* No source code to build off of

[University of Notre Dame Lab Version 1](https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/project06.html) / [Version 2](https://www3.nd.edu/~dthain/courses/cse30341/spring2017/project6/)
* Good graphics explaining overview and file system design
* Source code included
* Detailed explanation of implementation

[UIC File System Implementation](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/11_FileSystemImplementation.html)
* A LOT of detail about all of the aspects of file system implementation
* Very ugly website
* Describes different methods and data structures to use for various parts of implementation


Trello: [AstroFile Trello Board](https://trello.com/b/5nLQ3kX3/astrofile)
GitHub: [AstroFile Github Repository](https://github.com/camillexue/SoftSysAstroFile)
