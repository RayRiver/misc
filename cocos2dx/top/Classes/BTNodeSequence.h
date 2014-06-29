#ifndef BTNodeSequence_h__
#define BTNodeSequence_h__

#include "BTNode.h"

class BTPrecondition;
class BTNodeSequence : public BTNode
{
public:
	BTNodeSequence(BTNode *parent, BTPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BTInputParam &input);
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

protected:
	int m_nCurrentSelectIndex;

};

#endif // BTNodeSequence_h__
