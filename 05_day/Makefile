obj-m = kset-example.o

KDIR = /root/linux
PWD  = $(shell pwd)

default : 
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) modules

clean : 
	$(MAKE) -C $(KDIR)  SUBDIRS=$(PWD) clean

app : 
	arm-linux-gnueabihf-gcc my_input_app.c -o my_app

install : 
	scp  my_app  root@192.168.137.100:
	scp  kset-example.ko  root@192.168.137.100:

