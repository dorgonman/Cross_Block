
#include "PersonalData.h"

#include <shlwapi.h> 
#pragma comment(lib, "shlwapi.lib")
vector<string> PersonalData::getAllFile(char* folderPath, char* fileType){
	char targetPath[MAX_PATH];
	char filePath[MAX_PATH];
	HANDLE hFind;
	WIN32_FIND_DATAA findFileData;


	vector<string> files;

	// �]�w�ɮ׷j�M�r��

	sprintf(targetPath, "%s%s", folderPath, fileType);

	// �}�l�j�M�ɮ�

	if( (hFind = FindFirstFileA(targetPath, &findFileData)) != INVALID_HANDLE_VALUE) {

		do{ // �C���@�ӲŦX���ɮ״N�|�i�J�j��A����䤣��ŦX���ɮ�
			if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){ // ��ܨëD�ؿ�
				// �N�ɮת��۹���g�s�J FilePath �r�ꤧ��
				sprintf(filePath, "%s%s", folderPath, findFileData.cFileName);
				files.push_back(filePath);
			}

		}while(FindNextFileA(hFind, &findFileData)); // �M��U�@���ɮ�

	FindClose(hFind);
	}

	return files;
}

void PersonalData::currentDirectory(){
	//�]�w�ɮ׬���e���ؿ�
	const int nBufSize = 512;
    wchar_t chBuf[nBufSize];
    ZeroMemory(chBuf,nBufSize);
    GetModuleFileNameW(NULL,chBuf,nBufSize);
    LPWSTR lpStrPath = chBuf;
    PathRemoveFileSpecW(lpStrPath);
	SetCurrentDirectoryW(lpStrPath);
}

