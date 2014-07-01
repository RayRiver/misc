#include "Utils.h"

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

USING_NS_CC;

const char *Utils::emptyString = "";

Utils *Utils::s_instance = nullptr;
Utils * Utils::getInstance()
{
	if (!s_instance)
	{
		s_instance = new Utils();
	}
	return s_instance;
}

Utils::Utils()
	: m_bTextLoaded(false)
	, m_bGlobalSettingLoaded(false)
{

}

Utils::~Utils()
{

}

bool Utils::_init()
{
	if (!_loadConfig("config/text.json", m_docText, m_textMap, m_bTextLoaded)) return false;
	if (!_loadConfig("config/global_setting.json", m_docGlobalSetting, m_globalSettingMap, m_bGlobalSettingLoaded)) return false;
	return true;
}

bool Utils::_loadConfig(const char *filename, rapidjson::Document &doc, KVMap &kvmap, bool &bLoaded)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
	std::string fileContent = FileUtils::getInstance()->getStringFromFile(fullPath);

	doc.Parse<0>(fileContent.c_str());
	if (doc.HasParseError()) {
		CCLOG("GetParseError %s\n", doc.GetParseError());
		return false;
	}

	for (rapidjson::Value::ConstMemberIterator it=doc.MemberonBegin(); it!=doc.MemberonEnd(); ++it)
	{
		const auto &member = *it;
		const char *name = member.name.GetString();
		const rapidjson::Value &val = member.value;
		kvmap.insert(Utils::KVMapPair(name, val));
	}

	bLoaded = true;
	return true;
}

const rapidjson::Value * Utils::_gettext(const char *key)
{
	KVMap::const_iterator it = m_textMap.find(key);
	if (it != m_textMap.end())
	{
		const rapidjson::Value &findVal = it->second;
		return &findVal;
	}
	else
	{
		return nullptr;
	}
}

const rapidjson::Value * Utils::_getGlobalSetting(const char *key)
{
	KVMap::const_iterator it = m_globalSettingMap.find(key);
	if (it != m_globalSettingMap.end())
	{
		const rapidjson::Value &findVal = it->second;
		return &findVal;
	}
	else
	{
		return nullptr;
	}
}

bool Utils::init()
{
	return Utils::getInstance()->_init();
}

const char * Utils::gettext( const char *text )
{
	const rapidjson::Value *val = Utils::getInstance()->_gettext(text);
	if (val)
	{
		return val->GetString();
	}
	else
	{
		return text;
	}
}

bool Utils::getGlobalSettingBoolean( const char *key, bool defaultValue /*= false*/ )
{
	const rapidjson::Value *val = Utils::getInstance()->_getGlobalSetting(key);
	if (val)
	{
		return val->GetBool();
	}
	else
	{
		return defaultValue;
	}
}

int Utils::getGlobalSettingInt( const char *key, int defaultValue /*= 0*/ )
{
	const rapidjson::Value *val = Utils::getInstance()->_getGlobalSetting(key);
	if (val)
	{
		return val->GetInt();
	}
	else
	{
		return defaultValue;
	}
}

float Utils::getGlobalSettingFloat( const char *key, float defaultValue /*= 0.0f*/ )
{
	const rapidjson::Value *val = Utils::getInstance()->_getGlobalSetting(key);
	if (val)
	{
		return (float)val->GetDouble();
	}
	else
	{
		return defaultValue;
	}
}

const char * Utils::getGlobalSettingString( const char *key, const char *defaultValue /*= emptyString*/ )
{
	const rapidjson::Value *val = Utils::getInstance()->_getGlobalSetting(key);
	if (val)
	{
		return val->GetString();
	}
	else
	{
		return defaultValue;
	}
}
