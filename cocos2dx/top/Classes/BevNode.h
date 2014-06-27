#ifndef BevNode_h__
#define BevNode_h__

#include <string>
#include <vector>

#include "BevDef.h"
#include "BevNodeParam.h"
#include "BevNodePrecondition.h"

class BevNode
{
public:
	BevNode(BevNode *parent, BevNodePrecondition *precondition = nullptr);
	virtual ~BevNode();

	inline bool doEvaluate(const BevNodeInputParam &input) { return (m_precondition==nullptr || m_precondition->externalCondition(input)) && _doInternalEvaluate(input); }
	inline void doTransition(const BevNodeInputParam &input) { _doTransition(input); }
	inline BevRunningStatus doTick(const BevNodeInputParam &input, BevNodeOutputParam &output) { return _doTick(input, output); }

	inline void setName(const char *name) { m_name = name; }
	inline const char *getName() { return m_name.c_str(); }
	BevNode &addChild(BevNode *child);

	BevNode &setPrecondition(BevNodePrecondition *precondition);

protected:
	virtual bool _doInternalEvaluate(const BevNodeInputParam &input);
	virtual void _doTransition(const BevNodeInputParam &input);
	virtual BevRunningStatus _doTick(const BevNodeInputParam &input, BevNodeOutputParam &output);

protected:
	inline bool _checkIndex(int index) const { return index>=0 && index<(int)m_childrenList.size(); }
	inline bool _isIndexValid(int index) const { return index != BevInvalidChildNodeIndex; }

protected:
	BevNodePrecondition *m_precondition;
	std::string m_name;
	std::vector<BevNode *> m_childrenList;

};

#endif // BevNode_h__
