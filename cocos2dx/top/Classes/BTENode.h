#ifndef BTENode_h__
#define BTENode_h__

#include "cocos2d.h"

#include "BTEResponder.h"

class BTENode : public BTEResponder
{
public:
	static BTENode *create(const std::string& filename);
	virtual bool initWithFile(const std::string& filename);

	virtual void onActivate();
	virtual void onInactivate();
	virtual void onAction(const cocos2d::Vec2 &last, const cocos2d::Vec2 &current);

};

#endif // BTENode_h__
