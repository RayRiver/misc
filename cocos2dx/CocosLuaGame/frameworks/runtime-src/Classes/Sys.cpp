#include "Sys.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace Sys
{
	void sleep(int msec)
	{
#ifdef _WIN32
		::Sleep(static_cast<DWORD>(msec));
#else
		::usleep(static_cast<unsigned long>(msec * 1000));
#endif
	}
}
