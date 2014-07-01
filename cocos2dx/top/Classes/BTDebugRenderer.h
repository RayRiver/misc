#ifndef BTDebugRenderer_h__
#define BTDebugRenderer_h__

#include <vector>
#include <map>

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
	typedef std::vector<BTNode *> NodeList;
	typedef std::map<BTNode *, NodeInfo> NodeMap;

private:
	BTDebugRenderer();
	static BTDebugRenderer *s_instance;

public:
	~BTDebugRenderer();

	static BTDebugRenderer *create(BTNode *root);
	static BTDebugRenderer *getInstance();
	virtual bool init(BTNode *root);

	void initNodes(NodeList &nodes, float origin_x);
	inline cocos2d::DrawNode *getDrawNode() { return m_drawNode; }

	void render();
	void renderNode(BTNode *node, BTNodeEvent event);

private:
	cocos2d::DrawNode *m_drawNode;
	cocos2d::DrawNode *m_dynamicDrawNode;
	BTNode *m_btroot;

	NodeMap m_nodeMap;
};

#endif // BTDebugRenderer_h_
