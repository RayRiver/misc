#ifndef BevNodeNonePrioritySelector_h__
#define BevNodeNonePrioritySelector_h__

#include "BevNode.h"
#include "BevNodePrioritySelector.h"

class BevPrecondition;
class BevNodeNonePrioritySelector : public BevNodePrioritySelector
{
public:
	BevNodeNonePrioritySelector(BevNode *parent, BevPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BevInputParam &input);
};

#endif // BevNodeNonePrioritySelector_h__
