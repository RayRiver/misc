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
	int m_nEvaluateSelectIndex;		// ����ѡ���Ľڵ�
	int m_nCurrentSelectIndex;		// ��ǰ�������еĽڵ㣨���������Ϻ󣬻���Ϊ��Ч��

};

#endif // BevNodePrioritySelector_h__
