

#include <string.h>
#include "simpleKNXtransfer.h"
#include "virtualethernet.h"
#include <stdarg.h>
  
//#define BUFFER_SIZE (BUFSIZE<STDBUFFERSIZE?BUFSIZE:STDBUFFERSIZE)
#define BUFFER_SIZE BUFSIZE //1500BYTE
void usage(void)
{
    fprintf(stderr,"Usage:\n");
    fprintf(stderr,"server_knx2tun <tun_name> <knx_url> <knx_eibadress>");
}

void prdebug(char *msg, ...){
  int debug=(DEBUG|DO_DEBUG);
  va_list argp;

  if(debug) {
	va_start(argp, msg);
	vfprintf(stderr, msg, argp);
	va_end(argp);
  }
}

int main(int argc,char* argv[])
{
    char buffer[BUFFER_SIZE];
    char url[30]="";
    strcpy(url,argv[2]);
    char eibaddr[15]="";
    strcpy(eibaddr,argv[3]);
    int ret=-1,fd_tun=-1;
	unsigned long int knx2tun=0;
    int nread=0,nwrite=0,plength=0;
    if(argc!=4) usage();
    
    if((fd_tun=initialize_virtual(argv[1]))<0)
    {   
        perror("[server_tun2knx]:initialize_virtual() error");
        return -1;
    }
    
    while(1)
    {
    
        if( (nread=readKNX((uint8_t *)buffer,BUFFER_SIZE,url,eibaddr))<0)
            {   
                perror("[server_tun2knx]:readKNX() error");
                return -2;
            }
        knx2tun++;
        prdebug("KNX2TUN %lu: Read %d bytes from %s over the KNX bus\n",knx2tun,nread,eibaddr);
    
        if( (nwrite=cwrite(fd_tun,buffer,nread))<0)
            {   
                perror("[server_tun2knx]:cread() error");
                return -2;
            }
       
        prdebug("KNX2TUN %lu: Written %d bytes to tun interface\n",knx2tun,nwrite);
       
    }
   
  return 0;



}

