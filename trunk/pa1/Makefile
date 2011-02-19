
SERVER= ind_srv
CLIENT= 
APPL= 

RPC_X= ind.x 
RPC_SVC= ind_svc.c
RPC_XDR= ind_xdr.c
RPC_CLNT= ind_clnt.c

RPC_FILES= $(RPC_SVC) $(RPC_CLNT) $(RPC_XDR)

SERVER_SRC= ind_svc_proc.c $(RPC_SVC) $(RPC_XDR) 

SERVER_OBJ= $(SERVER_SRC:.c=.o)

# Targets

clean:
	rm -f *.o $(RPC_FILES) $(SERVER) $(CLIENTLIB) $(APPL)

all:
	$(SERVER) $(CLIENT) $(APPL)

$(SERVER): $(SERVER_OBJ)
	cc -o $@ $(SERVER_OBJ) -lnsl
	
.c.o:
	cc -c $<

$(RPC_FILES): $(RPC_X)
	rpcgen $(RPC_X)
	
	
