

#include "simpleKNXtransfer.h"


uint8_t buf_[KNX_MTU+4]	= 	{ 0, 0x80,0,0 };
//uint8_t buf_cnt[3]		= 	{ 0, 0x80, 0 };



void
printHex2 (int len, uchar * data){
	int j;
	printf("HexData:\n");
	
  	for (j = 0; j < len; j++){
    	printf ("%02X ", data[j]);
		if((j%10)==0) printf("\n");
	}
	printf("\n");
}




int send(uint8_t *buf,int size,EIBConnection *con)
{	
	int len=0,ret=0,i=0,j=4,bufsize=KNX_MTU+4,cnt=0,last=0;
	//double temp=0;
	int temp=size;
	//send number of following packets
	while(temp)
	{
		if(temp>KNX_MTU){
			cnt++;
			temp-=KNX_MTU;
		}else if(temp<=KNX_MTU){
			cnt++;
			last=temp;
			temp=0;	
		}
	}
/*
	temp=(double)size;	
	temp=temp/((double)KNX_MTU);
	cnt=size/KNX_MTU;
	if(temp>cnt){
		cnt++;
		
	}
*/	
	//printf("temp:%f ; cnt:%d\n",temp,cnt);
	if(DO_DEBUG)printf("Packets to send:%d\n",cnt);
	
	while(cnt>0){
		buf_[2]=cnt;
		if(cnt==1){
			buf_[3]=last;
			len+=last;
		}else{
			buf_[3]=KNX_MTU;
			len+=KNX_MTU;	
		}
		while(j<bufsize){
			if(i<size){
				buf_[j]=buf[i];
				i++;
			}else{
				buf_[j]=0;
			}
			j++;	
		}//while
		j=4;//2 bytes are KNX reserved + 1 byte for the number of packets
		ret=EIBSendAPDU (con, bufsize, buf_);

		if(DO_DEBUG)printf("Send %d. packet with %d bytes of data\n",cnt,buf_[3]);
		if(DO_DEBUG && DO_DETAILED) printHex2 ((ret-4), (buf_+4));
		cnt--;
	}//while

	return len;
}



int recv(uint8_t *buf,int size,EIBConnection *con,eibaddr_t *src)
{		
	int len=0,ret=0,i=0,j=4,bufsize=KNX_MTU+4;
	int cnt=-1;
	
	
	while(cnt != 0)
	{
		ret=EIBGetAPDU_Src (con, bufsize, buf_, src);
		//ret=ret-4;
		len = len + buf_[3];
		cnt=buf_[2];
		if(DO_DEBUG)printf("Received %d. packet with %d bytes of data\n",cnt,buf_[3]);
		if(DO_DEBUG && DO_DETAILED) printHex2 ((ret-4), (buf_+4));	
		//the buffer that is used to store incoming data should be greater than 
		//the amount of data that is expected
		if(size<len){
		    perror("[recv]:temporary buffer to small");
		    return -2;
		}
		
		while(j<bufsize)
		{
			if(i<size){
				buf[i]=buf_[j];
				j++;
				i++;
			}else{
				break;
			}
		}//while
		j=4;
		cnt--;
		//if((cnt-1)==0)break;
	}//while
	return len;
}



/*
*sendKNX(): 
*	Data are written to socket at url, only packets are 
*	send to eibaddr
*	example:readKNX(buf,255,"local:/var/run/knx","1/1/141")
*/
int sendKNX(uint8_t *buf,int size,char* url,char* eibaddr)
{
	int len=0;
	EIBConnection *con;
  	eibaddr_t dest;
	//uint8_t buf_[STDBUFFERSIZE] = { 0, 0x80 };	//1500 bytes:maximum mtu of ip packets 
	//check parameter
	if(buf ==NULL || url == NULL || eibaddr == NULL || size<=0 || size>STDBUFFERSIZE) 
	{	
		perror("[sendKNX]:wrong parameters");
		return -1;
	}
	

	con = EIBSocketURL (url);
	if (!con)
	{
    	perror ("[sendKNX]:Open failed");
		return -2;
	}

	dest = readgaddr (eibaddr);
	if (EIBOpenT_Group (con, dest, 1) == -1)
	{
    	perror ("[sendKNX]:Connect failed");
		return -2;
	}
	

	//send data over KNX Bus
	len =  send(buf,size,con);
	//EIBSendAPDU (con, size+2, buf_);
	
	if(DO_DEBUG)printf("Totally Send %d bytes of data\n",len);
    if (len < 0)
	{
    	perror ("[sendKNX]:Request failed");
		return -3;
	}
	if(DO_DEBUG)
	{
    	printf ("[sendKNX]:Send request\n");
	}

  	EIBClose (con);
  	return len;
}





/*
*readKNX(): 
*	Data are read from socket at url, only packets are 
*	accepted written from eibaddr
*	example:readKNX(buf,255,"local:/var/run/knx","1/1/141")
*/
int readKNX(uint8_t *buf,int size,char* url,char* eibaddr)
{
	int len=0;
	EIBConnection *con;
  	eibaddr_t dest;
  	eibaddr_t src;
  	//uint8_t buf_[STDBUFFERSIZE];
	//check parmeter
	if(buf ==NULL || url == NULL || eibaddr == NULL || size<=0) 
	{	
		perror("[readKNX]:wrong parameters");
		return -1;
	}
	//set up connection to the KNX Bus
	con = EIBSocketURL (url);
	if (!con)
	{
    	perror ("[readKNX]:Open failed");
		return -2;
	}
	dest = readgaddr (eibaddr);
	if (EIBOpenT_Group (con, dest, 0) == -1)
	{
    	perror ("[readKNX]:Connect failed");
		return -2;
	}

	//read data from KNX Bus
	len =recv(buf,size,con,&src);
	//len = EIBGetAPDU_Src (con, STDBUFFERSIZE, buf_, &src);
	if(DO_DEBUG)printf("Totally Received %d bytes of data\n",len);
	
	
    if (len < 2) 
	{
		if (len < 0){
			perror("[readKNX]:Read failed");
		}else{
			perror("[readKNX]:Invalid Packet");
		}
		return -3;
	}
	/*
	if (buf_[0] & 0x3 || (buf_[1] & 0xC0) == 0xC0)
	{
	  	perror ("[readKNX]:Unknown APDU");
	  	if (DO_DEBUG>0) {printf(" from ");printIndividual (src);printf("\n");}
		if(DO_DETAILED)
		{
			printHex2(len,buf_);	
		}
	  	return -3;
	}
      else
	{
		if(DO_DEBUG>0){
	  		switch (buf_[1] & 0xC0)
	    		{
	    			case 0x00:
	      				printf ("Read from ");
	      				break;
	    			case 0x40:
	      				printf ("Response from ");
	      				break;
	    			case 0x80:
	      				printf ("Write from ");
	      				break;
	  			}
	  		printIndividual (src);
			if(DO_DETAILED){
				
				if (buf_[1] & 0xC0)
	    		{
	      			printf (": \n");
	      			if (len == 2)
						printf ("%02X", buf_[1] & 0x3F);
	      			else{
						printf("[readKNX]:KNX data:\n");
						printHex2(2,buf_);
						printHex2 (len - 2, buf_ + 2);
					}		
	    		}
			}
			printf("\n");
			fflush (stdout);
		}//do_debug
	}//else */
	
	//received data is copied to the input buffer 
	/*for(i=0;i<(len-2);i++)
	{
		buf[i]=buf_[i+2];
	}	
	*/
	EIBClose (con);
  	return len;
}


