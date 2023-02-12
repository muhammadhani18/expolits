# Rootkit (Learning purposes)

The rootkit made is made by me when i was learning about exploit development and other red-team hacking techniques.

This rootkits involves several calls of Windows.h api and is designed for windows. 

First compile `injectDLL.cpp`. You will notice an .exe file created. 

The program ***RootkitStart.cpp** * creates a process in the operating system and runs ***injectDLL.exe** *which intercept the `CreateFile` system call and log its parameters.

**NOTE:**   Intercepting system calls in Windows requires low-level programming, and can be a complex task. One way to intercept system calls is to create a custom dynamic link library (DLL) that acts as a wrapper for the desired system calls, and then inject the DLL into the process you want to monitor.

More additions will come in this expolit throughout my learning journey. 

Happy Hacking !!! :)
