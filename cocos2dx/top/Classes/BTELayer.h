#ifndef BTELayer_h__
#define BTELayer_h__

#include <vector>

#include "cocos2d.h"

class BTEResponder;
class BTELayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(BTELayer);

	virtual bool init();

	bool touchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	inline bool isTouchActive() { return m_activeResponder!=nullptr; }

	void registerResponder(BTEResponder *responder);
	BTEResponder *getActiveResponder(const cocos2d::Vec2 &point);

protected:
	typedef std::vector<BTEResponder *> ResponderList;
	ResponderList m_responders;

	BTEResponder *m_activeResponder;
};

#endif // BTELayer_h__
