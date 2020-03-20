#if defined(_MSC_VER)
#include <windows.h>
#endif
#include <stdio.h>
#include <wchar.h>

#include "helloworld.h"

#if defined(_MSC_VER)
int __cdecl main(int argc, char *argv[])
#else
int         main(int argc, char *argv[])
#endif
{

	wprintf(Hello(L" "));
	wprintf(L"\n\r");
	return 0;
}
