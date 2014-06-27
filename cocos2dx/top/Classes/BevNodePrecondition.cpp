#include "BevNodePrecondition.h"

#include <assert.h>

bool BevNodePreconditionTRUE::externalCondition( const BevNodeInputParam &input ) const
{
	return true;
}

bool BevNodePreconditionFALSE::externalCondition( const BevNodeInputParam &input ) const
{
	return false;
}

BevNodePreconditionNOT::BevNodePreconditionNOT( BevNodePrecondition *lhs )
	: m_lhs(lhs)
{
	assert(m_lhs);
}

BevNodePreconditionNOT::~BevNodePreconditionNOT()
{
	if (m_lhs)
	{
		delete m_lhs;
		m_lhs = nullptr;
	}
}

bool BevNodePreconditionNOT::externalCondition( const BevNodeInputParam &input ) const
{
	return !m_lhs->externalCondition(input);
}

BevNodePreconditionAND::BevNodePreconditionAND( BevNodePrecondition *lhs, BevNodePrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BevNodePreconditionAND::~BevNodePreconditionAND()
{
	if (m_lhs)
	{
		delete m_lhs;
		m_lhs = nullptr;
	}
	if (m_rhs)
	{
		delete m_rhs;
		m_rhs = nullptr;
	}
}

bool BevNodePreconditionAND::externalCondition( const BevNodeInputParam &input ) const
{
	return m_lhs->externalCondition(input) && m_rhs->externalCondition(input);
}

BevNodePreconditionOR::BevNodePreconditionOR( BevNodePrecondition *lhs, BevNodePrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BevNodePreconditionOR::~BevNodePreconditionOR()
{
	if (m_lhs)
	{
		delete m_lhs;
		m_lhs = nullptr;
	}
	if (m_rhs)
	{
		delete m_rhs;
		m_rhs = nullptr;
	}
}

bool BevNodePreconditionOR::externalCondition( const BevNodeInputParam &input ) const
{
	return m_lhs->externalCondition(input) || m_rhs->externalCondition(input);
}

BevNodePreconditionXOR::BevNodePreconditionXOR( BevNodePrecondition *lhs, BevNodePrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BevNodePreconditionXOR::~BevNodePreconditionXOR()
{
	if (m_lhs)
	{
		delete m_lhs;
		m_lhs = nullptr;
	}
	if (m_rhs)
	{
		delete m_rhs;
		m_rhs = nullptr;
	}
}

bool BevNodePreconditionXOR::externalCondition( const BevNodeInputParam &input ) const
{
	return m_lhs->externalCondition(input) ^ m_rhs->externalCondition(input);
}

