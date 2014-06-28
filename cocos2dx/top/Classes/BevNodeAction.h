#ifndef BevNodeAction_h__
#define BevNodeAction_h__

#include "BevNode.h"

class BevNodeAction : public BevNode
{
public:
	BevNodeAction(BevNode *parent, BevPrecondition *precondition = nullptr);

protected:
	virtual void _doEnter(const BevInputParam &input);
	virtual void _doExit(const BevInputParam &input, BevRunningStatus state);
	virtual BevRunningStatus _doExecute(const BevInputParam &input, BevOutputParam &output);

protected:
	virtual void _doTransition(const BevInputParam &input);
	virtual BevRunningStatus _doTick(const BevInputParam &input, BevOutputParam &output);

private:
	bool m_isRunning;
};

#endif // BevNodeAction_h__
