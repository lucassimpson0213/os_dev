#ifndef UTILS_H
#include <stdint.h>
#include <stdarg.h>

#define UTILS_H

void serial_write_string(const char * string);

/*
What’s going on

"a"(data) → put data in the accumulator register.
Since data is uchar, GCC uses AL (8-bit).

"d"(port) → put port in DX (16-bit I/O port number).

The template "out %0,%1" just drops those operands in order, so the assembler sees:

out %al, %dx


which encodes to the x86 “port-mapped I/O” instruction that writes AL → port in DX.

Size is inferred from the C types:

uchar ⇒ AL (byte) ⇒ byte-sized OUT.

If you wrote a 16-bit version (outw) with ushort data, it would use AX and emit the word form.

volatile → don’t optimize/reorder the asm away.

*/


/*
  When you set the least significant bit and the most signficant bit you have to set the 16 bit values
  using two seperate 8 bit values because the data transmission line is 8 bits

*/
static inline void outb(uint16_t port, uint8_t val)
{
  __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
  uint8_t ret;
  __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

#define PORT 0x3f8 // COM1

static int init_serial()
{
  outb(PORT + 1, 0x00); // Disable all interrupts
  outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
  outb(PORT + 1, 0x00); //                  (hi byte)
  outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
  outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
  outb(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip
  outb(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

  // Check if serial is faulty (i.e: not same byte as sent)
  if (inb(PORT + 0) != 0xAE)
  {
    return 1;
  }

  // If serial is not faulty set it in normal operation mode
  // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
  outb(PORT + 4, 0x0F);
  return 0;
}

int serial_received()
{
  return inb(PORT + 5) & 1;
}

char read_serial()
{
  while (serial_received() == 0)
    ;

  return inb(PORT);
}

int is_transmit_empty()
{
  return inb(PORT + 5) & 0x20;
}

void write_serial(char a)
{
  while (is_transmit_empty() == 0)
    ;

  outb(PORT, a);
}


void printk(char * format, ...) {
    va_list args;


}

void printint() {

}


void ktest_assert()


void consputc(char c) {
    if(c == '\n') {
        write_serial('\r');
    }
    write_serial(c);
}

#endif