#include <stdio.h>
#include "nfs.h"
#define SERVER "indus"

int my_read(char *file, char *buf, int offset, int size)
{
	CLIENT *clnt;
	int 	*result;
	rd_wr_t	t;

	strcpy(t.file, file);
	t.offset = offset;
	t.size = size;
	
	clnt = clnt_create(SERVER, OURNFS, OURNFSVERS, "tcp");	
	if (clnt == (CLIENT *) NULL) {
                clnt_pcreateerror(SERVER);
                exit(1);
        }

	result = read_1(&t, clnt);

	fprintf(stderr, "my_read() : buf = %s\n", t.buf);

	bcopy(t.buf, buf, 1024);

	return(*result);
}
	
int my_write(char *file, char *buf, int offset, int size)
{
	CLIENT *clnt;
	int 	*result;
        rd_wr_t t;

        strcpy(t.file, file);
        strcpy(t.buf, buf);
        t.offset = offset;      
        t.size = size; 

	clnt = clnt_create(SERVER, OURNFS, OURNFSVERS, "tcp");	
	if (clnt == (CLIENT *) NULL) {
                clnt_pcreateerror(SERVER);
                exit(1);
        }

	result = write_1(&t, clnt);
	return(*result);
}
