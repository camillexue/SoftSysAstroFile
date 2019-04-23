#include <stdio.h>

// TODO: #define these or use const?
#define MAGIC_NUMBER        0xf0f04419;
#define INODES_PER_BLOCK    128;
#define POINTERS_PER_INODE  5;
#define POINTERS_PER_BLOCK  1024;
#define BLOCK_SIZE          4096;


// TODO: figure out blocknr block, disk, inumber, data
// differences between two reference labs
int openDisk(char *filename, int nbytes);
int readBlock(int disk, int blocknr, void *block);
int writeBlock(int disk, int blocknr, void *block);
void syncDisk();

typedef struct {
  int magicNumber;
  int blocks;
  int inodeBlocks;
  int inodes;
} SuperBlock;

typedef struct {
  int size;
  int direct[POINTERS_PER_INODE];
  int indirect;
} Inode;

union Block {
  SuperBlock super;                   // superblock
  Inode inodes[INODES_PER_BLOCK];     // inode block
  int pointers[POINTERS_PER_BLOCK];   // pointer block
  char data[BLOCK_SIZE];              // data block
}
