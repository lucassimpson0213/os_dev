cargo +nightly build -p kernel --target ~/c/os_dev/rust/crates/kernel/i686-os.json \
  -Z build-std=core,alloc -Z build-std-features=compiler-builtins-mem --message-format=short

cargo build -p tools  --message-format=short

cargo build -p memory  --message-format=short

cargo build -p kernel_core --message-format=short

cargo build -p elf --message-format=short

cargo build -p drivers --message-format=short

cargo build -p arch_x86 --message-format=short

