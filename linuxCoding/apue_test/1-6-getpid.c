#include "apue.h"

int main(void)
{
	printf("hello world from process ID %ld\n", (long)getpid()); //getpid's type(return) is pid_t
	exit(0);
}
