/*
*Pre:
*start KNX server:
*	ex: sudo knxd  -t 0xffc -f 9 -e 1.1.135 -u  /var/run/knx  -c -D -T -R -S -b tpuarts:/dev/ttyKNX1
*/
#include "simpleKNXtransfer.h"
#include <string.h>
#include "stdio.h"

//char*  testdata="Willkommen bei KNX.";
//uint8_t buffer[200]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10};
uint8_t buffer[4];

int main(int argc,char** argv)
{
int i,ret;

//int s=strlen(testdata);
int s=sizeof(buffer);
for(i=0;i<s;i++)
{	
	//buffer[i]=(unsigned)testdata[i];
	buffer[i]=i%255;	
}
//printf("Send text: ");printf("%s \n",testdata);

if(argc == 2)
{
	if(strcmp(argv[1],"0")==0)
		ret=sendKNX(buffer,sizeof(buffer),"local:/var/run/knx","1/1/141");
	else
		ret=sendKNX(buffer,sizeof(buffer),"local:/var/run/knx","1/1/135");
}else
	return -1;


return ret;
}
