#ifndef BehaviorTreeEditor_h__
#define BehaviorTreeEditor_h__

#include "cocos2d.h"

#include "BTECanvasLayer.h"
#include "BTEControlLayer.h"

class BehaviorTreeEditor : public cocos2d::Layer
{
public:
	static cocos2d::Scene* create();

	static BehaviorTreeEditor *getInstance();

	virtual bool init();

	inline BTEControlLayer *getControlLayer() { return m_controlLayer; }
	inline BTECanvasLayer *getCanvasLayer() { return m_canvasLayer; }

private:
	static BehaviorTreeEditor *s_instance;

	BTEControlLayer *m_controlLayer;
	BTECanvasLayer *m_canvasLayer;

};

#endif // BehaviorTreeEditor_h__
