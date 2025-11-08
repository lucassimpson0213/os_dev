# Compiler / Linker
CC = i686-elf-gcc
LD = i686-elf-ld

# Flags
CFLAGS  = -ffreestanding -std=gnu11 -nostdlib -fno-builtin -O2 -Wall -Wextra
LDFLAGS = -T linker.ld

# QEMU
QEMU = qemu-system-i386
QEMUFLAGS = -serial stdio

# Source files
OBJS = boot.o kernel.o utils.o str.o pmm.o

# Default target
all: kernel.elf

# Compile assembly
boot.o: boot.s
	$(CC) -c $(CFLAGS) $< -o $@

# Compile C files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Link everything
kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Run with QEMU and serial redirected to terminal
run: kernel.elf
	$(QEMU) $(QEMUFLAGS) -kernel kernel.elf

# Cleanup
clean:
	rm -f *.o kernel.elf


