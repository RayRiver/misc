#ifndef SweeperView_h__
#define SweeperView_h__

#include "cocos2d.h"

#include "utils/Fixed.h"

class SweeperObject;
class SweeperView : public cocos2d::Node
{
public:
	static SweeperView *create();

	void updatePosition(const FixedPoint &p);
	void updateSize(const FixedSize &size);
	void updateRotation(const Fixed &rotation);
	void updateFitness(const Fixed &n);

private:
	bool init();

private:
	cocos2d::DrawNode *m_drawnode;
	cocos2d::Label *m_label;

};

#endif // SweeperView_h__
