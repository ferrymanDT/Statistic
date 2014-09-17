#ifndef _SOFTWARE_H_
#define _SOFTWARE_H_

#include <string>
#include <windows.h>
#include <fstream>

#include "time.h"


#include "MD5.h"
#include "ZBase64.h"


//PIP_ADAPTER_INFO  ͷ�ļ�
#include <iphlpapi.h>
#pragma comment(lib,"iphlpapi.lib")

//PathFileExists
//#include "Shlwapi.h"
//#pragma comment(lib,"Shlwapi.lib")

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------����ID��Ϣ��----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
struct  ReadData
{
	std::string ReadName;
	__int64 ReadValue;
};

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------������ID�������------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
struct Count
{
	int UserCodeCount;            //ID��Ŀ
	int SoftCount;                //�ƹ������Ŀ
};



//----------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------���������Ϣ--------------------------------------------------//
//---------------------1.�����--2.������--3.���--4.��װ·��--5.ж��·��--6.��װ��--7.����ʱ��-------------------//
//----------------------------------------------------------------------------------------------------------------//
typedef struct Soft
{
	std::string SoftName;                 //�������
	std::string ProcessName;              //��������
	std::string AbbreviateName;           //���
	std::string LocalAddress;             //��װ·��
	std::string UninstAddress;            //ж��·��
	bool IsInstall;                       //�Ƿ�װ
	bool InstallValid;                    //��װ�Ƿ���Ч
	__int64 NowTime;                      //��ǰϵͳʱ��
	SYSTEMTIME StartTime;                 //��ʼ
	SYSTEMTIME EndTime;                   //�رռ�ʱ
}SW;


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------����-------------------------------------------------------//
//-----------------------1.��ȡMAC,CPUID,Ӳ��ID PID��CID��������Լ��䰲װ��Ϣ 2.ͳ�Ƹ������������װ-------------//
//----------------------------------------------------------------------------------------------------------------//
typedef class Manage
{
public:
	//����
	std::string GetMacCode();                                            //MAC��ȡ
	std::string GetCpuCode();                                            //CPUID��ȡ
	std::string GetHDID();                                               //Ӳ��ID��ȡ
	void ReadDataFromComputer(Manage &sm, char* BagType);                //��ȡ������
	bool ReadDataFromIni(char* Path, Manage &sm);                        //��ȡID��Ϣ
	std::string RandomString();											 //����ַ���
	std::string HandleSecret();                                          //�����ض��ַ�

	//��¼д��  ����ǰ�ж��Ƿ�װĳ���
	void WriteCheckData(char *path, Manage &sm);
	void ReadCheckData(char *path, Manage &sm);
	
	

	//������
	bool InstallIsOrNo(SW sw);
	LRESULT GetValue(HKEY hKey, LPCTSTR name, LPTSTR value, LPLONG size);
	void DumpSoftware(LPCTSTR szKey , HKEY hParent, Manage &sm, int place);
	int GetSoftInformation(Manage &sm, int place);                       //��ȡ�����װ��Ϣ
	std::string TCHA2STRING(char* tchStr);                               //char*תString(char* ת wchar_t*)
	bool FindProcess(WCHAR* Progress);									 //���̲���


	std::string DataHanding(Manage &sm, char* URL, char* Type );
	bool FeedBackInformation(char* URL, std::string &BackMessage);           //ͳ����Ϣ���ܷ���
	std::string GetFileVersion(std::string FileName);

	char* GetInterfaceMac();
	std::string WorkChange(std::string s);

private:
	std::string MACCode;                                                 //MAC��ַ
	std::string CpuCode;                                                 //CPUID
	std::string HDID;                                                    //Ӳ��ID
	std::string Random;                                                  //�����
	std::string SecretM;                                                 //������
	Count count;                                                         //����


	std::string Version;                                                 //�汾��
	std::string BagType;                                                 //��������

	ReadData rd[MAX_PATH];                                               //ID�� PID, CID�� UID��
}SM;

#endif