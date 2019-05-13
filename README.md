# Making a File System with C
Camille Xue, May 9, 2019

## Project Description
For my second Software Systems project, I wanted to implement my own file system in C called AstroFile. Although I didn't get a fully functioning file system working, the idea was to create a file system made up of superblock, inode, and block data structures. After struggling with my first attempt, I ended up creating a simple implementation using FUSE, which is a tool for creating file sytems in user space instead of at a kernel level. 

## File System Design
I created a diagram of how the file system is structured based on Resource 2, the University of Notre Dame File System Lab. The disk is divided into 4KB blocks, which can then be used for different purposes. 

![FileSystemDesign](https://i.ibb.co/9rgBrhp/fs-design.png)

The **superblock** is the first block in the disk, and it contains meta information about the file system. The `magic_number` is used to validate whether or not things are working properly. The `blocks` field describes the total number of blocks on the disk. Next, `inodeBlocks` indicates how many blocks are used for storing inodes. The last field, `inodes` is the number of inodes in each of the inode blocks.


**Inodes** contain the location of the data blocks through direct and indirect pointers. The `indirect` pointer points to an indirection block that contains pointers to data blocks. 

## Reading and Writing Blocks

When blocks are stored in memory, they are stored in a buffer. Each of these buffers is described by a `buffer_head` struct that contains all of the relevant information of that buffer. The `<linux/buffer_head.h>` library provides the definition for `buffer_head` struct. Functions that involve reading or writing blocks utitilze this data structure to access the data of the block. 

As a specific example, the function for getting an inode would have the following in its implementation:
```c
struct Inode *get_inode(SuperBlock *sb, int inode_no) {
    struct buffer_head *bh;
    struct Inode inode = NULL;
    struct Inode *inode_buffer = kmem_cache_alloc(inode_cachep, GFP_KERNEL);

    bh = sb_bread(sb, inodestore_block_number);
    inode = bh->b_data;
    ...
```
The initial inode is located in the b_data of the buffer_head. Now that we have this first inode, we can iterate through all of the inodes until we have located the one given by `inode_no`.
```c
    ...
    for(int i = 0; i< sb->inodes_count; i++) {
        if(inode->inode_no = inode_no) {
            memcpy(inode_buffer, inode, sizeof(*inode_buffer))
        }
        inode++;
    }
    brelse(bh);
    return inode_buffer;
}  
```

In order to read a data block of a given file path `filp`, the buffer head would instead be defined as follows:
```c
    sb = filp->f_path.dentry->d_inode->i_sb;
    bh sb_bread(sb, inode->data_block_number);
```
The `b_data` would then be stored in a buffer that could be copied into a different buffer in the user space using the `copy_to_user` function.


## FUSE File System Implementation
I did not actually finish my AstroFile implementation because I could not manage to get all of the pieces working together, so I decided to create a simple FUSE file system implementation by following the FUSE tutorials listed in the resources. 

Again, FUSE is a tool that is used to create a file system in user space instead of at the kernel level. In order to run my file system, FUSE can be installed using the command:
```
apt-get install gcc fuse libfuse-dev make cmake
```


#### Implementing `read_callback`
```c
static int read_callback(const char *path, char *buffer, size_t size, 
    off_t offset, struct fuse_file_info *fi)
```
The `read` function, reads the file starting at the given `offset` position into the `buffer`. The information in the file can be directly put into the buffer with `memcpy`. For example, if `offset = 0` and `size = 8`, then reading our test file `file1234` would give "Hello th".
```c
memcpy(buffer, filecontent + offset, size);
``` 
#### Implementing `readdir_callback`
```c
static int readdir_callback(const char *path, void *buffer, 
    fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
```
In order to list all the files and directories within a specified directory, the file system calls `readdir`. This function makes use of the FUSE filler struct  which populates the given buffer. 
```c
filler(buffer, ".", NULL, 0);  // Current Directory
filler(buffer, "..", NULL, 0); // Parent Directory
```

In order to mount the file system, you would run the following command:
```
./asfs -f [mountpoint]
```
## Reflection
My original learning goals were to I want to solidify my understanding of how file systems work and how specific data structures are used to keep track of information. I also wanted to learn about more about interacting with data in memory versus disk storage, and I wanted to build on my understanding of blocks and allocation from my first project. I definitely didn't get as far as I'd hoped with the implementation, but I think on a conceptual level, I achieved my learning goals. I think it took more mental work to navigate the pieces that go into making a file system than I anticipated; I spent a lot of time reading about file sytems without knowing what coding in it C should look like. Even when I found examples of full file systems in C, I spent even more time going through them line by line, trying understand how they worked. 

## Resources

[University of Notre Dame Lab Version 1](https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/project06.html) / [Version 2](https://www3.nd.edu/~dthain/courses/cse30341/spring2017/project6/)
* Good graphics explaining overview and file system design
* Source code included
* Detailed explanation of implementation

[Simple File System Implementation by psankar](https://github/com/psankar/simplefs)
* An actual implementation of a simple file system in C.
* Super helpful when I had no idea what I was doing 

[Shichao's Notes on Blocks](https://notes.shichao.io/lkd/ch14)
* Explains the block head struct since I was confused about what the /linux/block_head.h library was being used for


[FUSE File System Tutorial](http://www.maastaar.net/fuse/linux/filesystem/c/2016/05/21/writing-a-simple-filesystem-using-fuse/)
* Very easy to understand and follow through step by step
* Gives explanations of each variable and FUSE structure

[FUSE File System Tutorial 2](https://engineering.facile.it/blog/eng/write-filesystem-fuse/)
* Used in conjunction with the first tutorial
* Some of the variables in the example are not actually defined, so I'm not sure how that worked

[UIC File System Implementation](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/11_FileSystemImplementation.html)
* A LOT of detail about all of the aspects of file system implementation
* Very ugly website
* Describes different methods and data structures to use for various parts of implementation


[MIT File System Lab](http://web.mit.edu/6.033/1997/handouts/html/04sfs.html)
* Resource given from project page
* Gives cursory overview of disk and file system implementation
* No source code to build off of

Trello: [AstroFile Trello Board](https://trello.com/b/5nLQ3kX3/astrofile)
GitHub: [AstroFile Github Repository](https://github.com/camillexue/SoftSysAstroFile)
