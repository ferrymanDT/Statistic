#ifndef _SOFTWARE_H_
#define _SOFTWARE_H_

#include <string>
#include <windows.h>
#include <fstream>

#include "time.h"


#include "MD5.h"
#include "ZBase64.h"


//PIP_ADAPTER_INFO  头文件
#include <iphlpapi.h>
#pragma comment(lib,"iphlpapi.lib")

//PathFileExists
//#include "Shlwapi.h"
//#pragma comment(lib,"Shlwapi.lib")

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------保存ID信息等----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
struct  ReadData
{
	std::string ReadName;
	__int64 ReadValue;
};

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------计数（ID，软件）------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
struct Count
{
	int UserCodeCount;            //ID数目
	int SoftCount;                //推广软件数目
};



//----------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------软件属性信息--------------------------------------------------//
//---------------------1.软件名--2.进程名--3.简称--4.安装路径--5.卸载路径--6.安装性--7.运行时长-------------------//
//----------------------------------------------------------------------------------------------------------------//
typedef struct Soft
{
	std::string SoftName;                 //软件名字
	std::string ProcessName;              //进程名字
	std::string AbbreviateName;           //简称
	std::string LocalAddress;             //安装路径
	std::string UninstAddress;            //卸载路径
	bool IsInstall;                       //是否安装
	bool InstallValid;                    //安装是否有效
	__int64 NowTime;                      //当前系统时间
	SYSTEMTIME StartTime;                 //开始
	SYSTEMTIME EndTime;                   //关闭计时
}SW;


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------管理-------------------------------------------------------//
//-----------------------1.获取MAC,CPUID,硬盘ID PID，CID，软件属性及其安装信息 2.统计各种类型软件安装-------------//
//----------------------------------------------------------------------------------------------------------------//
typedef class Manage
{
public:
	//函数
	std::string GetMacCode();                                            //MAC获取
	std::string GetCpuCode();                                            //CPUID获取
	std::string GetHDID();                                               //硬盘ID获取
	void ReadDataFromComputer(Manage &sm, char* BagType);                //读取机器码
	bool ReadDataFromIni(char* Path, Manage &sm);                        //读取ID信息
	std::string RandomString();											 //随机字符串
	std::string HandleSecret();                                          //处理特定字符

	//记录写出  运行前判断是否安装某软件
	void WriteCheckData(char *path, Manage &sm);
	void ReadCheckData(char *path, Manage &sm);
	
	

	//软件监测
	bool InstallIsOrNo(SW sw);
	LRESULT GetValue(HKEY hKey, LPCTSTR name, LPTSTR value, LPLONG size);
	void DumpSoftware(LPCTSTR szKey , HKEY hParent, Manage &sm, int place);
	int GetSoftInformation(Manage &sm, int place);                       //获取软件安装信息
	std::string TCHA2STRING(char* tchStr);                               //char*转String(char* 转 wchar_t*)
	bool FindProcess(WCHAR* Progress);									 //进程查找


	std::string DataHanding(Manage &sm, char* URL, char* Type );
	bool FeedBackInformation(char* URL, std::string &BackMessage);           //统计信息汇总发送
	std::string GetFileVersion(std::string FileName);

	char* GetInterfaceMac();
	std::string WorkChange(std::string s);

private:
	std::string MACCode;                                                 //MAC地址
	std::string CpuCode;                                                 //CPUID
	std::string HDID;                                                    //硬盘ID
	std::string Random;                                                  //随机数
	std::string SecretM;                                                 //特征码
	Count count;                                                         //计数


	std::string Version;                                                 //版本号
	std::string BagType;                                                 //包的类型

	ReadData rd[MAX_PATH];                                               //ID号 PID, CID， UID等
}SM;

#endif