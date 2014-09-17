#define DLL_EXPORT

#include "EntryDLL.h"
#include "SoftWare.h"

extern "C"
{
	DECLDIR int Upload(char* path, char* URL, int check ,double check2, char* Type)
	{
		int Message = 11111111;
		std::string Path(path);
		Path = Path + "\\YiWeather.exe";

		std::fstream _File;
		_File.open(Path, std::ios::in);
		if (!_File)
		{
			MessageBox(NULL, L"缺少主程序", L"提示", MB_OK);
		}
		else
		{
//包类型判断
			SM sm;
			char* BagType;
			std::string sTemp(URL);
			size_t len = sTemp.find_first_of('Q', 0);
			if (len != sTemp.npos)
			{
				sTemp = sTemp.replace(len, sTemp.length()-len, "");
				BagType = "1";
				URL = (char*)sTemp.c_str();

			}
			else
			{
				BagType = "0";
			}

			if (check2 == 0.618)
			{
				sm.ReadDataFromComputer(sm, BagType);
				if (sm.ReadDataFromIni(path, sm))
				{
					std::string _Message = sm.DataHanding(sm, URL, Type);
					if (!strcmp(_Message.c_str(),""))
					{
						Message = atoi(_Message.c_str());
					}
				}
			}
		}
		return Message;
	}

	DECLDIR char* Binterface(int Temp)
	{
		SM sm;
		if (Temp == 16)
		{
			return sm.GetInterfaceMac();
		}
		return "";
	}
}