/*
 * virtualethernet.cpp
 *
 *  Created on: Sep 22, 2016
 *      Author: sankerspace
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/types.h>
//  #include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
//  #include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <stdarg.h>

#include "virtualethernet.h"

char if_name[IFNAMSIZ]="";
int tun_fd=-1;



/**************************************************************************
 * do_debug: prints debugging stuff                               *
 **************************************************************************/
void do_debug_(char *msg, ...){
  int debug=DEBUG;
  va_list argp;

  if(debug) {
	va_start(argp, msg);
	vfprintf(stderr, msg, argp);
	va_end(argp);
  }
}

/**************************************************************************
 * my_err: prints custom error messages on stderr.                        *
 **************************************************************************/
void my_err_(char *msg, ...) {

  va_list argp;

  va_start(argp, msg);
  vfprintf(stderr, msg, argp);
  va_end(argp);
}





/**************************************************************************
 * tun_alloc: allocates or reconnects to a tun/tap device. The caller     *
 *            must reserve enough space in *dev.                          *
 **************************************************************************/

int tun_alloc(char *dev, int flags) {

  struct ifreq ifr;
  int fd, err;
  //char clonedev[30];
  //strncpy(clonedev,TUN_LOCATION,sizeof(TUN_LOCATION));
  char* clonedev = (char*)TUN_LOCATION;
  if( (fd = open(clonedev , O_RDWR)) < 0 ) {
    perror("[virtualethernet.cpp]:Opening /dev/net/tun");
    return fd;
  }

  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = flags;

  if (*dev) {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if( (err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0 ) {
    perror("[virtualethernet.cpp]:ioctl(TUNSETIFF)");
    close(fd);
    return err;
  }

  strcpy(dev, ifr.ifr_name);


  return fd;
}

/**************************************************************************
 * initialize_virtual: entry point for an virtual TUN interface        *
 *       Initialized for RAW IP Header, no additional Header
 *       Returns: Filedescriptor of the virtual Tun Interface		                                                       *
 **************************************************************************/
int initialize_virtual(const char* tun_name)
{
	do_debug_("[virtualethernet.cpp]:Try to connect to interface %s\n.",tun_name);
	if(tun_name != '\0')
	{
		strcpy(if_name,tun_name);
	}
	 /* initialize tun/tap interface */

	if ( (tun_fd = tun_alloc(if_name, IFF_NO_PI | IFF_TUN | IFF_MULTI_QUEUE)) < 0 ) {
		my_err_("[virtualethernet.cpp]:Error connecting to tun/tap interface %s!\n", (char*)if_name);
	    return -1;
	}
	do_debug_("[virtualethernet.cpp]:Successfully connected to interface %s\n", if_name);
	return tun_fd;

}




/**************************************************************************
 * cread: read routine that checks for errors and exits if an error is    *
 *        returned.                                                       *
 **************************************************************************/
int cread(int fd, char *buf, int n){

  int nread;

  if((nread=read(fd, buf, n)) < 0){
    perror("[virtualethernet.cpp]:Error Reading data");
    return -1;
  }
  return nread;
}

/**************************************************************************
 * cwrite: write routine that checks for errors and exits if an error is  *
 *         returned.                                                      *
 **************************************************************************/
int cwrite(int fd, char *buf, int n){

  int nwrite;

  if((nwrite=write(fd, buf, n)) < 0){
    perror("[virtualethernet.cpp]:Error Writing data");
    return -1;
  }
  return nwrite;
}









