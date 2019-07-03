ip route add 192.168.43.0/24 dev ap0 table local_network proto static scope link
ip route add 192.168.43.0/24 dev ap0 table local proto static scope link
iptables -t nat -F
iptables -F
iptables -A OUTPUT -o lo -j ACCEPT
iptables -t nat -A POSTROUTING -o ppp0 -s 192.168.43.0/24 -j MASQUERADE
echo 1 > /proc/sys/net/ipv4/ip_forward
ip rule add from all lookup main

