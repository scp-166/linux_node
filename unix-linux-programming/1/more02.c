//version 2.0
//using /dev/tty to divide the content of file and command of user
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE*);
int see_more(FILE*);

void do_more(FILE *fp)
{
	char line[LINELEN];
	int num_of_lines = 0;
	int reply;
	FILE * fp_tty;
	if ((fp_tty = fopen("/dev/tty", "r")) == NULL )
		exit(1);
	while (fgets(line, LINELEN, fp))	// more input
	{
		if (num_of_lines == PAGELEN)	//full screen
		{
			reply = see_more(fp_tty);	// ask user
			if (reply == 0)		// n:done
				break;
			num_of_lines -= reply;	//reset count
		}
		if ( fputs(line, stdout) == EOF)	// show line
			exit(1);
		num_of_lines++;		// count it
	}
}

int see_more(FILE *fp)
{
	int c;
	printf("more? ");
	while( (c = getc(fp)) != EOF)
	{
		if ( c == 'q')	//exit
			return 0;
		if ( c == ' ')	// next page
			return PAGELEN;
		if ( c == '\n') //next line
			return 1;
	}
	return 0;
}


int main(int ac, char**av)
{
	FILE *fp;
	if (ac == 1)
		do_more(stdin);
	else
		while(--ac)
			if ((fp = fopen(* ++av ,"r")) != NULL)
			{
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
			return 0;
}
