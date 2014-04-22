#include "ScriptInterface.h"
#include "Sys.h"

void sys_sleep(int msec)
{
	Sys::sleep(msec);
}