#ifndef BTEResponder_h__
#define BTEResponder_h__

#include "cocos2d.h"

class BTEResponder : public cocos2d::Sprite
{
public:
	static BTEResponder *create(const std::string& filename);
	virtual bool initWithFile(const std::string& filename);

	virtual void onActivate();
	virtual void onInactivate();
	virtual void onAction(const cocos2d::Vec2 &last, const cocos2d::Vec2 &current);
};

#endif // BTEResponder_h__
