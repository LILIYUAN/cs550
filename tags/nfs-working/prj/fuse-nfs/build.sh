#rpcgen -M ds.x
gcc -D_FILE_OFFSET_BITS=64 -o pnfs-client-dummy pnfs-client-dummy.c -lfuse
