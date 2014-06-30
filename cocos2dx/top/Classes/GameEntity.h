#ifndef GameEntity_h__
#define GameEntity_h__

#include <string>
#include <map>

#include "cocos2d.h"

class GameEntity : public cocos2d::Node 
{
public:
	GameEntity();
	virtual ~GameEntity();

	CREATE_FUNC(GameEntity);


};

#endif // GameEntity_h__
