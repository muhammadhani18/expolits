import os
from time import sleep
import psutil
import threading
from datetime import datetime



def get_CPU_Load(currentTime):

    while(1):
             
        load1, load5,load15 = psutil.getloadavg()
        cpu_usage15 = (load15/os.cpu_count()) * 100
        cpu_usage1 = (load1/os.cpu_count()) * 100
        cpu_usage5 = (load5/os.cpu_count()) * 100


        print("The CPU usage over 1 min is : ", cpu_usage1)
        
        file = open(f"cpu_usage.txt", "a")
        file.write(f" {cpu_usage1} \n")
        file.close()
        sleep(60)
        #print("The CPU usage over 5 min is : ", cpu_usage5)
        #print("The CPU usage over 15 min is : ", cpu_usage15)


def get_bandwidth(currentTime):
    
    while(1):
        # Get net in/out
        net1_out = psutil.net_io_counters().bytes_sent
        net1_in = psutil.net_io_counters().bytes_recv

        sleep(59) # 4 sec

        # Get new net in/out
        net2_out = psutil.net_io_counters().bytes_sent
        net2_in = psutil.net_io_counters().bytes_recv

        # Compare and get current speed
        if net1_in > net2_in:
            current_in = 0
        else:
            current_in = net2_in - net1_in

        if net1_out > net2_out:
            current_out = 0
        else:
            current_out = net2_out - net1_out

        #network = {"traffic_in" : current_in, "traffic_out" : current_out}
        print(f"Traffic in: {current_in} bytes\sec")
        print(f"Traffic Out: {current_out} bytes\sec")
        
        file = open(f"bandwidth.txt", "a")
        file.write(f"{current_in},{current_out}\n")
        file.close()
        sleep(1)
        #return network 


if __name__ == "__main__":
    
    now = datetime.now()

    current_time = now.strftime("%H:%M:%S")
 
    
    t1 = threading.Thread(target=get_bandwidth, args=(current_time, ))
    t2 = threading.Thread(target=get_CPU_Load, args=(current_time, ))
        
    t1.start()
    t2.start()
 