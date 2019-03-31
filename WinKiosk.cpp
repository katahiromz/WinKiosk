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

BOOL CreateShortcut(
    LPCWSTR pszLnkFileName, 
    LPCWSTR pszTargetPathName, 
    LPCWSTR pszDescription)
{
    IPersistFile*   ppf;
    IShellLink* psl;
    HRESULT hres;

    hres = CoInitialize(NULL);
    if(SUCCEEDED(hres))
    {
        hres = CoCreateInstance(CLSID_ShellLink, NULL, 
            CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
        if(SUCCEEDED(hres))
        {
            psl->SetPath(pszTargetPathName);
            if (pszDescription != NULL)
                psl->SetDescription(pszDescription);

            hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
            if(SUCCEEDED(hres))
            {
                hres = ppf->Save(pszLnkFileName, TRUE);
                ppf->Release();
            }
            psl->Release();
        }
        CoUninitialize();
    }
    SetLastError(hres);

    return SUCCEEDED(hres);
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    int argc;
    LPWSTR *wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argc >= 2)
    {
        WCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);

        LPITEMIDLIST pidl = NULL;
        SHGetSpecialFolderLocation(NULL, CSIDL_STARTUP, &pidl);

        WCHAR szLnkFile[MAX_PATH] = L"";
        SHGetPathFromIDList(pidl, szLnkFile);
        PathAppend(szLnkFile, L"WinKiosk.lnk");

        if (lstrcmpiW(wargv[1], L"--install") == 0)
        {
            if (!CreateShortcut(szLnkFile, szPath, L"WinKiosk"))
            {
                MessageBoxA(NULL, "CreateShortcut failed.", NULL, MB_ICONERROR);
            }
        }
        else if (lstrcmpiW(wargv[1], L"--uninstall") == 0)
        {
            DeleteFile(szLnkFile);
        }
    }
    else
    {
        DoExecute(NULL, L"SimpleBrowser.exe --kiosk", SW_SHOWNORMAL);
    }
    LocalFree(wargv);
    return 0;
}
