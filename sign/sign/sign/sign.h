#if _MSC_VER
#define LIBCALL __cdecl
#else
#define LIBCALL
#endif

extern int 	LIBCALL GetSign(int month, int day, wchar_t *rslt,int len);
extern int 	LIBCALL GetSignObject(wchar_t *in,wchar_t *out,size_t len);
extern wchar_t* LIBCALL ReturnSign(wchar_t *in);
extern void * 	LIBCALL SignFree(void *);
extern wchar_t* LIBCALL SignOf(int month,int day);

