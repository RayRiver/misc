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

	inline bool doEvaluate(const BevInputParam &input) { 
		return (m_precondition==nullptr || m_precondition->externalCondition(input)) && _doInternalEvaluate(input); }
	inline void doTransition(const BevInputParam &input) { _doTransition(input); }
	inline BevRunningStatus doTick(const BevInputParam &input, BevOutputParam &output) { return _doTick(input, output); }

	inline void setName(const char *name) { m_name = name; }
	inline const char *getName() { return m_name.c_str(); }
	BevNode &addChild(BevNode *child);

	BevNode &setPrecondition(BevPrecondition *precondition);

protected:
	virtual bool _doInternalEvaluate(const BevInputParam &input);
	virtual void _doTransition(const BevInputParam &input);
	virtual BevRunningStatus _doTick(const BevInputParam &input, BevOutputParam &output);

protected:
	inline bool _checkIndex(int index) const { return index>=0 && index<(int)m_childrenList.size(); }
	inline bool _isIndexValid(int index) const { return index != BevInvalidChildNodeIndex; }

protected:
	BevPrecondition *m_precondition;
	std::string m_name;
	std::vector<BevNode *> m_childrenList;

};

#endif // BevNode_h__
