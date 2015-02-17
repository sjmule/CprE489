Scott Mueller

We learned how to use a few basic network tools built into Linux 

ping exercises

1) ping www.iastate.edu avg: 0.744ms
--- www.iastate.edu ping statistics ---
12 packets transmitted, 12 received, 0% packet loss, time 11358ms
rtt min/avg/max/mdev = 0.638/0.744/0.819/0.072 ms

ping www.cam.ac.uk avg: 146.648ms
--- www.cam.ac.uk ping statistics ---
12 packets transmitted, 12 received, 0% packet loss, time 11443ms
rtt min/avg/max/mdev = 146.282/146.648/146.913/0.358 ms

ping www.lenovo.com.cn avg: 221.265ms
--- savelenovo.dtwscache.glb0.lxdns.com ping statistics ---
13 packets transmitted, 13 received, 0% packet loss, time 12686ms
rtt min/avg/max/mdev = 212.187/221.265/230.904/5.803 ms

2) The results look like the ping results from pinging a website. The ping sent 56 bytes of data and received 64 bytes back but the average time for the response was only 0.021ms

hping2 exercise
--- www.lenovo.com.cn hping statistic ---
3 packets transmitted, 3 packets received, 0% packet loss
round-trip min/avg/max = 208.9/209.8/210.4 ms

This command lists different things than the regular ping command. The 3rd part is the same, minus the mdev time listed. The port is listed, flags are listed, and something called "win" is listed.

nslookup exercises
3) nslookup www.microsoft.com
canonical name = toggle.www.ms.akadns.net
canonical name = www.microsoft.com.edgekey.net
canonical name = e10088.dscb.akamaiedge.net

nslookup g.www.ms.akadns.net
canonical name = lb1.www.ms.akadns.net

4) nslookup
>set type=MX
>ece.iastate.edu
ece.iastate.edu mail exchanger = 10 vulcan.ece.iastate.edu

5) nslookup 129.186.215.40
name = spock.ee.iastate.edu

host exercises
6) host www.engineering.iastate.edu
www.engineering.iastate.edu has address 129.186.239.13

host wwww.google.com
www.google.com has address 216.58.216.100
www.google.com has IPv6 address 2607:f8b0:4009:80b::2004

7)Neither of the machines have an alias

ifconfig exercises
8) inet addr:192.168.254.6

iperf exercises
9) The bandwidth between these two hosts is 933 Mbits/sec. The connection between the two hosts is most likely 1Gbps.

traceroute exercises
10) The route contained 8 hops, it routed through 5 gateways within the domain iastate.edu before reaching a gateway outside of the university network. While in the university network, it took just under 1ms to reach each gateway, after it left the university network it took about 16.5ms to reach each gateway. This website is easily reachable.

11)traceroute to www.mit.edu (23.194.46.93), 30 hops max, 60 byte packets
 1  192.168.254.254  0.112 ms  0.134 ms  0.122 ms
 2  129.186.5.252  0.950 ms  1.042 ms  1.625 ms
 3  129.186.254.131  1.156 ms  1.155 ms  1.264 ms
 4  192.245.179.54  0.848 ms  0.677 ms  0.719 ms
 5  198.49.182.173  3.773 ms  3.779 ms  3.771 ms
 6  198.49.182.13  4.685 ms  4.606 ms  4.588 ms
 7  62.115.50.53  12.925 ms  12.869 ms  12.892 ms
 8  62.115.141.173  13.379 ms  13.433 ms  13.452 ms
 9  195.12.254.218  12.998 ms  12.966 ms 213.248.85.30  12.953 ms
10  205.171.93.45  12.937 ms  12.971 ms  12.934 ms
11  23.194.46.93  12.994 ms  13.070 ms  13.062 ms


12) The route contained 22 hops with 4 being unreachable, it again routed through 5 gateways within the domain iastate.edu before reating a gateway outside the university. It took about 0.9ms to reach each of the iastate.edu gateways, then much longer eventually increasing to a time of 194.5ms. This website is more difficult to reach.

traceroute to www.newcastle.edu.au (134.148.4.137), 30 hops max, 60 byte packets
 1  192.168.254.254  0.162 ms  0.180 ms  0.155 ms
 2  129.186.5.252  0.959 ms  1.008 ms  1.139 ms
 3  129.186.254.131  0.973 ms  1.021 ms  1.075 ms
 4  192.245.179.54  0.687 ms  0.867 ms  0.700 ms
 5  192.245.179.163  0.674 ms  0.612 ms  0.734 ms
 6  164.113.255.17  5.027 ms  4.938 ms  4.917 ms
 7  164.113.255.254  4.911 ms  5.065 ms  5.100 ms
 8  198.71.45.19  25.134 ms  25.090 ms  25.093 ms
 9  198.71.45.25  41.146 ms  41.123 ms  41.116 ms
10  207.231.240.4  41.108 ms  41.112 ms  41.008 ms
11  202.158.194.109  93.058 ms  93.135 ms  93.102 ms
12  113.197.15.98  187.113 ms  187.056 ms  186.655 ms
13  113.197.15.18  186.603 ms  186.695 ms  186.643 ms
14  182.255.121.50  190.278 ms  190.063 ms  190.055 ms
15  * * *
16  134.148.154.251  190.830 ms  191.137 ms  190.057 ms
17  134.148.154.1  190.021 ms  190.103 ms  190.083 ms
18  * * *
19  * * *
20  * * *
21  134.148.4.252  193.475 ms  193.472 ms  194.174 ms
22  134.148.4.137  195.100 ms  194.689 ms  194.966 ms


tcptraceroute exercises
13) The route again contained 22 hops with 4 being unreachable. It took the same route as traceroute did and took about the same amount of time to reach its destination.

Netcat exercises
14) port 22 on spock.ee.iastate.edu is open

15) +OK <45e429186863d2640aa48c7f9135b5fb@spock.ee.iastate.edu>

route exercises
16) 










