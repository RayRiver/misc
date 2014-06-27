#ifndef BevNodeTerminal_h__
#define BevNodeTerminal_h__

#include "BevNode.h"

class BevNodeTerminal : public BevNode
{
public:
	BevNodeTerminal(BevNode *parent, BevNodePrecondition *precondition = nullptr);

protected:
	virtual void _doEnter(const BevNodeInputParam &input);
	virtual void _doExit(const BevNodeInputParam &input, BevRunningStatus state);
	virtual BevRunningStatus _doExecute(const BevNodeInputParam &input, BevNodeOutputParam &output);

protected:
	virtual void _doTransition(const BevNodeInputParam &input);
	virtual BevRunningStatus _doTick(const BevNodeInputParam &input, BevNodeOutputParam &output);

private:
	bool m_isRunning;
};

#endif // BevNodeTerminal_h__
