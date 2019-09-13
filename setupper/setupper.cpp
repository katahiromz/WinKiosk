#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <strsafe.h>

BOOL GetStartupFolder(HWND hwnd, LPWSTR pszPath)
{
    return SHGetSpecialFolderPathW(hwnd, pszPath, CSIDL_STARTUP, FALSE);
}

LPWSTR LoadStringDx(UINT id)
{
    static WCHAR s_sz[512];
    LoadStringW(NULL, id, s_sz, 512);
    return s_sz;
}

LPWSTR LoadStringDx2(UINT id)
{
    static WCHAR s_sz[512];
    LoadStringW(NULL, id, s_sz, 512);
    return s_sz;
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

    return SUCCEEDED(hres);
}

BOOL DoInstall(HWND hwnd)
{
    WCHAR szModule[MAX_PATH];
    GetModuleFileNameW(NULL, szModule, MAX_PATH);
    PathRemoveFileSpec(szModule);
    PathAppendW(szModule, L"WinKiosk.exe");

    WCHAR szPath[MAX_PATH];
    if (GetStartupFolder(hwnd, szPath))
    {
        PathAppendW(szPath, L"WinKiosk.lnk");
        if (CreateShortcut(szPath, szModule, L"WinKiosk"))
        {
            MessageBoxW(hwnd, LoadStringDx(1), LoadStringDx2(3),
                        MB_ICONINFORMATION);
            return TRUE;
        }
    }

    MessageBoxW(hwnd, LoadStringDx(5), NULL, MB_ICONERROR);
    return FALSE;
}

BOOL DoUninstall(HWND hwnd)
{
    WCHAR szPath[MAX_PATH];
    if (GetStartupFolder(hwnd, szPath))
    {
        PathAppendW(szPath, L"WinKiosk.lnk");
        if (DeleteFileW(szPath))
        {
            MessageBoxW(hwnd, LoadStringDx(2), LoadStringDx2(3), MB_ICONINFORMATION);
            return TRUE;
        }
    }

    MessageBoxW(hwnd, LoadStringDx(6), NULL, MB_ICONERROR);
    return FALSE;
}

BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    CheckRadioButton(hwnd, rad1, rad2, rad1);
    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
    case IDOK:
        if (IsDlgButtonChecked(hwnd, rad1) == BST_CHECKED)
        {
            DoInstall(hwnd);
        }
        else
        {
            DoUninstall(hwnd);
        }
        EndDialog(hwnd, id);
        break;
    case IDCANCEL:
        EndDialog(hwnd, id);
        break;
    }
}

INT_PTR CALLBACK
DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        HANDLE_MSG(hwnd, WM_INITDIALOG, OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    }
    return 0;
}

INT WINAPI
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpCmdLine,
        INT         nCmdShow)
{
    if (*lpCmdLine)
    {
        if (lstrcmpiA(lpCmdLine, "--install") == 0)
        {
            DoInstall(NULL);
        }
        else if (lstrcmpiA(lpCmdLine, "--uninstall") == 0)
        {
            DoUninstall(NULL);
        }
    }
    else
    {
        DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    }
    return 0;
}
