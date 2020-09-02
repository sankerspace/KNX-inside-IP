/*
 * virtualethernet.hpp
 *
 *  Created on: Sep 22, 2016
 *      Author: sankerspace
 */

#ifndef VIRTUALETHERNET_HPP_
#define VIRTUALETHERNET_HPP_

#define BUFSIZE 2000 /*every buffer should be allocated with this size*/
#define CLIENT 0
#define SERVER 1

#define TUN_LOCATION "/dev/net/tun"
#define FLAGS IFF_TUN

#define DEBUG 1

/*prototype functions*/
int initialize_virtual(const char* tun_name);
int cread(int fd, char *buf, int n);
int cwrite(int fd, char *buf, int n);
#endif /* VIRTUALETHERNET_HPP_ */
