#ifndef ECSManager_h__
#define ECSManager_h__

#include <map>

#include "cocos2d.h"
#include "GXMacros.h"
#include "Entity.h"

NS_GX_BEGIN 

class Com;

class ECSManager : public cocos2d::Ref
{
public:
	static ECSManager *create();

	ECSManager();
	~ECSManager();

	Entity *createEntity();
	Entity *createEntity(const std::string &filename);
	void removeEntity(Entity *entity);

	void registerCom(Com *com);

private:
	entity_id_type generateNewEid();

	int m_lowestUnassignedEid;

	std::map<std::string, Com *> m_templateComs;	
};

NS_GX_END

#endif // ECSManager_h__
