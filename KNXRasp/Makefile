SKNX_DIR:=../simpleKNX
#CROSS := /opt/cross/arm-linux-gnueabi
CC :=g++
CCC:=arm-linux-gnueabi-g++
# causes the compiler to auto-detect the architecture of the build computer. -Q -v to your GCC flags to see what optimizations are enabled
HWFLAGS := -march=native -Q -v 
CFLAGS := -pedantic -Wall -std=c++11 #-mfloat-abi=soft #-O2
CPPFLAGS:=
HEADER_1 := -I $(CROSS)/include #-I $(CROSS)/arm-linux-gnueabi/include#-DHARDWARE=0
HEADER_2 := -I /usr/include
HEADER_3 := -I $(SKNX_DIR)/client/c 
HEADER_4 := -I $(SKNX_DIR)/common 
HEADER_5 := -I $(SKNX_DIR)/include
LDFLAGS := -L/opt/cross/lib -lpthread -L$(SKNX_DIR)/lib -leibclient#-lboost_iostreams -lboost_system 
LDFLAGS_proto := -L/usr/lib/x86_64-linux-gnu  -lpthread#-lboost_iostreams -lboost_system 


CSRC := $(wildcard *.cpp)
OBJS := $(CSRC:%.cpp=%.o)
OBJL  := $(wildcard *.o) 
HDRS := $(wildcard *.hpp)


.PHONY: all
all: ipv6-to-KNX-server-all



ipv6-to-KNX-server-all: simpleKNXtransfer ipv6-to-KNX-server 

ipv6-to-KNX-server: $(OBJS) $(SKNX_DIR)/simpleKNXtransfer.o $(SKNX_DIR)/common.o
ifdef CUSTOM
	
	$(CC) $(CFLAGS)  -o $@  $+ $(LDFLAGS_proto)
else
	
	$(CCC) $(CFLAGS)  -o $@ $+ $(LDFLAGS)
endif



%.o: %.cpp $(HDRS)
ifdef CUSTOM
	$(CC) $(CFLAGS) ${HEADER_2}  ${HEADER_3} ${HEADER_4} ${HEADER_5} -c $<	
	
else
	$(CCC) $(CFLAGS) ${HEADER_1} ${HEADER_3} ${HEADER_4} ${HEADER_5} -c $<
	
endif


simpleKNXtransfer:
ifdef CUSTOM
	(cd $(SKNX_DIR); make CUSTOM="x64" simpleKNXtransfer.o)
else
	(cd $(SKNX_DIR); make  simpleKNXtransfer.o)
endif



debug: $(CSRC) $(HDRS)
ifdef CUSTOM
	@echo $(CUSTOM)
	$(CC) $(CFLAGS) ${HEADER_2}  -g -o $@  $+ $(LDFLAGS_proto)
else
	@echo $(CUSTOM)
	$(CCC) $(CFLAGS) ${HEADER_1} -g -o $@ $+  $(LDFLAGS)
endif






.PHONY: clean
clean:
	rm -rf *.o ipv6-to-KNX-server ipv6-to-KNX-server-proto debug
	(cd $(SKNX_DIR); make clean)
