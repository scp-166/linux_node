#include "apue.h"
#include <errno.h>

int
main(int ac, char **av)
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(av[0]);
	exit(0);
}
