#ifndef BevNodeLoop_h__
#define BevNodeLoop_h__

#include "BevNode.h"

class BevPrecondition;
class BevNodeLoop : public BevNode
{
public:
	enum { InfiniteLoop = -1 };

public:
	BevNodeLoop(BevNode *parent, BevPrecondition *precondition = nullptr, int nLoopCount = BevNodeLoop::InfiniteLoop);

	virtual bool onInternalEvaluate(const BevInputParam &input);
	virtual void onTransition(const BevInputParam &input);
	virtual BevRunningStatus onUpdate(const BevInputParam &input, BevOutputParam &output);

private:
	int m_nLoopCount;
	int m_nCurrentLoopCount;
};

#endif // BevNodeLoop_h__
