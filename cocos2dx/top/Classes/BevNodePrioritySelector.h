#ifndef BevNodePrioritySelector_h__
#define BevNodePrioritySelector_h__

#include "BevNode.h"

class BevNodePrecondition;
class BevNodePrioritySelector : public BevNode
{
public:
	BevNodePrioritySelector(BevNode *parent, BevNodePrecondition *precondition = nullptr);

	virtual bool _doInternalEvaluate(const BevNodeInputParam &input);
	virtual void _doTransition(const BevNodeInputParam &input);
	virtual BevRunningStatus _doTick(const BevNodeInputParam &input, BevNodeOutputParam &output);

protected:
	int m_nEvaluateSelectIndex;		// 评估选定的节点
	int m_nCurrentSelectIndex;		// 当前正在运行的节点（如果运行完毕后，会置为无效）

};

#endif // BevNodePrioritySelector_h__
