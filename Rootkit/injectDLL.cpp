#include <Windows.h>
#include <iostream>
#include <string>


typedef HANDLE(WINAPI* CREATEFILEW)(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
);

CREATEFILEW OriginalCreateFileW = NULL;

HANDLE WINAPI MyCreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
)
{
    std::wcout << "CreateFileW: " << lpFileName << std::endl;
    return OriginalCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call) //entry point for dll files when the system terminates or loads new process or thread
    {
    case DLL_PROCESS_ATTACH: //dll loaded to the virtual address space
        OriginalCreateFileW = (CREATEFILEW)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "CreateFileW");
        if (OriginalCreateFileW)
        {
            // Replace the original CreateFileW with our custom function
            FARPROC pMyCreateFileW = &MyCreateFileW;
            DWORD oldProtect;
            VirtualProtect(OriginalCreateFileW, sizeof(pMyCreateFileW), PAGE_EXECUTE_READWRITE, &oldProtect);
            memcpy(OriginalCreateFileW, &pMyCreateFileW, sizeof(pMyCreateFileW));
            VirtualProtect(OriginalCreateFileW, sizeof(pMyCreateFileW), oldProtect, &oldProtect);
        }
        break;
    case DLL_PROCESS_DETACH: //could not load the dll into virtual space
        break;
    }
    return true;
}
