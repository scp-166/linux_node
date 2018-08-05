// version 2.0
//using ctime() deal with time_t
#include <stdio.h>	//printf
#include <stdlib.h>	//exit()
#include <utmp.h>	//utmp
#include <fcntl.h>	//open
#include <unistd.h>	//read/write
#include <time.h>

//#define SHOWHOST


void show_info(struct utmp *utmpfd);
void showtime(time_t timeval);

//show info: version 2.0
void show_info(struct utmp *utmpfd)
{
	if (utmpfd->ut_type != USER_PROCESS) // no user process
		return;
	printf("% -8.8s", utmpfd->ut_name);
	printf(" ");
	printf("% -8.8s", utmpfd->ut_line);
	printf(" ");
	showtime(utmpfd->ut_time);
#ifdef SHOWHOST
	printf("(%s)", utmpfd->ut_host);
#endif
	printf("\n");
}


void showtime(time_t timeval)
// change time_t type to human language
// Note: %12.12s print a string 12 chars wide and LIMITS
// it to 12 chars
{
	char *cp;
	cp = ctime(&timeval);
	//printf("%s",cp+4);
	printf("%12.12s", cp+4);
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

