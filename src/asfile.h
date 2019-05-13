
// TODO: #define these or use const?
#define MAGIC_NUMBER        0xf0f04419
#define INODES_PER_BLOCK    128
#define POINTERS_PER_INODE  5
#define POINTERS_PER_BLOCK  1024
#define BLOCK_SIZE          4096

int as_sync(SuperBlock *vsb);
int as_open(char *filename, int nbytes);
int as_read(File *fpoint, void *buf, int n);
int as_write(File *fpoint, void *buf, int n);
int as_create(SuperBlock *vsb, Inode *inode);
int as_getFreeBlock(SuperBlock *vsb, int *out);;
Inode as_seek(SuperBlock *sb, Inode *start, Inode search);
int as_delete(Inode *inode);

DirEntry as_mount(Disk *vdisk);
void as_unmount();

void as_syncDisk();

typedef struct super_block {
  int magicNumber;
  int blocks;
  int inodeBlocks;
  int s_inodesNum;
  int freeBlocks;
} SuperBlock;

typedef struct inode {
  int size;
  int direct[POINTERS_PER_INODE];
  int indirect;
  int mode;

  union {
    int fileSize;
    int dirChild;
  }
} Inode;

typedef struct {

} File;


typedef struct {
  int d_inodeNumber;
  char filename[256];
} DirEntry;

union Block {
  SuperBlock super;                   // superblock
  Inode inodes[INODES_PER_BLOCK];     // inode block
  int pointers[POINTERS_PER_BLOCK];   // pointer block
  char data[BLOCK_SIZE];              // data block
}
