extern "C" {
#if defined(_MSC_VER)
#define LIBCALL __cdecl
#include <windows.h>
#else
#define LIBCALL
#define WINAPI
#endif
#if __APPLE__
#include <xlocale.h>
#endif
#include <stdio.h>
#include <wchar.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
}

#define AV_QUAD   0x2395
#define AV_LEFT   0x2190

#define EWSFULL		1
#define ESYNTAX		2
#define EINDEX		3
#define ERANK		4
#define ELENGTH		5
#define EVALUE		6
#define ELIMIT		10
#define EDOMAIN		11
#define EHOLD		12
#define EOPTION 	13	
#define ENONCE		16
#define EACCESS		17

#define 	AP_NULLTERM	0x08000000
#define 	AP_SIZED	0x00800000
#define 	AP_ALLOC	0x00400000

typedef unsigned int uint;
typedef unsigned char ubyte;

extern int LIBCALL Start(uint runtime,const wchar_t *user_param);

extern int LIBCALL NumericArray(double start, int32_t len, int8_t *out);
extern int LIBCALL NumericArray(double start, int32_t len, int16_t *out);
extern int LIBCALL NumericArray(double start, int32_t len, int32_t *out);
extern int LIBCALL NumericArray(double start, int32_t len, int64_t *out);
extern int LIBCALL NumericArray(double start, int32_t len, double *out);

extern int LIBCALL ScalarAdd(int16_t,int16_t,int32_t*);
extern int LIBCALL ScalarAdd(int16_t,int16_t,int16_t*);
extern int LIBCALL ScalarAdd(int16_t,int16_t,int8_t*);
extern int LIBCALL enable_asserts(int);

extern int LIBCALL UCStoCHARArray(int32_t *,size_t, char *, size_t);
extern int LIBCALL UCStoCHARArray(int32_t *,size_t, uint8_t *, size_t);
extern int LIBCALL UCStoCHARArray(int32_t *,size_t, uint16_t *, size_t);
extern int LIBCALL UCStoCHARArray(int32_t *,size_t, wchar_t *, size_t);

extern int LIBCALL UCStoCHAR(int32_t,wchar_t *);
extern int LIBCALL UCStoCHAR(int32_t,char *);

extern int LIBCALL Reflect(int8_t *,size_t, int8_t *, size_t);
extern int LIBCALL Reflect(int16_t *,size_t, int16_t *, size_t);
extern int LIBCALL Reflect(int32_t *,size_t, int32_t *, size_t);

extern int LIBCALL ReflectChar(char *p1, size_t len, uint iflags,char *out, size_t olen, uint flags);
extern int LIBCALL ReflectChar(uint8_t *p1, size_t len, uint iflags,uint8_t *out, size_t olen, uint flags);
extern int LIBCALL ReflectChar(uint16_t *p1, size_t len,uint iflags, uint16_t *out, size_t olen, uint flags);
extern int LIBCALL ReflectChar(uint32_t *p1, size_t len,uint iflags, uint32_t *out, size_t olen, uint flags);
extern int LIBCALL ReflectChar(wchar_t *p1, size_t len,uint iflags, wchar_t *out, size_t olen, unsigned int flags);

extern int LIBCALL ReflectLengthShort(void);
extern int LIBCALL ReflectLengthLong(void);

extern int LIBCALL NoAPLFunction(const wchar_t *name);

extern int LIBCALL Signal(int n);
extern int LIBCALL Error(int n);

extern int LIBCALL Deserialize(wchar_t *string,size_t len, ubyte *vp);
extern int LIBCALL SerializeAndAlloc(wchar_t *string, ubyte **vp);

extern int LIBCALL GetEnv(const wchar_t *name, wchar_t *value, size_t len);
extern int LIBCALL Execute(wchar_t *name, wchar_t *value, size_t len);


#define ARRAY(...)	__VA_ARGS__

#define laffirm(expr,l) ((expr)?1:fail(#expr,l))
#define affirm(expr) laffirm(expr,__LINE__)

static int RETN=0;

static int fail(const char *str, int line)
{
RETN=1;
char msg[256];
sprintf(msg, "QA Failure: \"%s\" is false on line %i\n", str, line);
#if defined (_MSC_VER)
OutputDebugStringA(msg);
#endif
printf("%s",msg);
return 0;
}

template <typename T> 
int check_array(T *p1, T*p2, int64_t len,int line)
{
for (int64_t i=0;i<len;i++) 
	if (0==laffirm(p1[i]==p2[i],line)) 
		return 0;
return 1;
}

#define AFFIRMNUMERICARRAY(type,start,len,retn,...) {		\
type r[len]; int err = NumericArray(start,len,r);	\
if (affirm(err==retn) && err==0) {type exp[len]={__VA_ARGS__}; check_array(exp,r,len,__LINE__);}\
}

