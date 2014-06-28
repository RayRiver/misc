#ifndef BevPrecondition_h__
#define BevPrecondition_h__

#include "BevParam.h"

class BevPrecondition
{
public:
	virtual bool externalCondition(const BevInputParam &input) const = 0;
};

class BevPreconditionTRUE : public BevPrecondition
{
public:
	virtual bool externalCondition(const BevInputParam &input) const;
};

class BevPreconditionFALSE : public BevPrecondition
{
public:
	virtual bool externalCondition(const BevInputParam &input) const;
};

class BevPreconditionNOT : public BevPrecondition
{
public:
	BevPreconditionNOT(BevPrecondition *lhs);
	virtual ~BevPreconditionNOT();
	virtual bool externalCondition(const BevInputParam &input) const;
private:
	BevPrecondition *m_lhs;
};

class BevPreconditionAND : public BevPrecondition
{
public:
	BevPreconditionAND(BevPrecondition *lhs, BevPrecondition *rhs);
	virtual ~BevPreconditionAND();
	virtual bool externalCondition(const BevInputParam &input) const;
private:
	BevPrecondition *m_lhs;
	BevPrecondition *m_rhs;
};

class BevPreconditionOR : public BevPrecondition
{
public:
	BevPreconditionOR(BevPrecondition *lhs, BevPrecondition *rhs);
	virtual ~BevPreconditionOR();
	virtual bool externalCondition(const BevInputParam &input) const;
private:
	BevPrecondition *m_lhs;
	BevPrecondition *m_rhs;
};

class BevPreconditionXOR : public BevPrecondition
{
public:
	BevPreconditionXOR(BevPrecondition *lhs, BevPrecondition *rhs);
	virtual ~BevPreconditionXOR();
	virtual bool externalCondition(const BevInputParam &input) const;
private:
	BevPrecondition *m_lhs;
	BevPrecondition *m_rhs;
};

#endif // BevPrecondition_h__
