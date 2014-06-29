#ifndef BTNodeParallel_h__
#define BTNodeParallel_h__

#include "BTNode.h"

class BTPrecondition;
class BTNodeParallel : public BTNode
{
public:
	BTNodeParallel(BTNode *parent, BTPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BTInputParam &input);
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

};

#endif // BTNodeParallel_h__
