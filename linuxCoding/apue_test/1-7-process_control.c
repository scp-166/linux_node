#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
	char buf[MAXLINE]; //MAXLINE from apue.h
	pid_t pid;
	int status;

	printf("%% ");	//print %
	while (fgets(buf, MAXLINE, stdin) != NULL)//ctrl+d == EOF, fgets return's type is NULL
	{
		if (buf[strlen(buf) - 1] == '\n') //each line fgets() return is finished by '\n' and NULL
			buf[strlen(buf) - 1] = 0; //execlp need line finished by NULL
	
	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	} else if(pid == 0)	// child
		{
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

	//parent
	if ((pid = waitpid(pid, &status, 0)) < 0)
		err_sys("waitpid error");
	printf("%% ");
	}
	exit(0);
}

