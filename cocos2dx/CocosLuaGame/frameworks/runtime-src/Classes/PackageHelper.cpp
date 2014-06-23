// add for resource pack by R.R.

#include "PackageHelper.h"

#include <string>

#include "CCLuaEngine.h"
#include "cocos2d.h"
#include "ConfigParser.h"
#include "xxtea/XXTEAUtil.h"

USING_NS_CC;

#define SCRIPT_PACKAGE "resource/game.zip"

void PackageHelper::startScript()
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(SCRIPT_PACKAGE);
	if (FileUtils::getInstance()->isFileExist(fullPath))
	{
		const char *key = "MYKEY";
		const char *sign = "XXTEA";
		XXTEAUtil::getInstance()->setXXTEAKeyAndSign(key, strlen(key), sign, strlen(sign));
		LuaEngine::getInstance()->getLuaStack()->loadChunksFromZIP("resource/game.zip");
		LuaEngine::getInstance()->executeString("require 'main'");
	}
	else
	{
		LuaEngine::getInstance()->executeScriptFile(ConfigParser::getInstance()->getEntryFile().c_str());
	}
}

