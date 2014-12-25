#ifndef Entity_h__
#define Entity_h__

#include "cocos2d.h"
#include "GXMacros.h"

typedef int32_t entity_id_type;

NS_GX_BEGIN

class Entity : public cocos2d::Ref
{
public:
	void sendEvent(const std::string &eventName);

private:
	Entity();
	virtual ~Entity();

	static Entity *createWithId(const entity_id_type &id);
	void initWithId(const entity_id_type &id);

	inline const entity_id_type &getId() { return m_id; }

	entity_id_type m_id;

public:
	friend class ECSManager;
};

NS_GX_END

#endif // Entity_h__
