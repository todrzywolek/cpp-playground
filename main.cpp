/* remove example: remove myfile.txt */
#include <stdio.h>
#include <windows.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <tchar.h>

HANDLE find_files(TCHAR* szDir, WIN32_FIND_DATA* ffd);
int delete_files(TCHAR* szDir);

int main ()
{
    TCHAR szPath[MAX_PATH];

    if(SUCCEEDED(SHGetFolderPath(NULL,
                             CSIDL_COMMON_APPDATA,
                             NULL,
                             0,
                             szPath)))
    {
        puts( "Udalo sie!" );
        PathAppend(szPath, TEXT("FluidDesk"));

        delete_inis(szPath);

    }
    else
        puts( "Error" );
/*


        if( remove(szPath ) != 0 )
            perror( "Error deleting file" );
        else
            puts( "File successfully deleted" );



        PathAppend(szPath, TEXT("New Doc.txt"));
        HANDLE hFile = CreateFile(szPath, ...);

    HRESULT result = SHGetFolderPathA(FOLDERID_ProgramData,
                                   0,
                                   NULL,
                                   program_data);



*/
    // free memory in program_data
  return 0;
}

int delete_files(TCHAR* szDir)
{
    HANDLE hfind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;

    hfind = find_inis(szDir, &ffd);

    TCHAR szPath[MAX_PATH];

    do
    {
        printf(TEXT("  %s <file>\n"), ffd.cFileName);
        _tcscpy(szPath, szDir);
        PathAppend(szPath, ffd.cFileName);
        puts(szPath);
        if (DeleteFile(szPath))
            puts("File deleted");
        else
            puts("Error");
    }
    while (FindNextFile(hfind, &ffd) != 0);


    DWORD dwerror = GetLastError();
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
        puts("Error");
    }
    return hfind;
}




