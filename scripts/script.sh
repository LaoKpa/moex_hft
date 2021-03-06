#!/bin/bash

info=$(/sbin/ifconfig)
start=${info#*ppp0}
start=${start#*addr:}
moex_address=${start%% *}
echo "MOEX address = $moex_address"
route add -net 1.1.1.0 netmask 255.255.255.0 gateway         $moex_address
route add -net 239.192.0.0 netmask 255.255.0.0 gateway       $moex_address
route add -net 10.50.129.200 netmask 255.255.255.255 gateway $moex_address
route add -net 10.50.129.90 netmask 255.255.255.255 gateway  $moex_address
route add -net 1.1.7.200 netmask 255.255.255.255 gateway     $moex_address

