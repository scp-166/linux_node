#include "apue.h"
#include <unistd.h>

int main()
{
	if (lseek(STDIN_FILENO,0,SEEK_CUR ) != -1)
		printf("seek OK\n");
	else
		printf("cannot seek\n");
	exit(0);
}
// ./3.1 /etc/passwd
// cat < /etc/passwd | ./3.1
