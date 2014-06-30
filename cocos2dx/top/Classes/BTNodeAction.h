#ifndef BTNodeAction_h__
#define BTNodeAction_h__

#include "BTNode.h"

class BTNodeAction : public BTNode
{
public:
	BTNodeAction(BTPrecondition *precondition = nullptr);

	// override these functions
protected:
	virtual void onEnter(const BTInputParam &input);
	virtual void onExit(const BTInputParam &input, BTRunningStatus state);
	virtual BTRunningStatus onExecute(const BTInputParam &input, BTOutputParam &output);

protected:
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

private:
	bool m_isRunning;
};

#endif // BTNodeAction_h__
