#ifndef BTECanvasLayer_h__
#define BTECanvasLayer_h__

#include <vector>

#include "cocos2d.h"

#include "BTELayer.h"

class BTENode;
class BTECanvas;
class BTECanvasLayer : public BTELayer
{
public:
	CREATE_FUNC(BTECanvasLayer);

	virtual bool init();

	void addNode(BTENode *node);

	void startDrag();
	void stopDrag();
	void doDrag(const cocos2d::Vec2 &move);
	bool isDragging();

private:
	bool m_bDaggingLayer;
	cocos2d::DrawNode *m_drawNode;

};

#endif // BTECanvasLayer_h__
