#ifndef ECSManager_h__
#define ECSManager_h__

#include "cocos2d.h"
#include "GXMacros.h"
#include "Entity.h"

NS_GX_BEGIN 

class ECSManager : public cocos2d::Ref
{
public:
	ECSManager();
	~ECSManager();

	Entity *createEntity();
	void removeEntity(Entity *entity);

private:
	entity_id_type generateNewEid();

	int m_lowestUnassignedEid;

	cocos2d::Vector<Entity *> m_addingList;
	cocos2d::Vector<Entity *> m_removingList;
};

NS_GX_END

#endif // ECSManager_h__
