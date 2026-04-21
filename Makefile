ARCH ?= x86_64
TOOLCHAIN_PATH = /home/user/opt/cross/bin

AS = nasm
ASFLAGS = -f elf64 -g

ifeq ($(ARCH), x86_64)
    CC = $(TOOLCHAIN_PATH)/x86_64-elf-gcc
    LD = $(TOOLCHAIN_PATH)/x86_64-elf-ld
    CFLAGS_ARCH = -m64 -march=x86-64 -mno-red-zone -mcmodel=kernel
    LDFLAGS_ARCH = -T src/kernel/arch/x86_64/linker.ld
endif

CFLAGS = -Wall -Wextra -std=c11 -Iinclude -g \
         -Isrc/drivers -Isrc/hal -Isrc/libstandard \
         -nostdinc -nostdlib -ffreestanding -fno-stack-protector -fno-stack-check \
         -fno-lto -fno-PIE $(CFLAGS_ARCH)

LDFLAGS = $(LDFLAGS_ARCH) -g -static -nostdlib -no-pie -z max-page-size=0x1000

SRCDIR = src
BUILDDIR = build
ISO_ROOT = $(BUILDDIR)/iso_root

SRCS_C = $(shell find $(SRCDIR) -name "*.c")
SRCS_ASM = $(shell find $(SRCDIR) -name "*.asm")
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS_C)) \
	   $(patsubst $(SRCDIR)/%.asm, $(BUILDDIR)/%.asm.o, $(SRCS_ASM))

KERNEL = $(BUILDDIR)/kernel.elf
ISO = ellu-os.iso

all: $(ISO)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.asm.o: $(SRCDIR)/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(KERNEL)

$(ISO): $(KERNEL) limine.conf
	@mkdir -p $(ISO_ROOT)
	cp $(KERNEL) limine.conf limine/limine-bios.sys \
	   limine/limine-bios-cd.bin limine/limine-uefi-cd.bin $(ISO_ROOT)/
	xorriso -as mkisofs -b limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-uefi-cd.bin -efi-boot-part \
		--efi-boot-image --protective-msdos-label \
		$(ISO_ROOT) -o $(ISO)
	./limine/limine bios-install $(ISO)

clean:
	rm -rf $(BUILDDIR) $(ISO) compile_commands.json

.PHONY: all clean