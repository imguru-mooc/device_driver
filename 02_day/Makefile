obj-m = my_mmap.o

KDIR = /root/linux
PWD  = $(shell pwd)

default : 
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) modules

clean : 
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) clean

app : 
	arm-linux-gnueabihf-gcc my_mmap_app.c -o my_app

install : 
	scp  my_app  root@192.168.137.100:
	scp  my_mmap.ko  root@192.168.137.100:

