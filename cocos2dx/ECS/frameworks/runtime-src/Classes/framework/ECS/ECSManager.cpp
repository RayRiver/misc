#include "ECSManager.h"

NS_GX_BEGIN

ECSManager::ECSManager()
{

}

ECSManager::~ECSManager()
{

}

Entity * ECSManager::createEntity()
{
	entity_id_type id = this->generateNewEid();
	Entity *entity = Entity::createWithId(id);

	this->m_addingList.pushBack(entity);

	return entity;
}

void ECSManager::removeEntity(Entity *entity)
{
	if (entity == nullptr)
	{
		return;
	}

	this->m_removingList.pushBack(entity);
}

entity_id_type ECSManager::generateNewEid()
{
	if (m_lowestUnassignedEid < UINT32_MAX)
	{
		return m_lowestUnassignedEid++;
	}
	return 0;
}

NS_GX_END
