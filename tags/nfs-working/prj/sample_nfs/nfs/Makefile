
SERVER=	ournfsd
CLIENTLIB= libournfs
APPL= mytest

RPC_X= nfs.x
RPC_SVC= nfs_svc.c
RPC_XDR= nfs_xdr.c
RPC_CLNT= nfs_clnt.c

RPC_FILES= $(RPC_SVC) $(RPC_CLNT) $(RPC_XDR)

SERVER_SRC= nfs_proc.c $(RPC_SVC) $(RPC_XDR) 
CLIENTLIB_SRC= ournfs.c $(RPC_CLNT) $(RPC_XDR)

APPL_SRC= mytest.c 

SERVER_OBJ= $(SERVER_SRC:.c=.o)
CLIENTLIB_OBJ= $(CLIENTLIB_SRC:.c=.o)

APPL_OBJ= $(APPL_SRC:.c=.o)

# Targets

clean:
	rm -f *.o $(RPC_FILES) $(SERVER) $(CLIENTLIB) $(APPL)

all:
	$(SERVER) $(CLIENTLIB) $(APPL)

$(SERVER): $(SERVER_OBJ)
	cc -o $@ $(SERVER_OBJ) -lnsl
	
$(CLIENTLIB): $(CLIENTLIB_OBJ)
	ar -r $(CLIENTLIB).a $(CLIENTLIB_OBJ)
	ld -G -o $(CLIENTLIB).so $(CLIENTLIB_OBJ) -lnsl

$(APPL): $(APPL_OBJ)
	cc -o $@ $(APPL_OBJ)  -L. -lournfs


.c.o:
	cc -c $<

$(RPC_FILES): $(RPC_X)
	rpcgen $(RPC_X)
	
	
