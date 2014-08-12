#ifndef MineView_h__
#define MineView_h__

#include "cocos2d.h"

#include "utils/Fixed.h"

class MineView : public cocos2d::Node
{
public:
	CREATE_FUNC(MineView);

	void updatePosition(const FixedPoint &p);

private:
	bool init();

private:
	FixedVec2 m_fixedPosition;

};

#endif // MineView_h__
