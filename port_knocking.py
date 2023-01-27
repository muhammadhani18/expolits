# ################################################################################################ 
#  So this sript will work by first getting a list of connected ports by the scan() function     #
#  then as we have gotten a list of connected ports, what we have to do is that we have to       #
#  comment out the scan() function and line 38,45,49. Then we have to uncomment the              #
#  line 37,44,47 and 57. Once try_port(int(sys.argv[1])) line is uncommented this means that     #
#  we have to pass the port numbers as arguments from the terminal from the list we got from     #
#  the scan() function one by one and then analyze the results                                   #
# ################################################################################################


from ftplib import FTP

import threading
# to multi thread the scan operation because it takes too long

import socket
# to make requests with web server

import sys 
# to take arguments from the command line

import itertools
# to try permutations and combinations of brute force 

def try_port(port):
    
    # making a socket to connect to the web server 
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #now creating a timeout if the port takes 0.1 seconds long to respond
    s.settimeout(0.1) 
    #now connecting to the srver IP Address through the respective port number 
    
    try:    
        s.send(b'a\n')
        s.connect(('192.168.0.104', port))
    except socket.error:
        #print("Port is closed")
        return False
    
    #now recieving data from server which will be 1024 bytes of data 
    
    try:    
        data = s.recv(1024)
        #print("Port is open. Recieved: ", data)
        return True
    except socket.timeout:
        #print("Port is opened but timed out")
        data = "" #assigning an empty string to data to avoid unbound object error 
        return True
    
    #closing the connection
    s.close()

    return data


# try_port(int(sys.argv[1]))

# now we will make a scan function because we wanna
# scan all 64000 ports by brute forcing

def scan():
    
    # making an empty list so that we can append all open ports
    # and we can see all open ports 
    found_ports = []
    for port in range(20,30):
        connected = try_port(port)
        if not connected:
            found_ports.append(port)
        
    return found_ports

print(scan())

t = scan()

def connectFTP():
    port_no = 21
    if port_no in t:
        host = "127.0.0.1" 
            # the host to which we will connect to. It may be something else
        user = "videoftptut"
            # the user which will connect to the host
        password = "Deviljin1"


        with FTP(host) as ftp: # this line means that the connection will 
                                    #automatically be closed
            ftp. login( user= user , passwd = password) 
                # the user will login with the username and password
            print(ftp.getwelcome())




# now the below loop will iterate in the permutations of 3 on the given range
# but these permutations will take a very long time

# for possible in itertools.permutations(range(1,65535),3):
#     print(possible) 


# t = threading.Thread(target=scan, args=0)
# t.start()
# t.join()








  