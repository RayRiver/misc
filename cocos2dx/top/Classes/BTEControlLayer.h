#ifndef BTEControlLayer_h__
#define BTEControlLayer_h__

#include "cocos2d.h"

#include "BTELayer.h"

class BTEControlLayer : public BTELayer
{
public:
	CREATE_FUNC(BTEControlLayer);

	virtual bool init();

	inline cocos2d::Node *getDraggingNode() { return m_draggingNode; }

private:
	cocos2d::Node *m_draggingNode;

	bool m_bDaggingLayer;
};

#endif // BTEControlLayer_h__
