#include "SoftWare.h"


//模块一：
//----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------初始化-------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------唯一信息获取---------------------------------------------------//
//----------------------------1.MAC 2.CPUID 3.HDID 4.Random(随机数) 5.特征码 6.ID号 7.包的类型--------------------//
void SM::ReadDataFromComputer(Manage &sm, char* BagType)
{
	sm.MACCode = GetMacCode();
	sm.CpuCode = GetCpuCode();
	sm.HDID = GetHDID();
	sm.Random = RandomString();
	sm.SecretM = HandleSecret();

	sm.BagType = BagType;       //包的类型
	
	//参数
	sm.rd[0].ReadName = "CID";
	sm.rd[1].ReadName = "MID";
	sm.rd[2].ReadName = "PID";
	sm.rd[3].ReadName = "UID";
	sm.rd[0].ReadValue = 1;
	sm.rd[1].ReadValue = 1;
	sm.rd[2].ReadValue = 1;
	sm.rd[3].ReadValue = 1;
}

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------获取MAC地址-----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::GetMacCode()
{
	/*IP_ADAPTER_INFO adapter[5];  //Maximum 5 adapters

	DWORD buflen=sizeof(adapter);

	DWORD status=GetAdaptersInfo(adapter,&buflen);

	BYTE s[8];
	if(status==ERROR_SUCCESS)
	{

	PIP_ADAPTER_INFO painfo=adapter;
	memcpy(s,painfo->Address,6);
	}
	char mac_addr[18];
	sprintf(mac_addr,"%02X-%02X-%02X-%02X-%02X-%02X",s[0],s[1],s[2],s[3],s[4],s[5]);

	return mac_addr;  */

	std::string  Temp;
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	//记录网卡数量
    int netCardNum = 0;
    //记录每张网卡上的IP地址数量
	int IPnumPerNetCard = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
        //则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
        //这也是说明为什么stSize既是一个输入量也是一个输出量
        //释放原来的内存空间
        delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		//输出网卡信息
		 //可能有多网卡,因此通过循环去判断
	while (pIpAdapterInfo)
	{
	  /*  std::cout<<"网卡数量："<<++netCardNum<<std::endl;
		std::cout<<"网卡名称："<<pIpAdapterInfo->AdapterName<<std::endl;
		std::cout<<"网卡描述："<<pIpAdapterInfo->Description<<std::endl;
		switch(pIpAdapterInfo->Type)
		{
		case MIB_IF_TYPE_OTHER:
			std::cout<<"网卡类型："<<"OTHER"<<std::endl;
			break;
		case MIB_IF_TYPE_ETHERNET:
            std::cout<<"网卡类型："<<"ETHERNET"<<std::endl;
			break;
		case MIB_IF_TYPE_TOKENRING:
			std::cout<<"网卡类型："<<"TOKENRING"<<std::endl;
			break;
		case MIB_IF_TYPE_FDDI:
			std::cout<<"网卡类型："<<"FDDI"<<std::endl;
            break;
        case MIB_IF_TYPE_PPP:
            printf("PP\n");
			std::cout<<"网卡类型："<<"PPP"<<std::endl;
            break;
        case MIB_IF_TYPE_LOOPBACK:
            std::cout<<"网卡类型："<<"LOOPBACK"<<std::endl;
			break;
        case MIB_IF_TYPE_SLIP:
            std::cout<<"网卡类型："<<"SLIP"<<std::endl;
            break;
		default:

            break;
        }*/
		//std::cout<<"网卡MAC地址：";
        //for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
            /*if (i < pIpAdapterInfo->AddressLength-1)
            {
				printf("%02X-", pIpAdapterInfo->Address[i]);
            }
            else
            {
				printf("%02X\n", pIpAdapterInfo->Address[i]);
            }*/
	char mac_addr[18];
	sprintf(mac_addr,"%02X%02X%02X%02X%02X%02X",pIpAdapterInfo->Address[0],pIpAdapterInfo->Address[1],pIpAdapterInfo->Address[2],pIpAdapterInfo->Address[3],pIpAdapterInfo->Address[4],pIpAdapterInfo->Address[5]);
	Temp = Temp + (mac_addr);
	//std::count<<ss<<std::endl;
            //std::cout<<"网卡IP地址如下："<<std::endl;
            //可能网卡有多IP,因此通过循环去判断
			//IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
          /*  do
            {
                std::cout<<"该网卡上的IP数量："<<++IPnumPerNetCard<<std::endl;
				std::cout<<"IP 地址："<<pIpAddrString->IpAddress.String<<std::endl;
                std::cout<<"子网地址："<<pIpAddrString->IpMask.String<<std::endl;
                std::cout<<"网关地址："<<pIpAdapterInfo->GatewayList.IpAddress.String<<std::endl;
				pIpAddrString=pIpAddrString->Next;
			} while (pIpAddrString);*/
			pIpAdapterInfo = pIpAdapterInfo->Next;
			//std::cout<<"--------------------------------------------------------------------"<<std::endl;
	}

	}
	//释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}


	//取数处理
	Temp = MD5Encode((char*)Temp.c_str());
	Temp = Temp.assign(Temp, 0 ,8);

	return Temp;
}

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------获取CPUID地址---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::GetCpuCode()
{
	#define CPUID dw 0xa20f
	DWORD dwCPUName, dwCPUReserved1, dwCPUReserved2, dwCPUID;
	std::string strCPUID;
	_asm
	{
		PUSHAD
		MOV EAX, 1
		CPUID
		MOV dwCPUName, EAX
		MOV dwCPUReserved1, EBX
		MOV dwCPUReserved2, ECX
		MOV dwCPUID, EDX
		POPAD
	}
	strCPUID.sprintf("%08X-%08X-%08X", dwCPUID,dwCPUName,dwCPUReserved2);


	return strCPUID;
}


