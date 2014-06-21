#ifndef XXTEAUtil_h__
#define XXTEAUtil_h__

class XXTEAUtil
{
private:
	XXTEAUtil();
	static XXTEAUtil *s_instance;

public:
	virtual ~XXTEAUtil();

	static XXTEAUtil *getInstance();

	void setXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);
	void cleanupXXTEAKeyAndSign(void);

	inline bool isEnable() { return m_xxteaEnabled; }
	inline const char *getSign() { return m_xxteaSign; }
	inline int getSignLen() { return m_xxteaSignLen; }

	unsigned char *decrypt(unsigned char *buffer, int size, int &outlen);
	bool isXXTEA(unsigned char *data, int size);

	bool  m_xxteaEnabled;
	char *m_xxteaKey;
	int   m_xxteaKeyLen;
	char *m_xxteaSign;
	int   m_xxteaSignLen;
};

#endif // XXTEAUtil_h__
