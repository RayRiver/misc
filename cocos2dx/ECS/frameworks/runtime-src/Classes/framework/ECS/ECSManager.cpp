#include "ECSManager.h"

#include "json/rapidjson.h"
#include "json/document.h"

#include "Com.h"

USING_NS_CC;

NS_GX_BEGIN

ECSManager *ECSManager::create()
{
	return new ECSManager;
}

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

	return entity;
}

Entity * ECSManager::createEntity(const std::string &filename)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filename);
	std::string fileContent = FileUtils::getInstance()->getStringFromFile(fullPath);
	
	rapidjson::Document doc;
	doc.Parse<0>(fileContent.c_str());
	if (doc.HasParseError())
	{
		log("JSON parse error %s", doc.GetParseError());
		return nullptr;
	}

	rapidjson::Value &root = doc;
	if (root.IsNull() || root.Size() == 0)
	{
		log("JSON root is null or size is zero");
		return nullptr;
	}

	Entity *entity = createEntity();
	log("Create entity %d with filename %s", entity->getId(), filename.c_str());
	
	int count = root.Size();
	for (int i=0; i<count; ++i)
	{
		rapidjson::Value &comValue = root[i];
		if (comValue.IsNull())
		{
			continue;
		}

		const char *type = comValue["type"].GetString();
		auto it = m_templateComs.find(type);
		if (it == m_templateComs.end())
		{
			continue;
		}

		Com *com = it->second->cloneEmpty();
	}


}

void ECSManager::removeEntity(Entity *entity)
{
	if (entity == nullptr)
	{
		return;
	}
}

entity_id_type ECSManager::generateNewEid()
{
	if (m_lowestUnassignedEid < UINT32_MAX)
	{
		return m_lowestUnassignedEid++;
	}
	return 0;
}

void ECSManager::registerCom(Com *com)
{
	std::string name = com->getType();
	if (m_templateComs.find(name) == m_templateComs.end())
	{
		m_templateComs.insert(std::make_pair(name, com));
	}
}

NS_GX_END
