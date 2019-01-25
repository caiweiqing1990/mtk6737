ifneq ($(KERNELRELEASE),)
obj-m += pcm_master_gpio.o
else
KERNELDIR=/home/book/work/XY3701_N0/out/target/product/len6737t_66_sh_n/obj/KERNEL_OBJ
PWD=$(shell pwd)
ARCH=arm64
CROSS_COMPILE=/home/book/work/XY3701_N0/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
.PHONY: modules clean
modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	@rm -rf *.o *.su *.order *.symvers *.mod.* .*.o.cmd .*.mod.o.cmd .*.ko.cmd .tmp_versions *.ko
endif
