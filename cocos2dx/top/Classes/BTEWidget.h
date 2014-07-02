#ifndef BTEWidget_h__
#define BTEWidget_h__

#include "cocos2d.h"

#include "BTEResponder.h"

class BTENode;
class BTEWidget : public BTEResponder
{
public:
	static BTEWidget *create(const std::string& filename);
	virtual bool initWithFile(const std::string& filename);

	virtual void onActivate();
	virtual void onInactivate();
	virtual void onAction(const cocos2d::Vec2 &last, const cocos2d::Vec2 &current);

private:
	BTENode *m_forkNode;
};

#endif // BTEWidget_h__
