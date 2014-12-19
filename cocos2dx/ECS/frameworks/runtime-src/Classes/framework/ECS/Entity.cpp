#include "Entity.h"

USING_NS_CC;

NS_GX_BEGIN

Entity::Entity()
{

}

Entity::~Entity()
{

}

Entity * Entity::createWithId(const entity_id_type &id)
{
	Entity *entity = new Entity();
	if (entity)
	{
		entity->initWithId(id);
		return entity;
	}

	return nullptr;
}

void Entity::initWithId(const entity_id_type &id)
{
	m_id = id;	
	log("Entity: %d be created", m_id);
}

void Entity::sendEvent(const std::string &eventName)
{

}

NS_GX_END
