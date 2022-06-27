/* See LICENSE of license details. */

#include "stub.h"

ssize_t _read(int fd, void *ptr, size_t len)
{
	(void)fd;
	(void)ptr;
	(void)len;
	return _stub(EBADF);
}
