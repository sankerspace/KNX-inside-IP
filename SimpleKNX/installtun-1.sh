#!/bin/bash
sudo ip tuntap add dev tun1 mode tun user pi group pi multi_queue
sudo ip address add ::ffff:172.128.0.1/112 dev tun1 #ipv6 version of 10.0.0.2
sudo ip addr add 172.128.0.1/24 dev tun1
sudo ip link set tun1 up
