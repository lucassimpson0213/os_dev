#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdarg.h>

/* Serial */
int serial_init(void);
void write_serial(char c);
char read_serial(void);

/* Console */
void consputc(char c);
void printk(const char *format, ...);

#endif // UTILS_H
