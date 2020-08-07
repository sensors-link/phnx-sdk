/* See LICENSE of license details. */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "stub.h"
#include "phnx02.h"

typedef unsigned int size_t;

extern int _put_char(int ch) __attribute__((weak));

ssize_t _write(int fd, const void *ptr, size_t len) {
    const uint8_t *current = (const uint8_t *)ptr;

    if (isatty(fd)) {
        for (size_t jj = 0; jj < len; jj++) {
#if defined(_UART2)
            UART2->SBUF = current[jj]; // sbuf
            while (((UART2->ISR) & 0x00000001) != 0x00000001) {
            };
            UART2->ISR = (0xff << 0); // clear intf
            if (current[jj] == '\n') {
                UART2->SBUF = '\r';
                while (((UART2->ISR) & 0x00000001) != 0x00000001) {
                };
                UART2->ISR = (0xff << 0); // clear intf
            }
#else
            UART1->SBUF = current[jj]; // sbuf
            while (((UART1->ISR) & 0x00000001) != 0x00000001) {
            };
            UART1->ISR = (0xff << 0); // clear intf
            if (current[jj] == '\n') {
                UART1->SBUF = '\r';
                while (((UART1->ISR) & 0x00000001) != 0x00000001) {
                };
                UART1->ISR = (0xff << 0); // clear intf
            }
#endif
        }
        return len;
    }

    return _stub(EBADF);
}

int puts(const char *string) {
    return _write(0, (const void *)string, strlen(string));
}

int _put_char(int ch) { return ch; }
