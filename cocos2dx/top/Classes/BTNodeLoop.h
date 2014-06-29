#ifndef BTNodeLoop_h__
#define BTNodeLoop_h__

#include "BTNode.h"

class BTPrecondition;
class BTNodeLoop : public BTNode
{
public:
	enum { InfiniteLoop = -1 };

public:
	BTNodeLoop(BTNode *parent, BTPrecondition *precondition = nullptr, int nLoopCount = BTNodeLoop::InfiniteLoop);

	virtual bool onInternalEvaluate(const BTInputParam &input);
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

private:
	int m_nLoopCount;
	int m_nCurrentLoopCount;
};

#endif // BTNodeLoop_h__
