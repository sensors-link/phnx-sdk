/* See LICENSE of license details. */
#ifndef _NUCLEI_SYS_STUB_H
#define _NUCLEI_SYS_STUB_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "lib_include.h"

static inline int _stub(int err)
{
	(void)err;
	return -1;
}

extern int	   _close(int fd);
extern int	   _fstat(int fd, struct stat *st);
extern int	   _isatty(int fd);
extern off_t   _lseek(int fd, off_t ptr, int dir);
extern int	   __wrap_sprintf(char *str, const char *fmt, ...);
extern ssize_t _read(int fd, void *ptr, size_t len);
extern void *  _sbrk(ptrdiff_t incr);
extern ssize_t _write(int fd, const void *ptr, size_t len);
extern void	   write_hex(int fd, unsigned long int hex);

#endif /* _NUCLEI_SYS_STUB_H */
