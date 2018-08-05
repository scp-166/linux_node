// extra function for who03.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>

#define LEN 16
#define NULLUTMP ((struct utmp*)NULL)
#define UTMPSIZE (sizeof(struct utmp))

static char utmpbuf[LEN*UTMPSIZE];
static int fd_utmp = -1;
static int num_step;
static int cur_step;

int utmp_open(char *filename)
{
	fd_utmp = open(filename, O_RDONLY);
	num_step = cur_step = 0;
	return fd_utmp;
}

struct utmp *utmp_next()
{
	struct utmp *value_addr;
	if (fd_utmp == -1)
		return NULLUTMP;
	if (cur_step == num_step && utmp_reload()== 0) // if cur_step==num_step is false, skipping utmp_reload()==0
		return NULLUTMP;
	value_addr = (struct utmp *)&utmpbuf[cur_step*UTMPSIZE];
	cur_step++;
	return value_addr;
}
int utmp_reload()
//read next bunch of records into buffer
{
	int value_read;
	value_read = read(fd_utmp, utmpbuf, LEN*UTMPSIZE);
	num_step = value_read / UTMPSIZE;	//cacular total len of leaf
	cur_step = 0;
	return num_step;
}
utmp_close()
{
	if(fd_utmp != -1)
		close(fd_utmp);
}
