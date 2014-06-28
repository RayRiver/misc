#ifndef BevNodeAction_h__
#define BevNodeAction_h__

#include "BevNode.h"

class BevNodeAction : public BevNode
{
public:
	BevNodeAction(BevNode *parent, BevPrecondition *precondition = nullptr);

	// override these functions
protected:
	virtual void onEnter(const BevInputParam &input);
	virtual void onExit(const BevInputParam &input, BevRunningStatus state);
	virtual BevRunningStatus onExecute(const BevInputParam &input, BevOutputParam &output);

protected:
	virtual void onTransition(const BevInputParam &input);
	virtual BevRunningStatus onUpdate(const BevInputParam &input, BevOutputParam &output);

private:
	bool m_isRunning;
};

#endif // BevNodeAction_h__
