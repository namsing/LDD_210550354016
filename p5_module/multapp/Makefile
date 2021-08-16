obj-m:=chardev.o
KDIR=/lib/modules/$(shell uname -r)/build/

all:
	make -C $(KDIR) M=$(PWD) modules
	gcc -o AddApp AddApp.c
	gcc -o SubApp SubApp.c
	gcc -o MulApp MulApp.c
	gcc -o DivApp DivApp.c

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -rf AddApp SubApp MulApp DivApp
install:
	make -C $(KDIR) M=$(PWD) modules_install
