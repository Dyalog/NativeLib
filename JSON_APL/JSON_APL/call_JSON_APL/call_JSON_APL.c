#if defined(_MSC_VER)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <xlocale.h>
#endif
#include <stdio.h>
#include <wchar.h>

#if _MSC_VER
#define LIBCALL __cdecl
#else
#define LIBCALL
#endif

#define AV_QUAD 0x2395
#define AV_FMT 0x2355

extern int LIBCALL Initialise(unsigned int runtime, unsigned int len, wchar_t **args);
extern int LIBCALL ExecAPL(wchar_t *statement, wchar_t *result);
extern int LIBCALL CallJSON(wchar_t *function, wchar_t *in, wchar_t *out, unsigned int len);
extern int LIBCALL GetEnv(const wchar_t *name, wchar_t *value, size_t len);

int run(void *ignore)
{
	#ifdef __APPLE__
	uselocale(newlocale(LC_CTYPE_MASK, "UTF-8", 0));
	#endif
	wchar_t buf[256];
	wchar_t APL[256];
	wchar_t *text = L"Hello there APL";
	int err;
	// Execute wchar APL statement (expects  char return so format required):

	wcscpy(APL,L" +/1 2 3 4"); APL[0]=AV_FMT;
	err = ExecAPL(APL, buf);
	wprintf(L"ExecAPL: %ls\n%ls\nError: %i\n", APL+1, buf, err);
	// LENGTH ERROR
	wcscpy(APL, L" 1 2 + 3 4 5"); APL[0]=AV_FMT;
	err = ExecAPL(APL, buf);
	wprintf(L"ExecAPL: %ls\n%ls\nError: %i\n", APL+1, buf, err);
	// Execute an APL function called using JSON
	wcscpy(APL,L"{\"Left\":[1,0,1,1,0],\"Function\":\"/\",\"Right\":\"APPLE\"}");
	err = CallJSON(L"Exec", APL, buf, 256);
	wprintf(L"CallJSON Exec: %ls\nError: %i\n", buf, err);
	// Load a .dyalog script
	wcscpy(APL,L"\"sign.dyalog\"");
	err = CallJSON(L"Load", APL, buf, 256);
	wprintf(L"CallJSON Load: %ls\nError: %i\n", buf, err);
	// Execute a function from loaded script using JSON
	err = CallJSON(L"GetSign", L"[1,24]", buf, 256);
	wprintf(L"CallJSON GetSign 1 24: %ls\nError:%i\n", buf, err);
	// Query available workspace (expects char return so format required)
	wcscpy(APL,L"  WA");  APL[0]=AV_FMT; APL[1]=AV_QUAD;
	err = ExecAPL(APL, buf);
	wprintf(L"WA: %ls\nError:%i\n", buf, err);
	// Query MAXWS
	err = GetEnv(L"MAXWS", buf, 256);
	wprintf(L"GetEnv MAXWS: %ls\nError: %i\n", buf, err);
	// Query SESSION_FILE
	err = GetEnv(L"SESSION_FILE", buf, 256);
	wprintf(L"GetEnv Session file: %ls\nError: %i\n", buf, err);
	return 0;
}

#if defined(_MSC_VER)
int __cdecl main(int argc, char *argv[])
#else
int         main(int argc, char *argv[])
#endif
{
	wchar_t *WSargs[] = {
		L"MAXWS=256Mb",
		L"SESSION_FILE=JSON_APL.dse"
	};
	Initialise(1, sizeof(WSargs) / sizeof(WSargs[0]), WSargs);
	run(NULL);
	return 0;
}
