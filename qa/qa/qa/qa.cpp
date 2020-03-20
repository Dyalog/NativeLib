#include <wchar.h>

extern "C" {

#include "call_apl.h"
#include "dllmain.h"		// not defining our own DllMain

}

EXPORT int Start(unsigned int runtime,const wchar_t *user_param)
{
	const wchar_t *args[] = {
		L"MAXWS=211Mb",
		L"SESSION_FILE=dwa_test.dse",
		user_param

	};
return load_apl(runtime?ENGINE_F_RUNTIME:0,sizeof(args)/sizeof(args[0]),(wchar_t**)args);
}

EXPORT int LIBCALL enable_asserts(int enable)
{
return dwa_enable_asserts(enable);
}

#define QA_ARRAY_RESULT(name)	APL_##name##_ARRAY_RESULT
#define QA_SCALAR_PARAM(name)	APL_##name##_PARAM
#define QA_SCALAR_RESULT(name)	APL_##name##_RESULT
#define QA_ARRAY_PARAM(name)	APL_##name##_ARRAY_PARAM

#define NUMERIC_ARRAY(type,name)					\
EXPORT int LIBCALL NumericArray(double start, int32_t len, type *out) {	\
APL_DOUBLE_PARAM(Start,start); APL_INT32_PARAM(Len,len);			\
QA_ARRAY_RESULT(name)(Out,out,len,AP_SIZED);				\
return call_apl(L"NumericArray",&Start,&Len,&Out,PARAM_END); }

#define SCALAR_ADD(t1,n1,t2,n2,tr,nr)					\
EXPORT int LIBCALL ScalarAdd(t1 p1, t2 p2, tr *out) {;			\
QA_SCALAR_PARAM(n1)(P1,p1); QA_SCALAR_PARAM(n2)(P2,p2);			\
QA_SCALAR_RESULT(nr)(Out);						\
int err= call_apl(L"Add",&P1,&P2,&Out,PARAM_END);			\
*out = SCALAR_VAL(&Out,tr);						\
return err;}					

#define UCSTOCHARARRAY(tr,nr)						\
EXPORT int LIBCALL UCStoCHARArray(int32_t *p1,size_t len, tr *out, size_t olen) {	\
APL_INT32_ARRAY_PARAM(P1,p1,len); 						\
QA_ARRAY_RESULT(nr)(Out,out,olen,AP_SIZED);				\
return call_apl(L"UCS",&P1,&Out,PARAM_END);				}					

#define UCSTOCHAR(tr,nr)						\
EXPORT int LIBCALL UCStoCHAR(int32_t p1,tr *out) {			\
APL_INT32_PARAM(P1,p1); 							\
QA_SCALAR_RESULT(nr)(Out);						\
int err= call_apl(L"UCS",&P1,&Out,PARAM_END);				\
*out = SCALAR_VAL(&Out,tr); 						\
return err;}					

#define REFLECT(type,name)						\
EXPORT int LIBCALL Reflect(type *p1, size_t len, type *out, size_t olen) {	\
QA_ARRAY_PARAM(name)(P1,p1,len);					\
QA_ARRAY_RESULT(name)(Out,out,olen,AP_SIZED);				\
return call_apl(L"Reflect",&P1,&Out,PARAM_END); }

#define REFLECTCHAR(type,name)						\
EXPORT int LIBCALL ReflectChar(type *p1, size_t len,unsigned int iflags, type *out, size_t olen, unsigned int oflags) {	\
QA_ARRAY_PARAM(name)(P1,p1,len,iflags);					\
QA_ARRAY_RESULT(name)(Out,out,olen,oflags);				\
return call_apl(L"Reflect",&P1,&Out,PARAM_END); }

EXPORT int LIBCALL ReflectLengthShort(void)
{	
APL_INT32_PARAM(i1,0);
APL_INT32_RESULT(o1);
APL_INT32_RESULT(o2);
return call_apl(L"Reflect",&i1,&o1,&o2,PARAM_END);
}

EXPORT int LIBCALL ReflectLengthLong(void)
{	
int32_t args[] = {0,1,2,3};
APL_INT32_ARRAY_PARAM(i1,args,3);
APL_INT32_RESULT(o1);
APL_INT32_RESULT(o2);
return call_apl(L"Reflect",&i1,&o1,&o2,PARAM_END);
}




NUMERIC_ARRAY(int8_t,INT8);
NUMERIC_ARRAY(int16_t,INT16);
NUMERIC_ARRAY(int32_t,INT32);
NUMERIC_ARRAY(double,DOUBLE);

SCALAR_ADD(int16_t,INT16,int16_t,INT16,int32_t,INT32);
SCALAR_ADD(int16_t,INT16,int16_t,INT16,int16_t,INT16);
SCALAR_ADD(int16_t,INT16,int16_t,INT16,int8_t,INT8);

UCSTOCHARARRAY(char,CHAR);
UCSTOCHARARRAY(char16,CHAR16);
UCSTOCHARARRAY(char32,CHAR32);
UCSTOCHARARRAY(wchar_t,WCHAR);

UCSTOCHAR(char,CHAR);
UCSTOCHAR(char8,CHAR8);
UCSTOCHAR(char16,CHAR16);
UCSTOCHAR(wchar_t,WCHAR);

REFLECT(int8_t,INT8);
REFLECT(int16_t,INT16);
REFLECT(int32_t,INT32);

REFLECTCHAR(char,CHAR);
REFLECTCHAR(char8,CHAR8);
REFLECTCHAR(char16,CHAR16);
REFLECTCHAR(char32,CHAR32);
REFLECTCHAR(wchar_t,WCHAR);

EXPORT int LIBCALL NoAPLFunction(const wchar_t *name)
{
return call_apl(name,PARAM_END);
}

EXPORT int LIBCALL Signal(int n)
{
APL_INT32_PARAM(N,n);
return call_apl(L"Signal",&N,PARAM_END);
}

EXPORT int LIBCALL Error(int n)
{
APL_INT32_PARAM(N,n);
return call_apl(L"Error",&N,PARAM_END);
}

EXPORT int Deserialize(wchar_t *string,size_t len, ubyte *vp)
{
APL_ZFORMAT_PARAM(Z,vp);
APL_WCHAR_ARRAY_RESULT(S,string,len,AP_NULLTERM|AP_SIZED);
return call_apl(L"Reflect",&Z,&S,PARAM_END);
}

EXPORT int SerializeAndAlloc(wchar_t *string, ubyte **vp)
{
APL_WCHAR_ARRAY_PARAM(S,string,0,AP_NULLTERM);
APL_ZFORMAT_RESULT(Z,0,0,AP_ALLOC);
int retn = call_apl(L"Reflect",&S,&Z,PARAM_END);
*vp=ARRAY_PTR(&Z,ubyte);
return retn;
}

EXPORT int GetEnv(const wchar_t *name, wchar_t *value, size_t len)
{
APL_WCHAR_ARRAY_PARAM(N,(wchar_t*)name,0,AP_NULLTERM);
APL_WCHAR_ARRAY_RESULT(R,value,len,AP_NULLTERM|AP_SIZED);
return call_apl(L"GetEnv",&N,&R,PARAM_END);
}

EXPORT int Execute(wchar_t *name, wchar_t *value, size_t len)
{
	APL_WCHAR_ARRAY_PARAM(N, name, 0, AP_NULLTERM);
	APL_WCHAR_ARRAY_RESULT(R, value, len, AP_NULLTERM | AP_SIZED);
	return call_apl(L"Execute", &N, &R, PARAM_END);
}
