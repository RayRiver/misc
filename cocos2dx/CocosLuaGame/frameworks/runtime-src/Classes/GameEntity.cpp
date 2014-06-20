#include "GameEntity.h"

USING_NS_CC;

GameEntity* GameEntity::create()
{
	 auto pRet = new (std::nothrow) GameEntity();
	if (pRet && pRet->init())
	{
		pRet->scheduleUpdate();
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

GameEntity::GameEntity()
{

}

GameEntity::~GameEntity()
{

}
