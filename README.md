# Remote Student Database using ONC RPC

## Overview
A client-server student database implemented using Linux Sun/ONC RPC.

## Features
- Add student
- Search student
- Update student
- Delete student

## Technologies
- C
- Sun/ONC RPC
- rpcgen
- XDR
- Linux/WSL
- rpcbind

## Architecture

Client
   |
   | RPC
   v
Server
   |
   v
students.dat

## Build

rpcgen -C student.x

gcc -c student_xdr.c -I/usr/include/tirpc
gcc -c server.c -I/usr/include/tirpc

gcc -o student_server student_svc.c server.o student_xdr.o \
    -I/usr/include/tirpc -ltirpc

gcc -o student_client client.c student_clnt.c student_xdr.o \
    -I/usr/include/tirpc -ltirpc

## Run

Start rpcbind:

sudo service rpcbind start

Start server:

./student_server

Run client:

./student_client
