CC = gcc
CFLAGS = -I/usr/include/tirpc
LIBS = -ltirpc

all: rpcgen_files student_server student_client tests/test_rpc

rpcgen_files:
	rpcgen -C student.x

student_server: student_svc.o server.o student_xdr.o
	$(CC) -o student_server student_svc.o server.o student_xdr.o $(CFLAGS) $(LIBS)

student_client: student_clnt.o client.o student_xdr.o
	$(CC) -o student_client student_clnt.o client.o student_xdr.o $(CFLAGS) $(LIBS)

tests/test_rpc: tests/test_rpc.c student_clnt.o student_xdr.o
	$(CC) -o tests/test_rpc tests/test_rpc.c student_clnt.o student_xdr.o $(CFLAGS) $(LIBS)

student_svc.o: student_svc.c student.h
	$(CC) -c student_svc.c $(CFLAGS)

student_clnt.o: student_clnt.c student.h
	$(CC) -c student_clnt.c $(CFLAGS)

student_xdr.o: student_xdr.c student.h
	$(CC) -c student_xdr.c $(CFLAGS)

server.o: server.c student.h
	$(CC) -c server.c $(CFLAGS)

client.o: client.c student.h
	$(CC) -c client.c $(CFLAGS)

test: tests/test_rpc
	./tests/test_rpc

clean:
	rm -f *.o student_server student_client tests/test_rpc
