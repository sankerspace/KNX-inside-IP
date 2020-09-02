CC := gcc

# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
CFLAGS := -pedantic -Wall #-std=c99 #-mfloat-abi=soft#-O2
CFLAGS_Thread := #-D_REENTRANT
CPPFLAGS:=
#HEADER_1 := -I $(CROSS)/include #-I $(CROSS)/arm-linux-gnueabi/include#-DHARDWARE=0
HEADER_2 := -I /usr/include
HEADER_3 := -I ./client/c 
HEADER_4 := -I ./common 
HEADER_5 := -I ./include
LDFLAGS :=# -L/opt/cross/lib -lboost_iostreams -lboost_system -lpthread
LDFLAGS_proto := -L/usr/lib/x86_64-linux-gnu #-lpthread
LDFLAGS_eibd := -L./lib -leibclient

CSRC := $(wildcard *.c)
#OBJS := $(CSRC:%.cpp=%.o)
#OBJL  := $(wildcard *.o) 
HDRS := $(wildcard *.h)


.PHONY: all
all:  server_tun2knx server_knx2tun

virtualKNX: simpleKNXtransfer.o virtualethernet.o ipv6-to-KNX-server.o common.o
		$(CC) $(CFLAGS) $(CFLAGS_Thread)  -o $@  $+ $(LDFLAGS_eibd) $(LDFLAGS_proto)
server_tun2knx: common.o simpleKNXtransfer.o  virtualethernet.o server_tun2knx.o 
		$(CC) $(CFLAGS) $(CFLAGS_Thread)  -o $@  $+ $(LDFLAGS_eibd) $(LDFLAGS_proto)
server_knx2tun: common.o simpleKNXtransfer.o  virtualethernet.o server_knx2tun.o 
		$(CC) $(CFLAGS) $(CFLAGS_Thread)  -o $@  $+ $(LDFLAGS_eibd) $(LDFLAGS_proto)

test: Testwrite-KNX Testlisten-KNX
	
Testwrite-KNX: simpleKNXtransfer.o  Testwrite-KNX.o common.o
	$(CC) $(CFLAGS)  -o $@  $+ $(LDFLAGS_eibd)
Testlisten-KNX:  simpleKNXtransfer.o Testlisten-KNX.o common.o
	$(CC) $(CFLAGS)  -o $@  $+ $(LDFLAGS_eibd)

Testwrite-KNX.o: Testwrite-KNX.c
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $<	

Testlisten-KNX.o: Testlisten-KNX.c
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $<	

simpleKNXtransfer.o: simpleKNXtransfer.c common.h
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $+

virtualethernet.o: virtualethernet.c virtualethernet.h
	$(CC) $(CFLAGS) ${HEADER_2}  -c $+

ipv6-to-KNX-server.o: ipv6-to-KNX-server.c simpleKNXtransfer.h virtualethernet.h 
	$(CC) $(CFLAGS) $(CFLAGS_Thread)  ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $+
server_tun2knx.o: server_tun2knx.c simpleKNXtransfer.h virtualethernet.h 
	$(CC) $(CFLAGS) $(CFLAGS_Thread)  ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $+
server_knx2tun.o: server_knx2tun.c simpleKNXtransfer.h virtualethernet.h 
	$(CC) $(CFLAGS) $(CFLAGS_Thread)  ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $+

common.o: common.c
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -c $<	
	

	

dbgTestwrite-KNX: Testwrite-KNX.c simpleKNXtransfer.c simpleKNXtransfer.h common.c common.h
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -g -o $@  $+ $(LDFLAGS_eibd)	
	 
dbgTestread-KNX: Testlisten-KNX.c simpleKNXtransfer.c simpleKNXtransfer.h common.c common.h
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -g -o $@  $+ $(LDFLAGS_eibd)

dbgserver_tun2knx: server_tun2knx.c simpleKNXtransfer.c simpleKNXtransfer.h virtualethernet.c virtualethernet.h common.c common.h
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -g -o $@  $+ $(LDFLAGS_eibd) $(LDFLAGS_proto)	
dbgserver_knx2tun: server_knx2tun.c simpleKNXtransfer.c simpleKNXtransfer.h virtualethernet.c virtualethernet.h common.c common.h
	$(CC) $(CFLAGS) ${HEADER_2} ${HEADER_3}  ${HEADER_4} ${HEADER_5}  -g -o $@  $+ $(LDFLAGS_eibd) $(LDFLAGS_proto)	


.PHONY: clean
clean:
	rm -rf *.o   dbgTestwrite-KNX dbgTestread-KNX *.gch *.o Testwrite-KNX Testlisten-KNX virtualKNX server_tun2knx server_knx2tun dbgserver_knx2tun dbgserver_tun2knx
