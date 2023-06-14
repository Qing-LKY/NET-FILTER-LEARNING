SHELL := /bin/bash

KDIR := /lib/modules/`uname -r`/build

MODULE := lab10
obj-m := $(foreach n, $(MODULE), $(n).o)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) modules clean

install:
	insmod $(MODULE).ko

uninstall:
	rmmod $(MODULE).ko