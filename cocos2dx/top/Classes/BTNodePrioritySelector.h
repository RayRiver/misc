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
	int m_nEvaluateSelectIndex;		// ����ѡ���Ľڵ�
	int m_nCurrentSelectIndex;		// ��ǰ�������еĽڵ㣨���������Ϻ󣬻���Ϊ��Ч��

};

#endif // BTNodePrioritySelector_h__
