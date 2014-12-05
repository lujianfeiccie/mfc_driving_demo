
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// DrivingDemo.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"




CString GetProductName()
{
TCHAR cPath[200],szVersionBuffer[200];
 DWORD dwHandle,InfoSize;
 CString strVersion;
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //���Ȼ�ð汾��Ϣ��Դ�ĳ���
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //���汾��Ϣ��Դ���뻺����
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return L"";
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //��������ļ�ʹ�õĴ���ҳ���ļ��汾
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
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //���Ȼ�ð汾��Ϣ��Դ�ĳ���
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //���汾��Ϣ��Դ���뻺����
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return L"";
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //��������ļ�ʹ�õĴ���ҳ���ļ��汾
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
 ::GetModuleFileName(NULL,cPath,sizeof(cPath)); //���Ȼ�ð汾��Ϣ��Դ�ĳ���
 InfoSize = GetFileVersionInfoSize(cPath,&dwHandle); //���汾��Ϣ��Դ���뻺����
 if(InfoSize==0) 
 {
  AfxMessageBox(_T("None VerSion Supprot"));
  return L"";
 }
 char *InfoBuf = new char[InfoSize];
 GetFileVersionInfo(cPath,0,InfoSize,InfoBuf); //��������ļ�ʹ�õĴ���ҳ���ļ��汾
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