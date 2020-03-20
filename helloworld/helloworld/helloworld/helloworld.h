#if _MSC_VER
#define LIBCALL __cdecl
#else
#define LIBCALL 
#endif

extern wchar_t *LIBCALL Hello(wchar_t *name);
