/*
*Pre:
*start KNX server:
*	ex: sudo knxd -t 0xffc -f 9 -e 1.1.141 -c -u /var/run/knx  -c -D -T -R -S -b tpuarts:/dev/ttyKNX0 
*
*/

#include "simpleKNXtransfer.h"
#include <string.h>
uint8_t buffer[500];

int main(int argc,char** argv)
{
int i=0,ret=-1;
int s=sizeof(buffer);

if(argc == 2)
{
	if(strcmp(argv[1],"0")==0)
		ret=readKNX(buffer,sizeof(buffer),"local:/var/run/knx","1/1/141");
	else
		ret=readKNX(buffer,sizeof(buffer),"local:/var/run/knx","1/1/135");
}else
	return -1;


if(ret>0)
{	
	for(i=0;i<s;i++)
	{
		if(buffer[i]!=(i%255)){
			printf("Bit compare error at position %d with %x and %x ",i,buffer[i],i);
			return -1;
		}
		//printf("%c",buffer[i]);
		//if(buffer[i]=='\0')break;
		//if(((char)buffer[i])=='\0') break;
	}
	//printf("\n");
}else{
	printf("Failed.\n");
	return -2; 
}
	printf("Test succeed!!!!!!!!!!!!!!!!!!!!!!!!!");
return 0;
}
