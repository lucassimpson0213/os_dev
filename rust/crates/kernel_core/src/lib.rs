#![no_std]

use core::{ffi::c_void, panic::PanicInfo};

#[unsafe(no_mangle)]
pub extern "C" fn rust_hello() -> u32 {
    0xCAFEBABE
}

#[unsafe(no_mangle)]
pub extern "C" fn rust_idt_entry() -> u32 {
    return 0;
}

#[unsafe(no_mangle)]
pub extern "C" fn rust_ping() -> u32 {
    0xC0FFEEu32
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
