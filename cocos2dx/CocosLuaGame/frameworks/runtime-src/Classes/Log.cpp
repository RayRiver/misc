#include "Log.h"

#include <string.h>

#include "cocos2d.h"

bool g_bLogEnable = true;
void LogEnable( bool bEnable )
{
	g_bLogEnable = bEnable;
}

void LogHex( char *buffer, size_t len )
{
	if (!g_bLogEnable) return;

	CCLOG("=======================================================================");
	CCLOG("HEX START:-00-01-02-03-04-05-06-07-|-08-09-0a-0b-0c-0d-0e-0f");
	char content[8192];
	memset(content, 0, sizeof(content));
	for (size_t i=0; i<len; ++i)	
	{
		if (i==0 || i%16==0)
		{
			char s[16];
			sprintf(s, "%08xh: ", buffer+i);
			if (i!=0) strcat(content, "\n");
			strcat(content, s);
		}
		else if (i%8 == 0)
		{
			strcat(content, " | ");
		}
		else
		{
			strcat(content, " ");
		}

		char s[16];
		sprintf(s, "%02x", (unsigned char)buffer[i]);
		strcat(content, s);
		//CCLOG("%02x", (unsigned char)buffer[i]);
	}
	CCLOG("%s", content);
	CCLOG("=======================================================================\n");
}

