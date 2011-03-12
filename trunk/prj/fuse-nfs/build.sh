gcc -D_FILE_OFFSET_BITS=64 -o pnfs-client pnfs-client.c -lfuse

rpcgen -M -a ds.x
