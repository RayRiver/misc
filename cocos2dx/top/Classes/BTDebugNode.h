#ifndef BTDebugNode_h__
#define BTDebugNode_h__

#include "cocos2d.h"

#include "BTDef.h"

class BTNode;
class BTDebugRenderer;
class BTDebugNode : public cocos2d::Node
{
public:
	static BTDebugNode *create(BTNode *btnode, BTDebugNode *prevDebugNode);
	virtual bool init(BTNode *btnode, BTDebugNode *prevDebugNode);

	void drawNode(BTNodeEvent event, bool isActionNode);
	void sendEvent(BTNodeEvent event);

private:
	BTNode *m_btnode;
	cocos2d::DrawNode *m_drawNode;
	BTDebugNode *m_prev;
};

#endif // BTDebugNode_h__
