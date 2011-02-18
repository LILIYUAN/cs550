#include<stdio.h>
#include "nfs.h"

int *read_1(struct rd_wr_t *t, CLIENT *clnt) 
{
	int fd;
	static int result = -1;
	FILE *fp;

	fp = fopen("ournet.log","a");
	fprintf(fp, "file : %s\n", (t)->file);

	if((fd = open((t)->file, 2) < 0))
		return(&result);

	lseek(fd, (t)->offset);

	result = read(fd, (t)->buf, (t)->size);

	fprintf(fp, "buff = %s\n",(t)->buf);

	close(fd);
	fflush(fp);
	fclose(fp);

	return(&result);
}

int *write_1(struct rd_wr_t *t, CLIENT *clnt)
{
	int fd;
	static int result = -1;
	FILE *fp;

	fp = fopen("ournet.log","a");
	fprintf(fp, "file : %s\n", (t)->file);
        fflush(fp);
	
	if((fd = open((t)->file, 2)) < 0)
		return(&result);

	lseek(fd, (t)->offset);

	result = write(fd, (t)->buf, (t)->size);

	close(fd);
	fclose(fp);

	return(&result);
}


