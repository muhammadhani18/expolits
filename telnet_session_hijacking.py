from scapy.all import *

layer3 = IP(src='' , dst='' )
layer4 = TCP(sport= '', dport= '', flags='', ack= '', seq='' )
data = ''

Packet = layer3/layer4/data

send(Packet, verbose=0)
