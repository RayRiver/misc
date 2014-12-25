#ifndef Com_h__
#define Com_h__

#include "cocos2d.h"
#include "GXMacros.h"

NS_GX_BEGIN

class Entity;

class Com : public cocos2d::Ref
{
public:
	static Com *create(const std::string &type);

	inline const std::string &getType() const { return m_type; }
	Com *cloneEmpty() const;

protected:
	Com(const std::string &type);
	virtual ~Com();

	std::string m_type;

private:
	Entity *m_ownEntity;
};

NS_GX_END

#endif // Com_h__
