#ifndef Config_h__
#define Config_h__

#include <string>
#include <map>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "json/reader.h"

class Config
{
public:
	Config();
	virtual ~Config();

	bool init(const char *configid);

	void read(const char *key, int &val);
	void read(const char *key, float &val);
	void read(const char *key, std::string &val);

private:
	rapidjson::Document m_root;
};

class ConfigManager
{
public:
	virtual ~ConfigManager();

	static ConfigManager *getInstance(); 

	Config *load(const char *configid);

	void read(const char *configid, const char *key, int &val);
	void read(const char *configid, const char *key, float &val);
	void read(const char *configid, const char *key, std::string &val);

private:
	ConfigManager();

	typedef std::map<std::string, Config *> CONFIG_MAP;
	CONFIG_MAP m_configs;

};

//#define CONFIG ConfigManager::getInstance();
#define LOAD_CONFIG(configid) ConfigManager::getInstance()->load(configid)
#define READ_CONFIG(configid, key, val) ConfigManager::getInstance()->read(configid, key, val)

#endif // Config_h__