//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------获取硬盘地址----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::GetHDID()
{
	return "";
}


//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------获取随机数-----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::RandomString()
{
	std::string Temp = "";
	int Digital = 0;
	srand((unsigned)time(NULL));
	for(int i = 0; i < 8; i++)
	{
		Digital = rand()%26;
		Temp += 'a' + Digital;
	}
	return Temp;
}

//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------处理特定字符---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::HandleSecret()
{
	ZBase64 ecode;
	int OutPut = 0;
	std::string Secret = "d3d3LjEwMDByZS5jb20=";
	Secret = ecode.Decode(Secret.c_str(), Secret.length(), OutPut);
	Secret = MD5Encode((char*)Secret.c_str());

	/*int len = Secret.length();
	char* p = (char*)Secret.c_str();
	std::string res("");
	for(int idx = 0; idx < len; ++idx)
	{
		if(*p == '\')
		{
			res += "\\";
		}
		else
		{
			res += *p;
		}
	}*/
	return Secret; 
}

//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------配置文件读取---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool SM::ReadDataFromIni(char* Path, SM &sm)
{
	return true;
}



//模块二：
//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------软件安装信息获取-----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------搜索安装列表---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
int SM::GetSoftInformation(SM &sm, int place)
{
	/*unsigned long index;
	TCHAR buffer[MAX_PATH];
	HKEY hKey;
	LRESULT lr;
	lr = RegOpenKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", & hKey);
	if(lr != ERROR_SUCCESS)
	{
		return -1;
	}

	bool Exchange = false;
	for(index =0;!Exchange;index++)
	{
		lr = RegEnumKey(hKey, index, &buffer[0], sizeof(buffer));
		std::string str = 	TCHA2STRING(buffer);

		switch(lr)
		{
			case ERROR_SUCCESS:
				if(strcmp(str.c_str(),sm.sw[place].SoftName.c_str()) == 0)
				{
					DumpSoftware(buffer,hKey,sm, place);
					Exchange = true;
				}
			  break;
			case ERROR_NO_MORE_ITEMS:
				//cout<<_T("完成软件搜索！") << endl;
				RegCloseKey(hKey);
				return 0;
			default:
				//("未能完成软件搜索！");
				RegCloseKey(hKey);
				return -2;
		}
	}
	RegCloseKey(hKey);
	return -1;*/
	return 1;
}


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------获取注册表安装信息-----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
void SM::DumpSoftware(LPCTSTR szKey , HKEY hParent, SM &sm, int place)
{
	/*LRESULT lr;
	HKEY hKey;
	LONG size;
	TCHAR buffer[MAX_PATH] ;
	lr = RegOpenKey(hParent, szKey, &hKey);

	//不能打开注册表
	if(lr != ERROR_SUCCESS)
	{
		//cout << _T("不能打开注册表！") << szKey << _T("(") << lr << _T(")") << endl;
		return;
	}

	size = sizeof(buffer);
	lr = GetValue(hKey, L"DisplayName", &buffer[0], &size);

	//注册表打开成功
	if(lr == ERROR_SUCCESS)
	{
		 if(size > 0)
         {
			  //cout << _T("显示名字：" ) << buffer << endl;
		 }
	}
	else
	{
		size = sizeof(buffer);
		lr = GetValue(hKey, L"QuietDisplayName", &buffer[0], &size);
		if(ERROR_SUCCESS== lr && size > 0 )
		{
			//cout << _T("显示名字：" ) << buffer << endl;
		}
	}*/
}


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------获取注册表安装信息-----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
LRESULT SM::GetValue(HKEY hKey, LPCTSTR name, LPTSTR value, LPLONG size)
{
	  return ::RegQueryValueEx(hKey, name, NULL, NULL, (LPBYTE)value, (LPDWORD)size);
}


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------类型转换---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string  SM::TCHA2STRING(char* tchStr)
{
	//int iLen = WideCharToMultiByte(CP_ACP, 0,tchStr, -1, NULL, 0, NULL, NULL);
	//char* chRtn =new char[iLen*sizeof(char)];
	//WideCharToMultiByte(CP_ACP, 0, tchStr, -1, chRtn, iLen, NULL, NULL);
	std::string str(tchStr);
	return str;
}


