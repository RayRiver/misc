#ifndef BevNode_h__
#define BevNode_h__

#include <string>
#include <vector>

#include "BevDef.h"
#include "BevParam.h"
#include "BevPrecondition.h"

class BevNode
{
public:
	BevNode(BevNode *parent, BevPrecondition *precondition = nullptr);
	virtual ~BevNode();

	// 评估选择哪个节点
	inline bool evaluate(const BevInputParam &input) { return (m_precondition==nullptr || m_precondition->onEvaluate(input)) && onInternalEvaluate(input); }
	// 转换节点
	inline void transition(const BevInputParam &input) { onTransition(input); }
	// 执行节点
	inline BevRunningStatus execute(const BevInputParam &input, BevOutputParam &output) { return onExecute(input, output); }

	inline void setName(const char *name) { m_name = name; }
	inline const char *getName() { return m_name.c_str(); }
	BevNode &addChild(BevNode *child);

	BevNode &setPrecondition(BevPrecondition *precondition);

protected:
	virtual bool onInternalEvaluate(const BevInputParam &input);
	virtual void onTransition(const BevInputParam &input);
	virtual BevRunningStatus onExecute(const BevInputParam &input, BevOutputParam &output);

protected:
	inline bool _isIndexValid(int index) const { return index != BevInvalidChildNodeIndex; }

protected:
	BevPrecondition *m_precondition;
	std::string m_name;
	std::vector<BevNode *> m_childrenList;

};

#endif // BevNode_h__
