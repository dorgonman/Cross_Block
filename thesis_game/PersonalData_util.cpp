
#include "PersonalData.h"

#include <shlwapi.h> 
#pragma comment(lib, "shlwapi.lib")
vector<string> PersonalData::getAllFile(char* folderPath, char* fileType){
	char targetPath[MAX_PATH];
	char filePath[MAX_PATH];
	HANDLE hFind;
	WIN32_FIND_DATAA findFileData;


	vector<string> files;

	// 設定檔案搜尋字串

	sprintf(targetPath, "%s%s", folderPath, fileType);

	// 開始搜尋檔案

	if( (hFind = FindFirstFileA(targetPath, &findFileData)) != INVALID_HANDLE_VALUE) {

		do{ // 每找到一個符合的檔案就會進入迴圈，直到找不到符合的檔案
			if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){ // 表示並非目錄
				// 將檔案的相對路經存入 FilePath 字串之中
				sprintf(filePath, "%s%s", folderPath, findFileData.cFileName);
				files.push_back(filePath);
			}

		}while(FindNextFileA(hFind, &findFileData)); // 尋找下一個檔案

	FindClose(hFind);
	}

	return files;
}

void PersonalData::currentDirectory(){
	//設定檔案為當前的目錄
	const int nBufSize = 512;
    wchar_t chBuf[nBufSize];
    ZeroMemory(chBuf,nBufSize);
    GetModuleFileNameW(NULL,chBuf,nBufSize);
    LPWSTR lpStrPath = chBuf;
    PathRemoveFileSpecW(lpStrPath);
	SetCurrentDirectoryW(lpStrPath);
}

