


#include "Test_TUN.hpp"
#include <sys/types.h>
#include <errno.h>
#include <inttypes.h>
//#include
/*read packet data from tun1 and forward them to tun2*/
int testserver(string tun1,string tun2 )
{
	int fd1,fd2,ret,max_fd;
	fd_set rd_set;
	//struct timeval tv;
	//tv.tv_sec=1;
	//tv.tv_usec=0;
	char buffer[BUFSIZE];
	uint16_t nread,nwrite;


	fd1=initialize_virtual(tun1.c_str());
	if(!fd1)return -1;
	fd2=initialize_virtual(tun2.c_str());
	if(!fd2)return -2;

	max_fd=(fd1 > fd2)?fd1:fd2;
	while(1)
	{

		FD_ZERO(&rd_set);
		FD_SET(fd1,&rd_set);
		FD_SET(fd2,&rd_set);
		ret=select(max_fd+1,&rd_set,NULL,NULL,NULL);
		if(ret < 0 && errno==EINTR)
		{
			continue;
		}
		if(ret<0)
		{
			perror("Select()");
			exit(1);
		}

		if(FD_ISSET(fd1,&rd_set))
		{
			nread=cread(fd1,buffer,BUFSIZE);
			printf("Read " PRIu16 " bytes of packet data from %s.\n",nread,tun1.c_str());
		}
		if(FD_ISSET(fd2,&rd_set))
		{
			nwrite=cwrite(fd2,buffer,nread);
			printf("Write " PRIu16 " bytes of packet data to %s.\n",nwrite,tun2.c_str());
		}
	}
}
