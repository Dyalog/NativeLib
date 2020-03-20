#include <wchar.h>

#define DWA_DISABLE_ASSERTS

#include "call_apl.h"
#include "dllmain.h"		// not defining our own DllMain

EXPORT wchar_t* LIBCALL SignOf(int month,int day)
{
static wchar_t sign[256];
APL_INT32_PARAM(Month,month);
APL_INT32_PARAM(Day,day);
APL_WCHAR_ARRAY_RESULT(Sign,sign,255,AP_NULLTERM|AP_SIZED);
call_apl(L"GetSign",&Month,&Day,&Sign,PARAM_END);
return sign;
}

EXPORT int LIBCALL GetSign(int month,int day, wchar_t *sign, int len)
{
APL_INT32_PARAM(Month,month);
APL_INT32_PARAM(Day,day);
APL_WCHAR_ARRAY_RESULT(Sign,sign,len,AP_NULLTERM|AP_SIZED);
return call_apl(L"GetSign",&Month,&Day,&Sign,PARAM_END);
}



EXPORT wchar_t * LIBCALL ReturnSign(wchar_t *in)
{
static wchar_t sign[256];
APL_WCHAR_ARRAY_PARAM (Parm,in,0,AP_NULLTERM|AP_JSON);
APL_WCHAR_ARRAY_RESULT(Sign,sign,255,AP_NULLTERM|AP_SIZED|AP_JSON);
if (0==call_apl(L"GetSignObject",&Parm,&Sign,PARAM_END))
	return sign;
return 0;
}


EXPORT int LIBCALL GetSignObject(wchar_t *in,wchar_t *out,unsigned len)
{
APL_WCHAR_ARRAY_PARAM (Parm,in,0,AP_NULLTERM|AP_JSON);
APL_WCHAR_ARRAY_RESULT(Sign ,out,len,AP_NULLTERM|AP_JSON|AP_SIZED);
return call_apl(L"GetSignObject",&Parm,&Sign,PARAM_END);
}
