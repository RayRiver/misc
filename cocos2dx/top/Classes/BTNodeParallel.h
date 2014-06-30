#ifndef BTNodeParallel_h__
#define BTNodeParallel_h__

#include "BTNode.h"

class BTPrecondition;
class BTNodeParallel : public BTNode
{
public:
	enum class FinishCondition
	{
		AND,
		OR,
	};

public:
	BTNodeParallel(FinishCondition finishCondition = FinishCondition::OR, BTPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BTInputParam &input);
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

private:
	void initStatus();

private:
	FinishCondition m_finishCondition;
	std::vector<BTRunningStatus> m_runningStatus;
};

#endif // BTNodeParallel_h__
