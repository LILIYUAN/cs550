rpcgen obtain.x

cc -c obtain_c.c

cc -c obtain_clnt.c

cc -c obtain_xdr.c

cc -o client obtain_c.o obtain_clnt.o obtain_xdr.c

cc -c obtain_s.c

cc -c obtain_svc.c

cc -o server obtain_s.o obtain_svc.o obtain_xdr.c

