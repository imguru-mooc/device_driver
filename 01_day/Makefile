obj-m = my_char.o

KDIR = /root/linux
PWD  = $(shell pwd)

default : 
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) modules

app : 
	arm-linux-gnueabihf-gcc my_app.c -o my_app

install : 
	scp  my_app       root@192.168.137.100:
	scp  my_char.ko  root@192.168.137.100:

clean : 
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) clean
