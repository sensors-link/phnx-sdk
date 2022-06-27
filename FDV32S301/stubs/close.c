/* See LICENSE of license details. */

#include "stub.h"

int _close(int fd)
{
	(void)fd;
	return _stub(EBADF);
}