wchar_t *add_tid(const wchar_t *fmt, wchar_t *buf, size_t len)
{
int tid=0;

#if defined(_MSC_VER)
tid = GetCurrentThreadId();
#endif

	swprintf(buf, len, fmt, tid);
	return buf;

}

unsigned long WINAPI run(void *ignore)
	{
	int err;

	AFFIRMNUMERICARRAY(int8_t,0,3,                 0,ARRAY(0,1,2));
	AFFIRMNUMERICARRAY(int8_t,-1,3,                0,ARRAY(-1,0,1));
	AFFIRMNUMERICARRAY(int8_t,SCHAR_MAX-1,3,          EDOMAIN);


	//int32_t a32[3]; int exp[3] = {10,11,12}; 
	//err=NumericArray(10,3,a32); affirm(err==0); check_array(a32,exp,3,__LINE__);

	AFFIRMNUMERICARRAY(int16_t,0,3,                 0,ARRAY(0,1,2));
	AFFIRMNUMERICARRAY(int16_t,-1,3,                0,ARRAY(-1,0,1));
	AFFIRMNUMERICARRAY(int16_t,SHRT_MAX-1,3,          EDOMAIN);

	AFFIRMNUMERICARRAY(int32_t,0,3,                 0,ARRAY(0,1,2));
	AFFIRMNUMERICARRAY(int32_t,-1,3,                0,ARRAY(-1,0,1));
	AFFIRMNUMERICARRAY(int32_t,INT_MAX-1,3,           EDOMAIN);

	AFFIRMNUMERICARRAY(double,0,3,                  0,ARRAY(0,1,2));
	AFFIRMNUMERICARRAY(double,1.1, 3,               0,ARRAY(1.1,2.1,3.1));
	AFFIRMNUMERICARRAY(double,-1.1, 3,              0,ARRAY(0+-1.1,1+-1.1,2+-1.1));

 	int32_t i32; err=ScalarAdd((int16_t)1,(int16_t)2,&i32); 	affirm(err==0); affirm(i32==3); 
 	int16_t i16; err=ScalarAdd((int16_t)SHRT_MAX,(int16_t)2,&i16);  affirm(err==EDOMAIN);
 	int8_t i8; err=ScalarAdd((int16_t)SCHAR_MAX,(int16_t)2,&i8);  affirm(err==EDOMAIN);

	err =  NoAPLFunction(L"Error exists but this is an invalid name"); affirm(err==-1);
	err =  NoAPLFunction(L"Error_exists_but_this_doesnt"); affirm(err==-1);
	err =  NoAPLFunction(L"none of this exists"); affirm(err==-1);

	err = Signal(1);	affirm(err==1);

	err = ReflectLengthShort();	affirm(err==ELENGTH);
	err = ReflectLengthLong();	affirm(err==ELENGTH);

#if !defined(_DEBUG)
	err = Signal(2);	affirm(err==2);
#endif

	{
	int32_t a[3]={'A','p','l'}; ; wchar_t exp[3] = {'A','p','l'}; wchar_t r[3];
	err=UCStoCHARArray(a,3,r,3); if (affirm(err==0)) check_array(r,exp,3,__LINE__);
	}

	{
	int32_t a[3]={97,98,99}; ; wchar_t exp[3] = {'a','b','c'}; wchar_t r[3];
	err=UCStoCHARArray(a,3,r,3); if (affirm(err==0)) check_array(r,exp,3,__LINE__);
	}

	{
	int32_t a[3]={97,98,99}; ; wchar_t exp[3] = {'a','b','c'}; wchar_t r[2];
	err=UCStoCHARArray(a,3,r,2); affirm(err==ELENGTH);
	}

	{
	int32_t a[1]={AV_QUAD}; ; char exp[1] = {0}; char r[1];
	err=UCStoCHARArray(a,1,r,1); affirm(err==EDOMAIN);
	}

	{
	char r; err=UCStoCHAR(AV_QUAD,&r); affirm(err==EDOMAIN);
	}
	{
	char r; err=UCStoCHAR('A',&r); if (affirm(err==0)) affirm(r=='A');
	}

	{
	wchar_t r; err=UCStoCHAR(AV_QUAD,&r); if (affirm(err==0)) affirm(r==(wchar_t)AV_QUAD);
	}

	{
	int32_t a[3]={97,98,99}; int32_t exp[3]; memcpy(exp,a,sizeof(a)); int32_t r[3];
	err=Reflect(a,3,r,3); if (affirm(err==0))	check_array(r,exp,3,__LINE__);
	}

	{
	int16_t a[3]={97,98,99}; ; int16_t exp[3]; memcpy(exp,a,sizeof(a)); int16_t r[3];
	err=Reflect(a,3,r,3); if (affirm(err==0))	check_array(r,exp,3,__LINE__);
	}

	{
	char *a = (char*)"john daintree",r[256]; size_t len = strlen(a);
	err=ReflectChar(a,0,AP_NULLTERM,r,len+1,AP_SIZED|AP_NULLTERM); 
	if (affirm(err==0)) check_array(r,a,len+1,__LINE__);
	}

	{
	char *a = (char*)"john daintree",r[256]; size_t len = strlen(a);
	err=ReflectChar(a,0,AP_NULLTERM,r,5,AP_SIZED|AP_NULLTERM); 
	affirm(err==ELENGTH);
	}

	{
	char *a = (char*)"john daintree",r[256]; size_t len = strlen(a);
	err=ReflectChar(a,0,AP_NULLTERM,r,len,AP_SIZED); 
	if (affirm(err==0)) check_array(r,a,len,__LINE__);
	}

	{
	wchar_t *a = (wchar_t *)L"john daintree",r[256]; size_t len = wcslen(a);
	err=ReflectChar(a,0,AP_NULLTERM,r,256,AP_SIZED|AP_NULLTERM); 
	if (affirm(err==0)) check_array(r,a,len+1,__LINE__);
	}

	{
	wchar_t *a = (wchar_t *)L"john daintree",r[256]; size_t len = wcslen(a);
	err=ReflectChar(a,0,AP_NULLTERM,r,len,AP_SIZED); 
	if (affirm(err==0)) check_array(r,a,len,__LINE__);
	}

	{
	ubyte *vp;
	wchar_t buf[256]; *buf=0;
	wchar_t *str = (wchar_t *)L"Hello World!!!!";
	err=SerializeAndAlloc(str,&vp); affirm(err==0);
	err=vp?Deserialize(buf,255,vp):-1;
	affirm(err==0); affirm(0==wcscmp(str,buf));
	}


	{
		wchar_t value[2048];
		wchar_t result[2048];
		err=GetEnv(L"USERNAME", value, 2048); affirm(err == 0);
		err = GetEnv(L"MAXWS", value, 2048); affirm(err == 0); affirm(0 == wcscmp(value, L"211Mb"));
		err = GetEnv(L"DOESNT_EXIST", value, 2048); affirm(err == 0); affirm(0 == *value);
		err = GetEnv(L"SESSION_FILE", value, 2048); affirm(err == 0); affirm(0 == wcscmp(value,L"dwa_test.dse"));
		err = GetEnv(L"USER_PARAM", value, 2048); affirm(err == 0); affirm(0 == wcscmp(value, L"user_param"));
#if defined(_MSC_VER)
		wchar_t expr[]={AV_QUAD,'W','A',0};
		err = Execute(expr, result, 2048); affirm(err == 0); int64_t WA = _wtol(result);
		affirm(WA < 211*1024*1024 && WA > 210*1024*1024);
#endif
	}


	

	{
		// persistent data
		wchar_t result[2049];
		wchar_t str[2049];
		wchar_t *expr;

		err = Execute(add_tid(L"GLOBAL%i",str,2048), result, 2048); affirm(err == 6);

		expr=add_tid(L"GLOBAL%i+'THIS_IS_A_TEST'",str,2048);  *wcsstr(expr,L"+")=AV_LEFT;
		err = Execute(expr,result, 2048); affirm(err == 0);
		err = Execute(add_tid(L"GLOBAL%i", str,2048), result, 2048); affirm(err == 0); affirm(0 == wcscmp(result, L"THIS_IS_A_TEST"));

		expr=add_tid(L"+EX'GLOBAL%i'", str,2048); *wcsstr(expr,L"+")=AV_QUAD;
		err = Execute(expr, result, 2048); affirm(err == 0);

		err = Execute(add_tid(L"GLOBAL%i", str,2048), result, 2048); affirm(err == 6);
		

	}

	return 0;
}

