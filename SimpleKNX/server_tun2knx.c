

#include <string.h>
#include "simpleKNXtransfer.h"
#include "virtualethernet.h"
#include <stdarg.h>
  
//#define BUFFER_SIZE (BUFSIZE<STDBUFFERSIZE?BUFSIZE:STDBUFFERSIZE)

#define BUFFER_SIZE BUFSIZE //1500BYTE

void usage(void)
{
    fprintf(stderr,"Usage:\n");
    fprintf(stderr,"server_tun2knx <tun_name> <knx_url> <knx_eibadress>");
    exit(1);
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
	unsigned long int tun2knx=0;
    int nread=0,nwrite=0,plength=0;
    if(argc!=4) usage();
    
    if((fd_tun=initialize_virtual(argv[1]))<0)
    {   
        perror("[server_tun2knx]:initialize_virtual() error");
        return -1;
    }
    
    while(1)
    {
        if( (nread=cread(fd_tun,buffer,BUFFER_SIZE))<0)
            {   
                perror("[server_tun2knx]:cread() error");
                return -2;
            }
        tun2knx++;
        prdebug("TUN2KNX %lu: Read %d bytes from tun interface\n",tun2knx,nread);
        if( (nwrite=sendKNX((uint8_t *)buffer,nread,url,eibaddr))<0)
            {   
                perror("[server_tun2knx]:sendKNX() error");
                return -2;
            }
        prdebug("TUN2KNX %lu: Written %d bytes to %s over the KNX bus\n",tun2knx,nwrite,eibaddr);
    }
   
  return 0;


}

