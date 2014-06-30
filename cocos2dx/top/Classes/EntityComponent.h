#ifndef EntityComponent_h__
#define EntityComponent_h__

#include "cocos2d.h"

class EntityComponent : public cocos2d::Component 
{
public:
	EntityComponent();
	virtual ~EntityComponent();

	CREATE_FUNC(EntityComponent);

};

#endif // EntityComponent_h__
