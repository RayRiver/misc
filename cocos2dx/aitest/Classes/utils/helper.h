#ifndef helper_h__
#define helper_h__

#include <string>
#include <map>

#include "json/rapidjson.h"
#include "json/document.h"

#include "Fixed.h"

class helper
{
public:
	static void init();

	static void clampFixed(Fixed &arg, const Fixed &min, const Fixed &max);
	static Fixed randFixedInt(const Fixed &x, const Fixed &y);
	static Fixed randFixed();
	static Fixed randFixedClamped(); 

	// random functions;
	static int randInt(int x, int y); // x ~ y;
	static double randFloat(); // 0.0 ~ 1.0;
	static bool randBool();
	static double randClamped(); // -1.0 ~ 1.0;

	static const rapidjson::Value *getSetting(const char *key);
	static bool getBoolSetting(const char *key, bool defaultValue = false);
	static int getIntSetting(const char *key, int defaultValue = 0);
	static double getFloatSetting(const char *key, double defaultValue = 0.0);
	static const char *getStringSetting(const char *key, const char *defaultValue = helper::emptyString);

public:
	static const char *emptyString;

private:
	typedef std::map<std::string, const rapidjson::Value&> KVMap;
	typedef std::pair<std::string, const rapidjson::Value&> KVMapPair;

	static rapidjson::Document s_docSetting;
	static KVMap s_settingMap;

};

#endif // helper_h__
