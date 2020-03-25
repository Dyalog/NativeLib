#include "call_apl.h"
#define DWA_DISABLE_ASSERTS
#include "dllmain.h"		// not defining our own DllMain

#include "stdio.h"
#include "wchar.h"

EXPORT int LIBCALL Initialise(unsigned int runtime, unsigned int len, wchar_t **args)
{
	return load_apl(runtime ? ENGINE_F_RUNTIME : 0, len, args);
}

EXPORT int LIBCALL ExecAPL(wchar_t *statement, wchar_t *result)
{
	APL_WCHAR_ARRAY_PARAM(S, statement, 256, AP_NULLTERM | AP_SIZED);
	APL_WCHAR_ARRAY_RESULT(R, result, 256, AP_NULLTERM | AP_SIZED);
	return call_apl(L"Exec", &S, &R, PARAM_END);
}

EXPORT int LIBCALL CallJSON(wchar_t *fname, wchar_t *in, wchar_t *out, unsigned int len)
{
	APL_WCHAR_ARRAY_PARAM(Parm, in, 0, AP_NULLTERM | AP_JSON);
	APL_WCHAR_ARRAY_RESULT(Res, out, len, AP_NULLTERM | AP_JSON | AP_SIZED);
	return call_apl(fname, &Parm, &Res, PARAM_END);
}

EXPORT int LIBCALL GetEnv(const wchar_t *name, wchar_t *value, size_t len)
{
	APL_WCHAR_ARRAY_PARAM(N, (wchar_t*)name, 0, AP_NULLTERM);
	APL_WCHAR_ARRAY_RESULT(R, value, len, AP_NULLTERM | AP_SIZED);
	return call_apl(L"GetEnv", &N, &R, PARAM_END);
}