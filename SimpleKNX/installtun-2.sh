#!/bin/bash
sudo ip tuntap add dev tun61 mode tun user pi group pi multi_queue
sudo ip address add ::ffff:a00:2/96 dev tun61 #ipv6 version of 10.0.0.2
sudo ip link set tun61 up


sudo ip tuntap add dev tun66 mode tun user pi group pi multi_queue
sudo ip address add ::ffff:b10:2/112 dev tun66 
sudo ip link set tun66 up
