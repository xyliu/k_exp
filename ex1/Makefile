obj-m:= complete.o
modules-objs:= complete.o

KDIR:= /usr/src/linux-headers-`uname -r`
PWD:= $(shell pwd)

default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.mod.c *.mod.o *.o *.markers *.symvers *.order

