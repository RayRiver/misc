#ifndef BevNodeParallel_h__
#define BevNodeParallel_h__

#include "BevNode.h"

class BevPrecondition;
class BevNodeParallel : public BevNode
{
public:
	BevNodeParallel(BevNode *parent, BevPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BevInputParam &input);
	virtual void onTransition(const BevInputParam &input);
	virtual BevRunningStatus onUpdate(const BevInputParam &input, BevOutputParam &output);

};

#endif // BevNodeParallel_h__
