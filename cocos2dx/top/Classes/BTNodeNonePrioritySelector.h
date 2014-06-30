#ifndef BTNodeNonePrioritySelector_h__
#define BTNodeNonePrioritySelector_h__

#include "BTNode.h"
#include "BTNodePrioritySelector.h"

class BTPrecondition;
class BTNodeNonePrioritySelector : public BTNodePrioritySelector
{
public:
	BTNodeNonePrioritySelector(BTPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BTInputParam &input);
};

#endif // BTNodeNonePrioritySelector_h__
