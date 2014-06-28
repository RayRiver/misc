#ifndef BevNodeSequence_h__
#define BevNodeSequence_h__

#include "BevNode.h"

class BevPrecondition;
class BevNodeSequence : public BevNode
{
public:
	BevNodeSequence(BevNode *parent, BevPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BevInputParam &input);
	virtual void onTransition(const BevInputParam &input);
	virtual BevRunningStatus onUpdate(const BevInputParam &input, BevOutputParam &output);

protected:
	int m_nCurrentSelectIndex;

};

#endif // BevNodeSequence_h__
