COMPILER = gcc
FILESYSTEM_FILES = asfile.c

build: $(FILESYSTEM_FILES)
	$(COMPILER) $(FILESYSTEM_FILES) -o asfs `pkg-config fuse --cflags --libs`
	echo 'To Mount: ./asfs -f [mount point]'
