#include "SoftWare.h"


//ģ��һ��
//----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------��ʼ��-------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------Ψһ��Ϣ��ȡ---------------------------------------------------//
//----------------------------1.MAC 2.CPUID 3.HDID 4.Random(�����) 5.������ 6.ID�� 7.��������--------------------//
void SM::ReadDataFromComputer(Manage &sm, char* BagType)
{
	sm.MACCode = GetMacCode();
	sm.CpuCode = GetCpuCode();
	sm.HDID = GetHDID();
	sm.Random = RandomString();
	sm.SecretM = HandleSecret();

	sm.BagType = BagType;       //��������
	
	//����
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
//------------------------------------------------��ȡMAC��ַ-----------------------------------------------------//
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
	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//�õ��ṹ���С,����GetAdaptersInfo����
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    //����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	//��¼��������
    int netCardNum = 0;
    //��¼ÿ�������ϵ�IP��ַ����
	int IPnumPerNetCard = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel)
    {
		//����������ص���ERROR_BUFFER_OVERFLOW
        //��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
        //��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
        //�ͷ�ԭ�����ڴ�ռ�
        delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        //�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		//���������Ϣ
		 //�����ж�����,���ͨ��ѭ��ȥ�ж�
	while (pIpAdapterInfo)
	{
	  /*  std::cout<<"����������"<<++netCardNum<<std::endl;
		std::cout<<"�������ƣ�"<<pIpAdapterInfo->AdapterName<<std::endl;
		std::cout<<"����������"<<pIpAdapterInfo->Description<<std::endl;
		switch(pIpAdapterInfo->Type)
		{
		case MIB_IF_TYPE_OTHER:
			std::cout<<"�������ͣ�"<<"OTHER"<<std::endl;
			break;
		case MIB_IF_TYPE_ETHERNET:
            std::cout<<"�������ͣ�"<<"ETHERNET"<<std::endl;
			break;
		case MIB_IF_TYPE_TOKENRING:
			std::cout<<"�������ͣ�"<<"TOKENRING"<<std::endl;
			break;
		case MIB_IF_TYPE_FDDI:
			std::cout<<"�������ͣ�"<<"FDDI"<<std::endl;
            break;
        case MIB_IF_TYPE_PPP:
            printf("PP\n");
			std::cout<<"�������ͣ�"<<"PPP"<<std::endl;
            break;
        case MIB_IF_TYPE_LOOPBACK:
            std::cout<<"�������ͣ�"<<"LOOPBACK"<<std::endl;
			break;
        case MIB_IF_TYPE_SLIP:
            std::cout<<"�������ͣ�"<<"SLIP"<<std::endl;
            break;
		default:

            break;
        }*/
		//std::cout<<"����MAC��ַ��";
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
            //std::cout<<"����IP��ַ���£�"<<std::endl;
            //���������ж�IP,���ͨ��ѭ��ȥ�ж�
			//IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
          /*  do
            {
                std::cout<<"�������ϵ�IP������"<<++IPnumPerNetCard<<std::endl;
				std::cout<<"IP ��ַ��"<<pIpAddrString->IpAddress.String<<std::endl;
                std::cout<<"������ַ��"<<pIpAddrString->IpMask.String<<std::endl;
                std::cout<<"���ص�ַ��"<<pIpAdapterInfo->GatewayList.IpAddress.String<<std::endl;
				pIpAddrString=pIpAddrString->Next;
			} while (pIpAddrString);*/
			pIpAdapterInfo = pIpAdapterInfo->Next;
			//std::cout<<"--------------------------------------------------------------------"<<std::endl;
	}

	}
	//�ͷ��ڴ�ռ�
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}


	//ȡ������
	Temp = MD5Encode((char*)Temp.c_str());
	Temp = Temp.assign(Temp, 0 ,8);

	return Temp;
}

//----------------------------------------------------------------------------------------------------------------//
//------------------------------------------------��ȡCPUID��ַ---------------------------------------------------//
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
//------------------------------------------------��ȡӲ�̵�ַ----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::GetHDID()
{
	return "";
}


//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------��ȡ�����-----------------------------------------------------//
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
//-------------------------------------------------�����ض��ַ�---------------------------------------------------//
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
//-------------------------------------------------�����ļ���ȡ---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool SM::ReadDataFromIni(char* Path, SM &sm)
{
	return true;
}



//ģ�����
//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------�����װ��Ϣ��ȡ-----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------������װ�б�---------------------------------------------------//
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
				//cout<<_T("������������") << endl;
				RegCloseKey(hKey);
				return 0;
			default:
				//("δ��������������");
				RegCloseKey(hKey);
				return -2;
		}
	}
	RegCloseKey(hKey);
	return -1;*/
	return 1;
}


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------��ȡע���װ��Ϣ-----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
void SM::DumpSoftware(LPCTSTR szKey , HKEY hParent, SM &sm, int place)
{
	/*LRESULT lr;
	HKEY hKey;
	LONG size;
	TCHAR buffer[MAX_PATH] ;
	lr = RegOpenKey(hParent, szKey, &hKey);

	//���ܴ�ע���
	if(lr != ERROR_SUCCESS)
	{
		//cout << _T("���ܴ�ע���") << szKey << _T("(") << lr << _T(")") << endl;
		return;
	}

	size = sizeof(buffer);
	lr = GetValue(hKey, L"DisplayName", &buffer[0], &size);

	//ע���򿪳ɹ�
	if(lr == ERROR_SUCCESS)
	{
		 if(size > 0)
         {
			  //cout << _T("��ʾ���֣�" ) << buffer << endl;
		 }
	}
	else
	{
		size = sizeof(buffer);
		lr = GetValue(hKey, L"QuietDisplayName", &buffer[0], &size);
		if(ERROR_SUCCESS== lr && size > 0 )
		{
			//cout << _T("��ʾ���֣�" ) << buffer << endl;
		}
	}*/
}


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------��ȡע���װ��Ϣ-----------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
LRESULT SM::GetValue(HKEY hKey, LPCTSTR name, LPTSTR value, LPLONG size)
{
	  return ::RegQueryValueEx(hKey, name, NULL, NULL, (LPBYTE)value, (LPDWORD)size);
}


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------����ת��---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string  SM::TCHA2STRING(char* tchStr)
{
	//int iLen = WideCharToMultiByte(CP_ACP, 0,tchStr, -1, NULL, 0, NULL, NULL);
	//char* chRtn =new char[iLen*sizeof(char)];
	//WideCharToMultiByte(CP_ACP, 0, tchStr, -1, chRtn, iLen, NULL, NULL);
	std::string str(tchStr);
	return str;
}


//ģ������
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------���м��---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool SM::FindProcess(WCHAR* Progress)
{
	return true;
}


//ģ���ģ�
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------�������---------------------------------------------------//
//-----------------------------------�����װʱ���������ע����鿴�б�������Ƿ�װ---------------------------//
//----------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------��������---------------------------------------------------//
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


//ģ���壺
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------�ύͳ��---------------------------------------------------//
//-----------------------------------------------1.��Ϣ���� 2.�ύ����--------------------------------------------// 
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------��Ϣ����---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
std::string SM::DataHanding(SM &sm, char* URL, char* Type)
{
	return "";
}

//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------�ύ����---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
bool SM::FeedBackInformation(char* URL, std::string &BackMessage)
{
	return true;
}





//�ӿڶ�����ش���
//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------����MID----------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------MAC��ַת��--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
char* SM::GetInterfaceMac()
{
	return "";
}

//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------�ַ���ȡ---------------------------------------------------//
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