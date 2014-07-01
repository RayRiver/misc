#ifndef Utils_h__
#define Utils_h__

#include <string>
#include <map>

#include "json/rapidjson.h"
#include "json/document.h"

class Utils
{
public:
	static bool init();

	static const char *gettext(const char *text); 

	static bool getGlobalSettingBoolean(const char *key, bool defaultValue = false); 
	static int getGlobalSettingInt(const char *key, int defaultValue = 0); 
	static float getGlobalSettingFloat(const char *key, float defaultValue = 0.0f); 
	static const char *getGlobalSettingString(const char *key, const char *defaultValue = Utils::emptyString); 

public:
	static const char *emptyString;

private:
	static Utils *getInstance();
	static Utils *s_instance;
	Utils();
	~Utils();

	typedef std::map<std::string, const rapidjson::Value&> KVMap;
	typedef std::pair<std::string, const rapidjson::Value&> KVMapPair;

	bool _init();
	bool _loadConfig(const char *filename, rapidjson::Document &doc, KVMap &kvmap, bool &bLoaded);
	const rapidjson::Value *_gettext(const char *key);
	const rapidjson::Value *_getGlobalSetting(const char *key);

private:
	bool m_bTextLoaded;
	bool m_bGlobalSettingLoaded;
	rapidjson::Document m_docText;
	rapidjson::Document m_docGlobalSetting;
	KVMap m_textMap;
	KVMap m_globalSettingMap;
};

#endif // Utils_h__
