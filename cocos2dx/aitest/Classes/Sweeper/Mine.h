#ifndef Mine_h__
#define Mine_h__

#include "cocos2d.h"

#include "utils/Fixed.h"

class Mine : public cocos2d::Node
{
public:
	CREATE_FUNC(Mine);

	inline const FixedVec2 &getFixedPosition() const { return m_fixedPosition; }
	inline void setFixedPosition(const FixedVec2 &p) { m_fixedPosition = p; setPosition((float)p.x, (float)p.y); }

private:
	bool init();

private:
	FixedVec2 m_fixedPosition;

};

#endif // Mine_h__
