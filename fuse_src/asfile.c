#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* gettattr_callback:
  the file system calls getattr when looking for attributes of specific
  file. The function will fill the stbuffer with the appropriate attributes

  path: path of the the file
  stbuffer: a stat structure that contains attributes of file
  returns: 0 on sucess
*/
static int getattr_callback(const char *path, struct stat *stbuffer) {
  memset(stbuffer, 0, sizeof(struct stat));

  printf("gettattr called. Attributes of %s requested.\n", path);
  stbuffer->st_uid = getuid();  // owner of file
  stbuffer->st_gid = getgid(); // owner of group of file
	stbuffer->st_atime = time( NULL );  // last access time
	stbuffer->st_mtime = time( NULL ); // last modification time

  if ( strcmp( path, "/" ) == 0 ) {
    stbuffer->st_mode = S_IFDIR | 0755; // mode of file, type info, permission info
    stbuffer->st_nlink = 2; // number of hard links to file
    return 0;
  }
  else {
    stbuffer->st_mode = S_IFREG | 0644;
    stbuffer->st_nlink = 1;
    stbuffer->st_size = 1024;  // size of a regular file
    return 0;
 }

 return -1;
}

/* read_callback:
  reads through the content of a speific file. Will read [size] amount of
  characters starting at [offset] position into the [buffer]

  path: path of file to be read
  buffer: where the chunk will be stored
  size: size of the chunk
  offset: where to start reading file content

  returns: number of bytes read sucecssfully
*/

static int read_callback(const char *path, char *buffer, size_t size, off_t offset,
  struct fuse_file_info *fi) {
  char file1234_Content[] = "Hello there. General Kenobi.";
  char *filecontent = NULL;

  if (strcmp(path, "/file1234") == 0) {
    size_t len = strlen(file1234_Content);
    filecontent = file1234_Content;

    if (offset >= len) { // invalid offset
      return 0;
    }
    if (offset + size > len) { // trying to read more than is in file
      memcpy(buffer, filecontent + offset, len - offset); // copy content into buffer
      return len - offset; // number of bytes read
    }
    memcpy(buffer, filecontent + offset, size);
    return size; // number of bytes read
  }

  return -1;
}

/* readdir_callback:
  Lists the files/directories within a given directory

  path: path of directory to be read
  buffer: buffer to put names of files/directories into
  filler: FUSE
  returns: 0 on success

*/
static int readdir_callback(const char *path, void *buffer, fuse_fill_dir_t filler,
  off_t offset, struct fuse_file_info *fi) {

    printf("Reading directory: %s\n", path);

    /* FUSE filler declaration is as follows:
    typedef int (*fuse_fill_dir_t) (void *buf, const char *name,
				const struct stat *stbuf, off_t off);
    */
    filler(buffer, ".", NULL, 0);  // Current Directory
    filler(buffer, "..", NULL, 0); // Parent Directory

    if(strcmp(path, "/") == 0) { // show files of root directory
      filler(buffer, "file1234", NULL, 0);
    }

    return 0;
}


static struct fuse_operations operations = {
  .getattr = getattr_callback,
  .readdir = readdir_callback,
  .read = read_callback,
};

int main(int argc, char *argv[]) {
  return fuse_main(argc, argv, &operations, NULL);
}
