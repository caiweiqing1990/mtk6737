ifneq ($(KERNELRELEASE),)
obj-m += pcm_master_gpio.o
#obj-m += pcm_slave_gpio.o
else
PWD=$(shell pwd)
KERNELDIR=$(PWD)/../../../out/target/product/len6737t_66_sh_n/obj/KERNEL_OBJ
ARCH=arm64
CROSS_COMPILE=$(PWD)/../../../prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
.PHONY: modules clean
modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	@rm -rf *.o .*su *su *.order *.symvers *.mod.* .*.o.cmd .*.mod.o.cmd .*.ko.cmd .tmp_versions *.ko
endif
