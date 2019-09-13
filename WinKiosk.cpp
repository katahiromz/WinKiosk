#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <strsafe.h>

BOOL DoExecute(HWND hwnd, LPCWSTR pszCmd, INT nCmdShow)
{
    WCHAR szText[256];
    StringCbCopyW(szText, sizeof(szText), pszCmd);

    WCHAR szPath[MAX_PATH];
    GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath));
    *PathFindFileName(szPath) = 0;

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.wShowWindow = nCmdShow;
    si.dwFlags = STARTF_USESHOWWINDOW;

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    HANDLE hProcess;
    BOOL ret = CreateProcessW(NULL, szText, NULL, NULL, TRUE, 0, NULL, szPath, &si, &pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return ret;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    if (DoExecute(NULL, L"SimpleBrowser.exe --kiosk", SW_SHOWNORMAL))
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}
