#include <stdio.h>

int debug(int disk) {
  // for a superblock:
  // print how many blocks
  // print how many inode blocks
  // print how many inodes

  // for an inode:
  // print size and # of direct blocks
  return 0;
}
// opens a file for reading and writing and returns a descriptor used
// to access the disk.
int openDisk(char *filename) {

  return 0;
}

// reads disk block blocknr from the disk pointed to by disk into a
// buffer pointed to by block
int readBlock(int blocknum, void *block) {
  return 0;
}

// writes data in block to disk blocknr pointed to by disk
int writeBlock(int blocknum, void *block) {
  return 0;
}

int stat(int disk, int blocknr) {

}

// forces all outstanding writes to disk
void syncDisk() {

}
