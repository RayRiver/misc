#include "Log.h"

#include <string.h>

bool g_bLogEnable = true;
void LogEnable( bool bEnable )
{
	g_bLogEnable = bEnable;
}

void LogHex( char *buffer, size_t len )
{
	if (!g_bLogEnable) return;

	printf("=======================================================================\n");
	printf("HEX START:-00-01-02-03-04-05-06-07-|-08-09-0a-0b-0c-0d-0e-0f");
	for (size_t i=0; i<len; ++i)	
	{
		if (i==0 || i%16==0)
		{
			printf("\n%08xh: ", i);
		}
		else if (i%8 == 0)
		{
			printf(" | ");
		}
		else
		{
			printf(" ");
		}

		printf("%02x", (unsigned char)buffer[i]);

	}
	printf("\n=======================================================================\n\n");
}