//模块三：
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------运行监控---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool SM::FindProcess(WCHAR* Progress)
{
	return true;
}


//模块四：
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------输入输出---------------------------------------------------//
//-----------------------------------软件安装时启动，检测注册表，查看列表中软件是否安装---------------------------//
//----------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------保护程序---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

void SM::WriteCheckData(char* path, Manage &sm)
{
	/*TIniFile *ini;
	AnsiString Path = AnsiString(path) + "\\DATA.ini";
	if (FileExists(Path))
		DeleteFile(Path +"\\DATA.ini");
	ini = new TIniFile(Path);
	for (int i = 0; i < sm.count.SoftCount; i++) {
		 if(sm.sw[i].IsInstall)
		 {
			ini->WriteBool("DATA", (char*)sm.sw[i].AbbreviatedName.c_str(), 0);
		 }
		 else
		 {
			ini->WriteBool("DATA", (char*)sm.sw[i].AbbreviatedName.c_str(), 1);
		 }
	}
	delete ini;*/
}


void SM::ReadCheckData(char* path, Manage &sm)
{
	/*AnsiString Path = AnsiString(path) + "\\DATA.ini";
	AnsiString s;
	if (FileExists(Path))
	{
		TIniFile *ini1;
		try
		{
			ini1  = new TIniFile(Path);
			for (int i = 0; i < sm.count.SoftCount; i++)
			{
				sm.sw[i].InstallValid = ini1->ReadBool("DATA",(char*)sm.sw[i].AbbreviatedName.c_str(),0);
			}
		}
		catch(...)
		{
			delete ini1;
		}
		delete ini1;
	}*/
}


//模块五：
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------提交统计---------------------------------------------------//
//-----------------------------------------------1.信息汇总 2.提交服务--------------------------------------------// 
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------信息汇总---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::DataHanding(SM &sm, char* URL, char* Type)
{
	return "";
}

//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------提交服务---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool SM::FeedBackInformation(char* URL, std::string &BackMessage)
{
	return true;
}





//接口二：相关处理
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------返回MID----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------MAC地址转换--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
char* SM::GetInterfaceMac()
{
	return "";
}

//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------字符截取---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::WorkChange(std::string s)
{
	char* Temp = (char*)s.c_str();
	int num[2];

	//Memo1->Lines->Add(Temp);


	for (int i = 0; i < 2; i++) {


		switch (Temp[i]) {
		case '0':num[i]=0;break;
		case '1':num[i]=1;break;
		case '2':num[i]=2;break;
		case '3':num[i]=3;break;
		case '4':num[i]=4;break;
		case '5':num[i]=5;break;
		case '6':num[i]=6;break;
		case '7':num[i]=7;break;
		case '8':num[i]=8;break;
		case '9':num[i]=9;break;
		case 'a':num[i]=10;break;
		case 'b':num[i]=11;break;
		case 'c':num[i]=12;break;
		case 'd':num[i]=13;break;
		case 'e':num[i]=14;break;
		case 'f':num[i]=15;break;
		default:
			;
		}
	}

	int a = num[0]*16 + num[1];

	//return char(a);
	return "";
}