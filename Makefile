.PHONY: all clean help
.PHONY: kernel kernel-config
.PHONY: linux

include chosen_board.mk

CROSS_COMPILE?=arm-linux-gnueabi-
AARCH64_CROSS_COMPILE?=$(COMPILE_TOOL)/aarch64-linux-gnu-
K_CROSS_COMPILE=$(AARCH64_CROSS_COMPILE)

K_O_PATH=linux-rtk
K_DOT_CONFIG=$(K_O_PATH)/.config

ROOTFS=$(CURDIR)/rootfs/linux/default_linux_rootfs.tar.gz

Q=
J=$(shell expr `grep ^processor /proc/cpuinfo  | wc -l` \* 2)

all: bsp

clean: kernel-clean
	rm -f chosen_board.mk env.sh

distclean: clean
	rm -rf usbflash/

$(K_DOT_CONFIG): linux-rtk
	$(Q)$(MAKE) -C linux-rtk ARCH=arm64 $(KERNEL_CONFIG)

kernel: $(K_DOT_CONFIG)
	$(Q)$(MAKE) -C linux-rtk ARCH=arm64 CROSS_COMPILE=${K_CROSS_COMPILE} -j$J INSTALL_MOD_PATH=output UIMAGE_LOADADDR=0x40008000 Image dtbs
	$(Q)$(MAKE) -C linux-rtk ARCH=arm64 CROSS_COMPILE=${K_CROSS_COMPILE} -j$J INSTALL_MOD_PATH=output modules
	$(Q)$(MAKE) -C linux-rtk ARCH=arm64 CROSS_COMPILE=${K_CROSS_COMPILE} -j$J INSTALL_MOD_PATH=output modules_install
	$(Q)scripts/install_kernel_headers.sh $(K_CROSS_COMPILE)

kernel-clean:
	$(Q)$(MAKE) -C linux-rtk ARCH=arm64 CROSS_COMPILE=${K_CROSS_COMPILE} -j$J distclean
	rm -rf linux-rtk/output/

kernel-config: $(K_DOT_CONFIG)
	$(Q)$(MAKE) -C linux-rtk ARCH=arm64 CROSS_COMPILE=${K_CROSS_COMPILE} -j$J menuconfig
	cp linux-rtk/.config linux-rtk/arch/arm64/configs/$(KERNEL_CONFIG)

bsp: kernel

help:
	@echo ""
	@echo "Usage:"
	@echo "  make bsp             - Default 'make'"
	@echo "  make clean"
	@echo ""
	@echo "Optional targets:"
	@echo "  make kernel           - Builds linux kernel"
	@echo "  make kernel-config    - Menuconfig"
	@echo ""

