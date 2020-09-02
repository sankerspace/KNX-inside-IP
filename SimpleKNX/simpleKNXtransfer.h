
#ifndef _SIMPLEKNXTRANSFER_
#define _SIMPLEKNXTRANSFER_


/*	STBUFFERSIZE:	
*	for every buffer size it must be reconsidered that the first 
*	2 bytes are reserved for KNX transmission
*	for IP packets size must be greater thet their MTU	(MTU + 2 bytes)
*/
#define STDBUFFERSIZE 1550
//#define KNX_MTU 234 //only MTU bytes can be transferred over KNX BUS due to some unknown restrictions
#define KNX_MTU 50
#define DO_DEBUG 1
#define DO_DETAILED 1

#include "common.h"




void printHex2 (int len, uchar * data);
int sendKNX(uint8_t *buf,int size,char* url,char* eibaddr);
int readKNX(uint8_t *buf,int size,char* url,char* eibaddr);


#endif
