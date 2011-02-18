#include <stdio.h>

main (int argc, char *argv[])
{

	char file[1024];
	char buf[1024];

	int res;

	res= my_write(argv[1], argv[2], 0, strlen(argv[2]));

	printf("Write : Res = %d\n", res);
	
	res = my_read(argv[1], buf, 0, strlen(buf));

	printf("Read : Res = %d buf = %s\n", res, buf);
}
