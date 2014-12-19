#ifndef GameSystem_h__
#define GameSystem_h__

#include "GXMacros.h"

#include "cocos2d.h"

NS_GX_BEGIN

class GameSystem : public cocos2d::Ref
{
public:
	virtual ~GameSystem();
	static GameSystem *getInstance();

	virtual void init();

protected:
	GameSystem();
	static GameSystem *s_instance;

};

NS_GX_END

#endif // GameSystem_h__
