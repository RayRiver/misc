#ifndef BTDebugNode_h__
#define BTDebugNode_h__

#include "cocos2d.h"

class BTNode;
class BTDebugRenderer;
class BTDebugNode : public cocos2d::Node
{
public:
	static BTDebugNode *create(BTNode *btnode);
	virtual bool init(BTNode *btnode);

private:
	BTNode *m_btnode;
};

#endif // BTDebugNode_h__
