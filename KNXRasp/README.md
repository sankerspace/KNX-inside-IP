The ipv6-to-KNX server connects to a 
	1) TUN Virtual Adapter Interface and on the otherside
	2) to a KNX eibd server
As a CLIENT it sends received packets from the TUN Interface over 
the KNX Bus. It is able to send ipv4 and ipv6 packets, 
it depends how the TUN Interfaces are configured.

As a SERVER it receives packets from the KNX Bus and 
forward it to the TUN Interface.



Preparation:
On every system(in out testcase a raspberry pi) which 
is connected to each other over a KNX Bus following things
must be installed:

A) A Virtual Ethernet Interface configured as a TUN Adapter
  The Name of that interface can be defined or the operating 
  system gives a random name.
  A Ipv6 adress has to be choosen, for example.:
	one adapter with 0:0:0:0:0:ffff:a00:1 (ipv6 version of 10.0.0.1)
	second adapter with 0:0:0:0:0:ffff:a00:2  (ipv6 version of 10.0.0.2)
 following commands can configure that:
(every command must be called with root permissions)
	$:ip -6 tuntap add dev tun1 mode tun user pi group pi   
        (tun1 is the name of the adapter)
	$:ip -6 link set tun1 up
	$:ip -6 add 0:0:0:0:0:ffff:a00:1 dev tun1
 (the same with the second adapter)


B)KNX eibd must be instaled and configured
