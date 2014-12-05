
// stdafx.cpp : 只包括标准包含文件的源文件
// DrivingDemo.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"




CString GetProductName()
{
TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion;
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return L"";
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
 unsigned int  cbTranslate = 0;
 struct LANGANDCODEPAGE {
  WORD wLanguage;
  WORD wCodePage;
 } *lpTranslate;
 VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
 // Read the file description for each language and code page.
 for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
 {
  TCHAR  SubBlock[200];
  wsprintf( SubBlock,
            TEXT("\\StringFileInfo\\%04x%04x\\ProductName"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);
  void *lpBuffer=NULL;
  unsigned int dwBytes=0;
  VerQueryValue(InfoBuf,
   SubBlock,
   &lpBuffer,
   &dwBytes);
  CString strTemp=(TCHAR *)lpBuffer;
  strVersion+=strTemp;
 }

delete InfoBuf;
 return strVersion;
}
CString GetProductVersion()
{
	TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion;
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return L"";
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
 unsigned int  cbTranslate = 0;
 struct LANGANDCODEPAGE {
  WORD wLanguage;
  WORD wCodePage;
 } *lpTranslate;
 VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
 // Read the file description for each language and code page.
 for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
 {
  TCHAR  SubBlock[200];
  wsprintf( SubBlock,
            TEXT("\\StringFileInfo\\%04x%04x\\ProductVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);
  void *lpBuffer=NULL;
  unsigned int dwBytes=0;
  VerQueryValue(InfoBuf,
   SubBlock,
   &lpBuffer,
   &dwBytes);
  CString strTemp=(TCHAR *)lpBuffer;
  strVersion+=strTemp;
 }

delete InfoBuf;

return strVersion;
}

CString GetProductRight()
{
	TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion;
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //首先获得版本信息资源的长度
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //将版本信息资源读入缓冲区
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return L"";
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //获得生成文件使用的代码页及文件版本
 unsigned int  cbTranslate = 0;
 struct LANGANDCODEPAGE {
  WORD wLanguage;
  WORD wCodePage;
 } *lpTranslate;
 VerQueryValue(InfoBuf, TEXT("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate,&cbTranslate);
 // Read the file description for each language and code page.
 for( int i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
 {
  TCHAR  SubBlock[200];
  wsprintf( SubBlock,
            TEXT("\\StringFileInfo\\%04x%04x\\LegalCopyright"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);
  void *lpBuffer=NULL;
  unsigned int dwBytes=0;
  VerQueryValue(InfoBuf,
   SubBlock,
   &lpBuffer,
   &dwBytes);
  CString strTemp=(TCHAR *)lpBuffer;
  strVersion+=strTemp;
 }

delete InfoBuf;

return strVersion;
}