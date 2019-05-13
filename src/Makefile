obj-m := asfile.o
LDFLAGS = -L../../lib -L../../lib64

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules
install: module_install

asfile.o: asfile.c asfile.h
	gcc -c $(LDFLAGS) asfile.c

asfile: asfile.o
	gcc -Wall -o asfile asfile.o

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm asfile
