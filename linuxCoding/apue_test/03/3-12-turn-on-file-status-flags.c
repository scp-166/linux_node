#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flag_of_want);
void set_fl(int fd, int flag_of_want)
{
	int val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");
	val |= flag_of_want;	//turn on flag
	//val &= flag_of_want;	//turn off flag
	if (fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
	
}

int main()
{
	//
	

	exit(0);
}

