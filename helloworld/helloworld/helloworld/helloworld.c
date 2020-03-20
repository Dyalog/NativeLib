#include "call_apl.h"
#define DWA_DISABLE_ASSERTS
#include "dllmain.h"		// not defining our own DllMain

#include "stdio.h"
#include "wchar.h"


EXPORT wchar_t * Hello(wchar_t *name)
{
static wchar_t rslt[256];
int retn;
APL_WCHAR_ARRAY_PARAM (Name,name,0   ,AP_NULLTERM);
APL_WCHAR_ARRAY_RESULT(Rslt,rslt,256,AP_NULLTERM|AP_SIZED);
retn = call_apl(L"Hello",&Name,&Rslt,PARAM_END);
if (retn!=0)
	printf("call_apl returned: %i\n",retn);
return rslt;
}

