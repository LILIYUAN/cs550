gcc -D_FILE_OFFSET_BITS=64 -o pnfs-client pnfs-client.c -lfuse

#-Wall `pkg-config fuse --cflags --libs` pnfs-client.c -o pnfs-client
