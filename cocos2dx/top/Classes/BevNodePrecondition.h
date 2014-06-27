#ifndef BevNodePrecondition_h__
#define BevNodePrecondition_h__

#include "BevNodeParam.h"

class BevNodePrecondition
{
public:
	virtual bool externalCondition(const BevNodeInputParam &input) const = 0;
};

class BevNodePreconditionTRUE : public BevNodePrecondition
{
public:
	virtual bool externalCondition(const BevNodeInputParam &input) const;
};

class BevNodePreconditionFALSE : public BevNodePrecondition
{
public:
	virtual bool externalCondition(const BevNodeInputParam &input) const;
};

class BevNodePreconditionNOT : public BevNodePrecondition
{
public:
	BevNodePreconditionNOT(BevNodePrecondition *lhs);
	virtual ~BevNodePreconditionNOT();
	virtual bool externalCondition(const BevNodeInputParam &input) const;
private:
	BevNodePrecondition *m_lhs;
};

class BevNodePreconditionAND : public BevNodePrecondition
{
public:
	BevNodePreconditionAND(BevNodePrecondition *lhs, BevNodePrecondition *rhs);
	virtual ~BevNodePreconditionAND();
	virtual bool externalCondition(const BevNodeInputParam &input) const;
private:
	BevNodePrecondition *m_lhs;
	BevNodePrecondition *m_rhs;
};

class BevNodePreconditionOR : public BevNodePrecondition
{
public:
	BevNodePreconditionOR(BevNodePrecondition *lhs, BevNodePrecondition *rhs);
	virtual ~BevNodePreconditionOR();
	virtual bool externalCondition(const BevNodeInputParam &input) const;
private:
	BevNodePrecondition *m_lhs;
	BevNodePrecondition *m_rhs;
};

class BevNodePreconditionXOR : public BevNodePrecondition
{
public:
	BevNodePreconditionXOR(BevNodePrecondition *lhs, BevNodePrecondition *rhs);
	virtual ~BevNodePreconditionXOR();
	virtual bool externalCondition(const BevNodeInputParam &input) const;
private:
	BevNodePrecondition *m_lhs;
	BevNodePrecondition *m_rhs;
};

#endif // BevNodePrecondition_h__