int  LIBCALL main(int argc, char *argv[])
{
	affirm(sizeof(int16_t) == sizeof(short));
	affirm(sizeof(int32_t) == sizeof(int));
	affirm(sizeof(int8_t) == sizeof(signed char));


#if __APPLE__
uselocale(newlocale(LC_CTYPE_MASK, "UTF-8", 0)); // set per-thread locale
#endif

#if defined(_MSC_VER)
	// CYGWIN issue: https://github.com/mintty/mintty/issues/218
	// doesn't change behaviour in CMD.EXE
	setvbuf(stdout, 0, _IONBF, 0);
#endif
	enable_asserts(0);
	wchar_t user_param[256];
	wcscpy(user_param,L"USER_PARAM=user_param");
	Start(1,user_param);
	wcscpy(user_param,L"overwritten");

#if defined(_MSC_VER)
#define THREAD_COUNT 5
	HANDLE threads[THREAD_COUNT];

	for (int i=0;i<THREAD_COUNT;i++)
		threads[i] = CreateThread(NULL, 0, run, NULL, 0, 0);
	
	if (THREAD_COUNT < WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE))
		RETN = 255; // something went wrong with the threads

#else
	run(NULL);
#endif


	printf("APL as a .so QAs completed. RETN=%i\n", RETN);

	return RETN;
}
