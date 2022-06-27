/* See LICENSE of license details. */

#include "stub.h"

int _fstat(int fd, struct stat *st)
{
	if (isatty(fd))
	{
		st->st_mode = S_IFCHR;
		return 0;
	}

	return _stub(EBADF);
}
