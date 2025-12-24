# # # Compiler / Linker
# # CC = i686-elf-gcc
# # LD = i686-elf-ld
#  RUST_SUPPORT = rust_support/target/i686-unknown-linux-gnu/release/librust_support.a


# # # Flags
# # CFLAGS  = -ffreestanding -std=gnu11 -nostdlib -fno-builtin -O2 -Wall -Wextra
# # LDFLAGS = -T linker.ld

# # # QEMU
# # QEMU = qemu-system-i386
# # QEMUFLAGS = -serial stdio

# # # Source files
#  OBJS = boot.o kernel.o utils.o str.o pmm.o testpmm.o paging.o vm.o setgdt.o

# # # Default target
# # all: kernel.elf

# # # Compile assembly
# # boot.o: boot.s
# # 	$(CC) -c $(CFLAGS) $< -o $@

# # paging.o: paging.s 
# # 	$(CC) -c $(CFLAGS) $< -o $@
# # # Compile C files
# # %.o: %.c
# # 	$(CC) -c $(CFLAGS) $< -o $@

# # $(RUST_SUPPORT):
# # 	cd rust_support && cargo build --release

# # # Link everything
# # kernel.elf: $(OBJS)
# # 	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(RUST_SUPPORT)

# # # Run with QEMU and serial redirected to terminal
# # run: kernel.elf
# # 	$(QEMU) $(QEMUFLAGS) -kernel kernel.elf

# # # Cleanup
# # clean:
# # 	rm -f *.o kernel.elf

# RUST_DIR = rust_support 
#  RUST_LIB := $(RUST_DIR)/target/i686-unknown-none/debug/librust_support.a

# CC = i686-elf-gcc

# # Added -g for debug symbols
# CFLAGS = -std=gnu99 -ffreestanding -g -O2 -Wall -Wextra
# LDFLAGS = -T  linker.ld -nostdlib -lgcc

# #OBJS = boot.o kernel.o 


# $(RUST_LIB):
# 	cd $(RUST_DIR) && cargo build

# kernel.elf: $(OBJS)
# 	$(CC) $(LDFLAGS) -o $@ $(CFLAGS) $(OBJS) $(RUST_LIB) -lgcc

# # Compile Assembly
# boot.o: boot.s
# 	$(CC) -c $< -o $@ $(CFLAGS)

# paging.o: paging.S
# 	$(CC) -c $< -o $@ $(CFLAGS)

# setgdt.o: setgdt.S
# 	$(CC) -c $< -o $@ $(CFLAGS)

# # Compile C
# kernel.o: kernel.c
# 	$(CC) -c $< -o $@ $(CFLAGS)

# # 1. Standard Run
# run: kernel.elf
# 	qemu-system-i386 -kernel kernel.elf -serial stdio

# # 2. Debug Run (Freezes and waits for GDB)
# debug: kernel.elf
# 	qemu-system-i386 -kernel kernel.elf -monitor stdio -s -S

# clean:
# 	rm -f *.o kernel.elf
# 	cd $(RUST_DIR) && cargo clean


# =========================
# Toolchain
# =========================
CC      := i686-elf-gcc
QEMU    := qemu-system-i386

# =========================
# Rust support library
# =========================
RUST_DIR := rust_support
# If you build debug:
RUST_LIB := $(RUST_DIR)/target/i686-os/debug/librust_support.a
# If you want release instead, comment the line above and uncomment this:
# RUST_LIB := $(RUST_DIR)/target/i686-unknown-none/release/librust_support.a

# =========================
# Flags
# =========================
CFLAGS  := -std=gnu99 -ffreestanding -g -O2 -Wall -Wextra -fno-builtin -nostdlib
LDFLAGS := -T linker.ld -nostdlib

# =========================
# Objects
# =========================
OBJS := boot.o kernel.o utils.o str.o pmm.o testpmm.o paging.o vm.o

# =========================
# Default
# =========================
all: kernel.elf

# =========================
# Rust build
# =========================
$(RUST_LIB):
	cd $(RUST_DIR) && cargo build
# If you want release:
# $(RUST_LIB):
# 	cd $(RUST_DIR) && cargo build --release

# =========================
# Compile rules
# =========================
# Assembly
boot.o: boot.s
	$(CC) $(CFLAGS) -c $< -o $@

paging.o: paging.S
	$(CC) $(CFLAGS) -c $< -o $@

setgdt.o: setgdt.S
	$(CC) $(CFLAGS) -c $< -o $@

# C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Link
# =========================
# IMPORTANT: make kernel.elf depend on the Rust library
kernel.elf: $(OBJS) $(RUST_LIB)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(RUST_LIB) -lgcc

# =========================
# Run
# =========================
run: kernel.elf
	$(QEMU) -kernel kernel.elf -serial stdio

debug: kernel.elf
	$(QEMU) -kernel kernel.elf -monitor stdio -s -S

# =========================
# Clean
# =========================
clean:
	rm -f *.o kernel.elf
	cd $(RUST_DIR) && cargo clean

.PHONY: all run debug clean
