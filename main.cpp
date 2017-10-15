/*
Author: Tomasz Odrzywolek
Simple file delete program based on MS interfaces
 */
#include <stdio.h>
#include <windows.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <tchar.h>
#include <fstream>
#include <iostream>

BOOL set_path(TCHAR* path);
HANDLE find_files(const TCHAR* path, WIN32_FIND_DATA* ffd);
int delete_files(const TCHAR* path_to_folder, HANDLE* handle, WIN32_FIND_DATA* ffd);
bool allow_work(const TCHAR* folder_path, int limit);

int main ()
{
    // empty path
    TCHAR path[MAX_PATH];

    HANDLE hfind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;


    // set path to Program Data and check if succeeded
    if ( set_path(path) )
    {
        puts( "Sciezka ustalona!" );
        // add path to FluidDesk folder
        PathAppend(path, TEXT("Fluid Desk Sp. z o.o"));
        // handle to files
        if (allow_work(path, 3) )
        {
            hfind = find_files(path, &ffd);
            // check if files are found
            if (hfind != INVALID_HANDLE_VALUE)
            {
                delete_files(path, &hfind, &ffd);
            }
            else
                puts("No inis in folder!");

            FindClose(hfind);
        }
    else
        puts( "Path cannot be set" );

    }
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



int delete_files(const TCHAR* path_to_folder, HANDLE* handle, WIN32_FIND_DATA* ffd)
{
    TCHAR file_path[MAX_PATH];
    DWORD dwerror;

    do
    {
        printf(TEXT("  %s <file>\n"), ffd->cFileName);
        _tcscpy(file_path, path_to_folder);
        PathAppend(file_path, ffd->cFileName);
        puts(file_path);
        if (DeleteFile(file_path))
            puts("File deleted");
        else
            puts("File not found");
    }
    while (FindNextFile(*handle, ffd) != 0);

    dwerror = GetLastError();
    if (dwerror != ERROR_NO_MORE_FILES)
    {
        puts("Error");
    }
    return dwerror;

}


HANDLE find_files(const TCHAR* path, WIN32_FIND_DATA* ffd)
{

    TCHAR search_path[MAX_PATH];

    // copy path string
    _tcscpy(search_path, path);
    // set search_path string to value that needs to be searched
    PathAppend(search_path, TEXT("*.ini"));
    // find all ini files in folder
    HANDLE hfind = FindFirstFile(search_path, ffd);

    if (INVALID_HANDLE_VALUE == hfind){
        puts("INVALID_HANDLE_VALUE");
    }
    return hfind;
}

bool allow_work(const TCHAR* folder_path, int limit)
{
    TCHAR file_path[MAX_PATH];
    _tcscpy(file_path, folder_path);
    PathAppend(file_path, TEXT("cred"));

    std::fstream file;
    file.open(file_path, std::ios::out | std::ios::in);
    if (file.good())
    {
        puts("YES");
        file >> limit;
        if (limit <=0 or limit > 7)
        {
            file.close();
            return false;
        }
        file.seekg(0);
        file << limit-1;
        std::cout << limit << std::endl;
    }
    else
    {
        file.open(file_path, std::ios::out);
        puts("NO!");
        file << limit;
    }
    file.close();
    return true;
}
