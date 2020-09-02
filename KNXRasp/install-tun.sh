#!/bin/bash
sudo ip tuntap add dev tun60 mode tun user sankerspace group sankerspace
sudo ip address add ::ffff:a00:1/96 dev tun60
sudo ip link set tun60 up

sudo ip tuntap add dev tun61 mode tun user sankerspace group sankerspace
sudo ip address add ::ffff:a00:2/96 dev tun61
sudo ip link set tun61 up

sudo route add default gw ::ffff:a00:1 tun60
