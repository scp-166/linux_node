#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //open
#include <unistd.h> //read create

#define BUFFSIZE 4096
#define COPYMODE 0644 	//-rw-r--r--

void oops(char *s1, char *s2);

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s", s1);
	perror(s2);
	exit(1);
}
int main(int ac, char **av)
{
	int in_fd, out_fd, num_of_chars;
	int buf[BUFFSIZE];
	if (ac != 3)
		fprintf(stderr, "usage:%s source destination\n", *av);
	if ((in_fd = open(av[1], O_RDONLY)) == -1)
		oops("Can not open", av[1]);
	if ((out_fd = creat(av[2], COPYMODE)) == -1)
		oops("Can not create", av[2]);
	while ((num_of_chars = read(in_fd, buf, BUFFSIZE)) > 0)	//read successful
		if (write(out_fd, buf, num_of_chars) != num_of_chars)
			oops("Write error to ", av[2]);
	if (num_of_chars == -1)
		oops("Read error from", av[1]);
	if (close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");
	return 0;
}
