#ifndef Log_h__
#define Log_h__

extern bool g_bLogEnable;
void LogEnable(bool bEnable);

#ifdef _WIN32
# include <stdio.h>
# define Log(fmt, ...) if (g_bLogEnable) printf(fmt"\n", __VA_ARGS__)
# define LogFormat(fmt, ...) if (g_bLogEnable) printf(fmt, __VA_ARGS__)
#else
# define Log(fmt, ...)
# define LogFormat(fmt, ...)
#endif

void LogHex(char *buffer, size_t len);

#endif // Log_h__
