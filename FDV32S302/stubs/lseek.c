/* See LICENSE of license details. */

#include "stub.h"

off_t _lseek(int fd, off_t ptr, int dir)
{
	(void)ptr;
	(void)dir;
	if (isatty(fd))
		return 0;

	return _stub(EBADF);
}
