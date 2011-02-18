struct rd_wr_t {
	opaque	file[1024];
	opaque	buf[1024];
	int 	offset;
	int	size;
} ;

program OURNFS {
	version OURNFSVERS {
		int	READ(rd_wr_t) = 1;
		int	WRITE(rd_wr_t) = 2;
	} = 1;
} = 0x20000002;

