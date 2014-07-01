#ifndef BTDebugRenderer_h__
#define BTDebugRenderer_h__

#include <vector>

#include "cocos2d.h"

#include "BTNode.h"
#include "BTDebugNode.h"

class BTDebugRenderer : public cocos2d::Layer
{
private:
	struct NodeInfo
	{
	public:
		BTNode *btNode;
		BTDebugNode *debugNode;
		BTDebugNode *prevDebugNode;
		NodeInfo() : btNode(nullptr), debugNode(nullptr), prevDebugNode(nullptr) {}
	};
	typedef std::vector<NodeInfo> NodeList;

public:
	BTDebugRenderer();
	~BTDebugRenderer();

	static BTDebugRenderer *create(BTNode *root);
	virtual bool init(BTNode *root);

	void initNodes(NodeList &nodes, float origin_x);
	inline cocos2d::DrawNode *getDrawNode() { return m_drawNode; }

	void render();

private:
	cocos2d::DrawNode *m_drawNode;
	BTNode *m_btroot;
};

#endif // BTDebugRenderer_h_
