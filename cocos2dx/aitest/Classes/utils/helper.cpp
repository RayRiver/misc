#include "helper.h"

#include <stdlib.h>

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "editor-support/cocostudio/DictionaryHelper.h"

USING_NS_CC;

const char *helper::emptyString = "";

rapidjson::Document helper::s_docSetting;
helper::KVMap helper::s_settingMap;

void helper::init()
{
	srand(time(NULL));

	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("config/settings.json");
	std::string fileContent = FileUtils::getInstance()->getStringFromFile(fullPath);

	s_docSetting.Parse<0>(fileContent.c_str());
	if (s_docSetting.HasParseError()) {
		CCLOG("GetParseError %s\n", s_docSetting.GetParseError());
		return;
	}

	for (rapidjson::Value::ConstMemberIterator it=s_docSetting.MemberonBegin(); it!=s_docSetting.MemberonEnd(); ++it)
	{
		const auto &member = *it;
		const char *name = member.name.GetString();
		const rapidjson::Value &val = member.value;
		s_settingMap.insert(helper::KVMapPair(name, val));
	}
}

void helper::clampFixed( Fixed &arg, const Fixed &min, const Fixed &max )
{
	if (arg < min)
	{
		arg = min;
	}
	if (arg > max)
	{
		arg = max;
	}
}

Fixed helper::randFixedInt( const Fixed &x, const Fixed &y )
{
	int ix = (int)x;
	int iy = (int)y;
	return (rand() % (iy-ix+1) + ix);
}

Fixed helper::randFixed()
{
	return Fixed(rand()) / (Fixed(RAND_MAX) + Fixed(1.0));
}

Fixed helper::randFixedClamped()
{
	return randFixed() - randFixed();
}

int helper::randInt( int x, int y )
{
	return (rand() % (y-x+1) + x);
}

double helper::randFloat()
{
	return (rand() / (RAND_MAX + 1.0));
}

bool helper::randBool()
{
	if (helper::randInt(0,1)) return true;
	else return false;
}

double helper::randClamped()
{
	return randFloat() - randFloat();
}

const rapidjson::Value * helper::getSetting( const char *key )
{
	KVMap::const_iterator it = s_settingMap.find(key);
	if (it != s_settingMap.end())
	{
		const rapidjson::Value &findVal = it->second;
		return &findVal;
	}
	else
	{
		return nullptr;
	}
}

bool helper::getBoolSetting( const char *key, bool defaultValue /*= false*/ )
{
	const rapidjson::Value *val = getSetting(key);
	if (val)
	{
		return val->GetBool();
	}
	else
	{
		return defaultValue;
	}
}

int helper::getIntSetting( const char *key, int defaultValue /*= 0*/ )
{
	const rapidjson::Value *val = getSetting(key);
	if (val)
	{
		return val->GetInt();
	}
	else
	{
		return defaultValue;
	}
}

double helper::getFloatSetting( const char *key, double defaultValue /*= 0.0*/ )
{
	const rapidjson::Value *val = getSetting(key);
	if (val)
	{
		return (float)val->GetDouble();
	}
	else
	{
		return defaultValue;
	}
}

const char * helper::getStringSetting( const char *key, const char *defaultValue /*= emptyString*/ )
{
	const rapidjson::Value *val = getSetting(key);
	if (val)
	{
		return val->GetString();
	}
	else
	{
		return defaultValue;
	}
}

