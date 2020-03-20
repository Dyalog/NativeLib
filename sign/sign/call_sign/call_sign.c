#if defined(_MSC_VER)
#include <windows.h>
#endif
#include <stdio.h>
#include <wchar.h>
#include "sign.h"

#if defined(_MSC_VER)
#if !defined(CDECL)
	#define CDECL __cdecl
#endif
#define scanf scanf_s
#else
#define CDECL 
#endif

int  CDECL main(int argc, char *argv[])
{

#if defined(_MSC_VER)
	// CYGWIN issue: https://github.com/mintty/mintty/issues/218
	// doesn't change behaviour in CMD.EXE
	setvbuf(stdout, 0, _IONBF, 0); 
#endif

	wchar_t *jd = SignOf(8,31);
	wprintf(L"jd is a %ls\n" ,jd);

	wchar_t buf[256];
	int err = GetSign(4,10,buf,256);
	wprintf(L"GRS is a %ls (error:%i)\n" ,buf,err);

	wchar_t *retn = ReturnSign(L"{\"month\":8,\"day\":31}");
	wprintf(L"jd is a %ls\n" ,retn);

	err = GetSignObject(L"{\"month\":8,\"day\":31}",buf,255);
	wprintf(L"jd is a %ls (error:%i)\n" ,buf,err);

	int m,d;
	while (EOF!=scanf("%i %i",&m,&d))
		wprintf(L"%i:%i is a %ls\n" ,m,d,SignOf(m,d));

	return 0;
}
