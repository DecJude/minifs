KVERS = $(shell uname -r)

# Kernel modules

obj-m += minifs.o

# Specify flags for the module compilation.

build: kernel_modules
kernel_modules:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) modules
clean:
	make -C /lib/modules/$(KVERS)/build M=$(CURDIR) clean
