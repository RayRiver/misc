#ifndef BTNode_h__
#define BTNode_h__

#include <string>
#include <vector>

#include "BTDef.h"
#include "BTParam.h"
#include "BTPrecondition.h"

class BTNode
{
public:
	BTNode(BTPrecondition *precondition = nullptr);
	virtual ~BTNode();

	// 评估选择哪个节点
	inline bool evaluate(const BTInputParam &input) { return (m_precondition==nullptr || m_precondition->onEvaluate(input)) && onInternalEvaluate(input); }
	// 转换节点
	inline void transition(const BTInputParam &input) { onTransition(input); }
	// 执行节点
	inline BTRunningStatus update(const BTInputParam &input, BTOutputParam &output) { return onUpdate(input, output); }

	inline void setName(const char *name) { m_name = name; }
	inline const char *getName() { return m_name.c_str(); }
	BTNode *addChild(const char *name, BTNode *child);
	BTNode *addChild(BTNode *child);

	BTNode &setPrecondition(BTPrecondition *precondition);

protected:
	virtual bool onInternalEvaluate(const BTInputParam &input);
	virtual void onTransition(const BTInputParam &input);
	virtual BTRunningStatus onUpdate(const BTInputParam &input, BTOutputParam &output);

protected:
	inline bool _isIndexValid(int index) const { return index>=0 && index<(int)m_childrenList.size(); }

protected:
	BTPrecondition *m_precondition;
	std::string m_name;
	std::vector<BTNode *> m_childrenList;

};

#endif // BTNode_h__
