/* remove example: remove myfile.txt */
#include <stdio.h>
#include <windows.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <tchar.h>
#include <iostream>

BOOL set_path(TCHAR* path);
HANDLE find_files(TCHAR* szDir, WIN32_FIND_DATA* ffd);
int delete_files(TCHAR* szDir);

int main ()
{
    // empty path
    TCHAR path[MAX_PATH];
    // set path to Program Data and check if succeeded
    if ( set_path(path) )
    {
        puts( "Sciezka ustalona!" );
        // add path to FluidDesk folder
        PathAppend(path, TEXT("FluidDesk"));





        int result = delete_files(szPath);
        std::cout << "Error= " << result;
    }
    else
        puts( "Path not found" );

  return 0;
}

BOOL set_path(TCHAR* path)
{
    return SUCCEEDED(SHGetFolderPath(NULL,
                                 CSIDL_COMMON_APPDATA,
                                 NULL,
                                 0,
                                 path));
}



int delete_files(TCHAR* szDir)
{
    HANDLE hfind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    DWORD dwerror;

    hfind = find_files(szDir, &ffd);

    TCHAR szPath[MAX_PATH];

    while (FindNextFile(hfind, &ffd) != 0 and GetLastError() != ERROR_PATH_NOT_FOUND);
    {
        printf(TEXT("  %s <file>\n"), ffd.cFileName);
        _tcscpy(szPath, szDir);
        PathAppend(szPath, ffd.cFileName);
        puts(szPath);
        if (DeleteFile(szPath))
            puts("File deleted");
        else
            puts("File not found");
    }

    dwerror = GetLastError();
    if (dwerror != ERROR_NO_MORE_FILES)
    {
        puts("Error");
    }

    FindClose(hfind);
    return dwerror;

}


HANDLE find_files(TCHAR* szDir, WIN32_FIND_DATA* ffd)
{
    TCHAR szPath[MAX_PATH];
    _tcscpy(szPath, szDir);
    PathAppend(szPath, TEXT("*.ini"));
    HANDLE hfind = FindFirstFile(szPath, ffd);
    puts(szPath);

    if (INVALID_HANDLE_VALUE == hfind){
        puts("BBBBBB");
    }
    return hfind;
}




