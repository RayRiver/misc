#include "Config.h"

using namespace std;
USING_NS_CC;

Config::Config()
{

}

Config::~Config()
{

}

bool Config::init( const char *configid )
{
	string file = "config/";
	file = file + configid + ".json";
	file = FileUtils::getInstance()->fullPathForFilename(file);

	string data = FileUtils::getInstance()->getStringFromFile(file);	
	m_root.Parse<0>(data.c_str());
	if (m_root.HasParseError())	
	{
		CCASSERT(false, "");
		return false;
	}

	return true;
}

void Config::read( const char *key, int &val )
{
	val = cocostudio::DictionaryHelper::getInstance()->getIntValue_json(m_root, key);
}

void Config::read( const char *key, float &val )
{
	val = cocostudio::DictionaryHelper::getInstance()->getFloatValue_json(m_root, key);
}

void Config::read( const char *key, std::string &val )
{
	val = cocostudio::DictionaryHelper::getInstance()->getStringValue_json(m_root, key);
}

ConfigManager * ConfigManager::getInstance()
{
	static ConfigManager obj;
	return &obj;
}

ConfigManager::ConfigManager()
{

}

ConfigManager::~ConfigManager()
{
	for (CONFIG_MAP::iterator it=m_configs.begin(); it!=m_configs.end(); ++it)
	{
		if (it->second)
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	m_configs.clear();
}

Config *ConfigManager::load( const char *configid )
{
	Config *config = nullptr;
	CONFIG_MAP::iterator it = m_configs.find(configid);
	if (it == m_configs.end())
	{
		config = new Config();
		config->init(configid);
		m_configs.insert(pair<string, Config *>(configid, config));
	}
	else
	{
		config = it->second;
	}
	CCASSERT(config, "config == nullptr");
	return config;
}

void ConfigManager::read( const char *configid, const char *key, int &val )
{
	auto config = this->load(configid);
	config->read(key, val);	
}

void ConfigManager::read( const char *configid, const char *key, float &val )
{
	auto config = this->load(configid);
	config->read(key, val);	
}

void ConfigManager::read( const char *configid, const char *key, std::string &val )
{
	auto config = this->load(configid);
	config->read(key, val);	
}
