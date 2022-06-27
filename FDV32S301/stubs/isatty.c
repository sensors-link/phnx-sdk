/* See LICENSE of license details. */

#include "stub.h"

int _isatty(int fd)
{
	if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
		return 1;

	return 0;
}
