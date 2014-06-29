#ifndef BTPrecondition_h__
#define BTPrecondition_h__

#include "BTParam.h"

class BTPrecondition
{
public:
	virtual bool onEvaluate(const BTInputParam &input) const = 0;
};

class BTPreconditionTRUE : public BTPrecondition
{
public:
	virtual bool onEvaluate(const BTInputParam &input) const;
};

class BTPreconditionFALSE : public BTPrecondition
{
public:
	virtual bool onEvaluate(const BTInputParam &input) const;
};

class BTPreconditionNOT : public BTPrecondition
{
public:
	BTPreconditionNOT(BTPrecondition *lhs);
	virtual ~BTPreconditionNOT();
	virtual bool onEvaluate(const BTInputParam &input) const;
private:
	BTPrecondition *m_lhs;
};

class BTPreconditionAND : public BTPrecondition
{
public:
	BTPreconditionAND(BTPrecondition *lhs, BTPrecondition *rhs);
	virtual ~BTPreconditionAND();
	virtual bool onEvaluate(const BTInputParam &input) const;
private:
	BTPrecondition *m_lhs;
	BTPrecondition *m_rhs;
};

class BTPreconditionOR : public BTPrecondition
{
public:
	BTPreconditionOR(BTPrecondition *lhs, BTPrecondition *rhs);
	virtual ~BTPreconditionOR();
	virtual bool onEvaluate(const BTInputParam &input) const;
private:
	BTPrecondition *m_lhs;
	BTPrecondition *m_rhs;
};

class BTPreconditionXOR : public BTPrecondition
{
public:
	BTPreconditionXOR(BTPrecondition *lhs, BTPrecondition *rhs);
	virtual ~BTPreconditionXOR();
	virtual bool onEvaluate(const BTInputParam &input) const;
private:
	BTPrecondition *m_lhs;
	BTPrecondition *m_rhs;
};

#endif // BTPrecondition_h__
