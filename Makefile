# Архитектура по умолчанию
ARCH ?= x86_64
TOOLCHAIN_PATH = /home/user/opt/cross/bin

# Настройки компилятора в зависимости от архитектуры
ifeq ($(ARCH), x86_64)
    CC = $(TOOLCHAIN_PATH)/x86_64-elf-gcc
    LD = $(TOOLCHAIN_PATH)/x86_64-elf-ld
    CFLAGS_ARCH = -m64 -march=x86-64 -mno-red-zone -mcmodel=kernel
    LDFLAGS_ARCH = -T src/kernel/arch/x86_64/linker.ld
endif

# Общие флаги
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -ffreestanding \
         -fno-stack-protector -fno-stack-check -fno-lto -fno-PIE \
         $(CFLAGS_ARCH)

LDFLAGS = $(LDFLAGS_ARCH) -static -nostdlib -no-pie -z max-page-size=0x1000

# Директории
SRCDIR = src/kernel
BUILDDIR = build
ISO_ROOT = $(BUILDDIR)/iso_root

# Поиск исходников (рекурсивно)
SRCS = $(shell find $(SRCDIR) -name "*.c")
# Превращаем пути src/file.c в build/src/file.o
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))

KERNEL = $(BUILDDIR)/kernel.elf
ISO = ellu-os.iso

all: $(ISO)

# Компиляция .c -> .o с созданием подпапок в build
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Линковка
$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(KERNEL)

# Сборка ISO
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