
from ftplib import FTP
# to interact with ftp sockets

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
    
    # now we will download a file from our server 
    
    with open('download.txt', 'wb') as f:
        ftp.retrbinary("RETR " + "upload.txt", f.write, 1024)  
        # for the above function we need a command 'RETR' means retrieve the file from the server 
        # plus the file name on the server
        # and a callback 
    
    
    # now we will upload a file to the server
    with open('upload.txt', 'rb') as f:
        ftp.storbinary("STOR " + "upload.txt", f) 
        
    # now downloading a file which is in another directory
    # it is not good to do a relative path so we user .cwd() function
    # to navigate through the directories
    # it is important to know the name of directories of the ftp server
   
    ftp.cwd("mydir") #can be any name 
    with open('myspecialfile.txt','wb') as f:
        ftp.retrbinary('RETR ' + 'otherfile.txt', f.write,1024)
                           
    ftp.quit()



        