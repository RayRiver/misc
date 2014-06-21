#include "XXTEAUtil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xxtea.h"

XXTEAUtil *XXTEAUtil::s_instance = nullptr;

XXTEAUtil * XXTEAUtil::getInstance()
{
	if (!s_instance)
	{
		s_instance = new XXTEAUtil;
	}
	return s_instance;
}

XXTEAUtil::XXTEAUtil()
	: m_xxteaEnabled(false)
	, m_xxteaKey(nullptr)
	, m_xxteaKeyLen(0)
	, m_xxteaSign(nullptr)
	, m_xxteaSignLen(0)
{

}

XXTEAUtil::~XXTEAUtil()
{
	if (m_xxteaKey) free(m_xxteaKey);
	if (m_xxteaSign) free(m_xxteaSign);
}

void XXTEAUtil::setXXTEAKeyAndSign( const char *key, int keyLen, const char *sign, int signLen )
{
	cleanupXXTEAKeyAndSign();

	if (key && keyLen && sign && signLen)
	{
		m_xxteaKey = (char*)malloc(keyLen);
		memcpy(m_xxteaKey, key, keyLen);
		m_xxteaKeyLen = keyLen;

		m_xxteaSign = (char*)malloc(signLen);
		memcpy(m_xxteaSign, sign, signLen);
		m_xxteaSignLen = signLen;

		m_xxteaEnabled = true;
	}
	else
	{
		m_xxteaEnabled = false;
	}
}

void XXTEAUtil::cleanupXXTEAKeyAndSign( void )
{
	if (m_xxteaKey)
	{
		free(m_xxteaKey);
		m_xxteaKey = NULL;
		m_xxteaKeyLen = 0;
	}
	if (m_xxteaSign)
	{
		free(m_xxteaSign);
		m_xxteaSign = NULL;
		m_xxteaSignLen = 0;
	}
}

unsigned char * XXTEAUtil::decrypt( unsigned char *buffer, int size, int &outlen )
{
	xxtea_long len = 0;
	unsigned char *outbuffer = xxtea_decrypt(buffer + m_xxteaSignLen,
		(xxtea_long)size - (xxtea_long)m_xxteaSignLen,
		(unsigned char*)m_xxteaKey,
		(xxtea_long)m_xxteaKeyLen,
		&len);
	outlen = (int)len;
	return outbuffer;
}
