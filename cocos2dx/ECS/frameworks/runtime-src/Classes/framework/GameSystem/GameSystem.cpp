#include "GameSystem.h"

NS_GX_BEGIN

GameSystem *GameSystem::s_instance = nullptr;

GameSystem *GameSystem::getInstance()
{
	if (s_instance == nullptr)
	{
		new GameSystem();
	}
	GX_ASSERT(s_instance);

	if (s_instance)
	{
		s_instance->init();
	}

	return s_instance;
}

GameSystem::GameSystem()
{
	GX_ASSERT(!s_instance);
	s_instance = this; 
}

GameSystem::~GameSystem()
{
	GX_ASSERT(s_instance == this);
	s_instance = nullptr;
}

void GameSystem::init()
{

}

NS_GX_END
