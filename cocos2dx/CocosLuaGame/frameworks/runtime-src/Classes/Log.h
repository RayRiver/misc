#ifndef Log_h__
#define Log_h__

extern bool g_bLogEnable;
void LogEnable(bool bEnable);

#ifdef _WIN32
# include <stdio.h>
# define Log(fmt, ...) if (g_bLogEnable) CCLOG(fmt, __VA_ARGS__)
#else
# define Log(fmt, ...)
#endif

void LogHex(char *buffer, size_t len);

#endif // Log_h__
