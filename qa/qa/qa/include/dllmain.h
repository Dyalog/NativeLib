#define dwa_enable_asserts(enable) (0)

#if _MSC_VER
#include <windows.h>

#if _DEBUG
#undef dwa_enable_asserts
#include <crtdbg.h>
static int dwa_enable_asserts(int enable)
{
	return _CrtSetReportMode(_CRT_ASSERT, enable ? _CRTDBG_MODE_WNDW : _CRTDBG_MODE_DEBUG);
}
#endif

extern HINSTANCE dwa_hInst;


int WINAPI DllMain (HMODULE h,DWORD reason,LPVOID process_termination)
	{
	switch(reason)
		{
		case DLL_PROCESS_ATTACH:
			{
#if defined (DWA_DISABLE_ASSERTS)
			dwa_enable_asserts(0);
#endif
			dwa_hInst=h;
			break;
			}
		}
	return TRUE;
	}



#else
extern void * dwa_hInst;
#endif // _MSC_VER
