# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)
 
	KERNEL_SOURCE := /usr/src/linux-headers-3.13.0-24-generic
	PWD := $(shell pwd)
default: module app
 
module:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules
 
clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean
	${RM} app
 
# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else
 
    obj-m := ATM.o
 
endif
