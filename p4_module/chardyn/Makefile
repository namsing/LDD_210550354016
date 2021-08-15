obj-m:=chardev.o
KDIR=/lib/modules/$(shell uname -r)/build/

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o Application Application.c
clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf Application

install:
	make -C $(KDIR) M=$(PWD) modules_install
