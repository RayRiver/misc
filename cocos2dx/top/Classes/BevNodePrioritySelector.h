#ifndef BevNodePrioritySelector_h__
#define BevNodePrioritySelector_h__

#include "BevNode.h"

class BevPrecondition;
class BevNodePrioritySelector : public BevNode
{
public:
	BevNodePrioritySelector(BevNode *parent, BevPrecondition *precondition = nullptr);

	virtual bool _doInternalEvaluate(const BevInputParam &input);
	virtual void _doTransition(const BevInputParam &input);
	virtual BevRunningStatus _doTick(const BevInputParam &input, BevOutputParam &output);

protected:
	int m_nEvaluateSelectIndex;		// ����ѡ���Ľڵ�
	int m_nCurrentSelectIndex;		// ��ǰ�������еĽڵ㣨���������Ϻ󣬻���Ϊ��Ч��

};

#endif // BevNodePrioritySelector_h__
