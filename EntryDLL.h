#ifndef _ENTRYDLL_H_
#define _ENTRYDLL_H_

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
	DECLDIR int Upload(char*, char*, int, double, char*);
	DECLDIR char* Binterface(int);
}




#endif