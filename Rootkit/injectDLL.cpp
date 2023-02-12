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
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
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
    case DLL_PROCESS_DETACH:
        break;
    }
    return true;
}
