// #include <stdio.h>
#include <linux/buffer_head.h>
#include <linux/module.h>

#include "asfile.h"
#define DEBUG 1


DirEntry as_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data) {
  DirEntry *ret;

  ret = mount_bdev(fs_type, flags, dev_name, data, as_fill_super);

  return ret;
}

void as_unmount() {
  kill_block_super(sb);
  return;
}

Inode as_createInode(SuperBlock *vsb, int *out) {
  SuperBlock *sb = SuperBlock(vsb);
  struct buffer_head *bh;
  Inode * inode_iterator;

  bh = sb_bread(vsb, 1); // block 1 is the inode block
  inode_iterator = (SuperBlock*)bh->b_data;

  inode_iterator += sb->inodesNum;
  memcpy(inode_iterator, inode, sizeof(Inode));
  sb->inodeNum++;

  brelse(bh);
  as_sync(vsb);

  return inode;
}

void as_destroyInode(Inode *inode) {

  kmem_cache_free(as_inode_cachep, inode);
}

int as_getFreeBlock(SuperBlock *vsb, int *out){
  SuperBlock *sb = SuperBLock(vsb);
  int n;

  for(int i = 3; i < 64; i++) {
    if(sb->free_blocks & (1<<i)) {
      break;
    }
  }

  *out = i;
  // remove the blcok from the free list
  sb->free_blocks &= ~(1<<i);

  as_sync(vsb);

  return i;
}

// looks for given inode number given by search, returns the inode number it locates
Inode* as_seek(SuperBlock *sb, Inode *start, Inode search){
  int count = 0;

  while(start->inode_no != search->inode_no && count < sb->inodesNum) {
    count++;
    start++;
  }

  if(start->inode_no == search->inode_no) {
    return start;
  }
  return NULL;
}


int as_open(char *filename, int nbytes) {
  return 0;
}

int as_read(File *fpoint, void *buf, int n, loff_t *ppos){
  Inode *inode = fpoint->f_path.dirEntry->d.inode);
  struct buffer_head *bh;

  char *buffer;
  int nbytes;

  if(*ppos >= inode->file_size) {
    return 0;
  }

  char *buffer;
  int nbytes;

  bh = sb_bread(fpoint->f_path.dirEntry->d.inode->i_sb, inode->data_block_number);

  buffer = (char*)bh->b_data;
  nbytes =
}

int as_readBlock(SuperBlock *sb, char __user *buf, size_t len) {
  struct buffer_head *bh;

  if(DEBUG) { printk("Read block: %d\n", inodeNum); }

  bh = sb_bread(sb, inodeNum);
  if(!bh) {
    printk("reading block %d failed.", inodeNum);
    return 0;
  }

  char *buffer = (char*)bh->b_data;
  int nbytes = min()

  if(copy_to_user(buf, buffer, nbytes)) {
    brelse(bh);

  }
  brelse(bh);

  if(DEBUG) { printk("Read block done: %d\n", inodeNum); }

  return BLOCK_SIZE;

}

int as_write(File *fpoint, void *buf, int n) {
  return 0;
}


int as_delete(Inode *inode) {
  return 0;
}

// make the super block valid and fill info into super block
void as_fill_super(SuperBlock *sb, void *data, int silent) {
  struct inode * root_inode;
  struct buffer_head *bh;
  SuperBlock *sb_disk;

  bh = sb_bread(sb, 0); // block 0 is the superblock number
  sb_disk = (SuperBlock*)bh->b_data;

  printk("The magic number obtained in disk is %d\n", sb_disk->magicNumber);

  root_inode = make_inode(sb);
  sb->s_root = d_make_root(root_inode);

  brelse(bh);

}

int as_sync(SuperBlock *vsb) {
  struct buffer_head *bh;
  SuperBlock *sb = (struct superblock)(vsb)

  bh = sb_bread(vsb, 0);

  bh->b_data = (char*)sb;

  brelse(bh);
}
