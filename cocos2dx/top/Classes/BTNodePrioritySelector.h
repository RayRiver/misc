#ifndef BTNodePrioritySelector_h__
#define BTNodePrioritySelector_h__

#include "BTNode.h"

class BTPrecondition;
class BTNodePrioritySelector : public BTNode
{
public:
	BTNodePrioritySelector(BTNode *parent, BTPrecondition *precondition = nullptr);

	virtual bool onInternalEvaluate(const BTInputParam &input);
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

protected:
	int m_nEvaluateSelectIndex;		// 评估选定的节点
	int m_nCurrentSelectIndex;		// 当前正在运行的节点（如果运行完毕后，会置为无效）

};

#endif // BTNodePrioritySelector_h__
