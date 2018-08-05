//version 1.0
//problem: in show_into, process of time_t is error
#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST


void show_info(struct utmp *utmpfd);

//show info: version 1.0
void show_info(struct utmp *utmpfd)
{
	printf("% -8.8s", utmpfd->ut_name);
	printf(" ");
	printf("% -8.8s", utmpfd->ut_line);
	printf(" ");
	printf("% 10ld", utmpfd->ut_time);
	printf(" ");
#ifdef SHOWHOST
	printf("(%s)", utmpfd->ut_host);
#endif
	printf("\n");
}
int main()
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);

	if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}

	while( read(utmpfd, &current_record, reclen) == reclen)
		show_info(&current_record);
	close(utmpfd);
	return 0;

}

