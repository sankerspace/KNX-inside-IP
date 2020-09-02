/*
 * Test_TUN.hpp
 *
 *  Created on: Sep 23, 2016
 *      Author: sankerspace
 */

#ifndef TEST_TUN_HPP_
#define TEST_TUN_HPP_

#define TESTTUNNAME_SERVER tun1
#define TESTTUNNAME_CLIENT tun2


#include <string>
#include "virtualethernet.hpp"

using namespace std;

/**
 * testserver: tests virtualethernet
 */
int testserver(string tun1,string tun2 );



#endif /* TEST_TUN_HPP_ */
