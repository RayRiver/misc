#include "BevPrecondition.h"

#include <assert.h>

bool BevPreconditionTRUE::externalCondition( const BevInputParam &input ) const
{
	return true;
}

bool BevPreconditionFALSE::externalCondition( const BevInputParam &input ) const
{
	return false;
}

BevPreconditionNOT::BevPreconditionNOT( BevPrecondition *lhs )
	: m_lhs(lhs)
{
	assert(m_lhs);
}

BevPreconditionNOT::~BevPreconditionNOT()
{
	if (m_lhs)
	{
		delete m_lhs;
		m_lhs = nullptr;
	}
}

bool BevPreconditionNOT::externalCondition( const BevInputParam &input ) const
{
	return !m_lhs->externalCondition(input);
}

BevPreconditionAND::BevPreconditionAND( BevPrecondition *lhs, BevPrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BevPreconditionAND::~BevPreconditionAND()
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

bool BevPreconditionAND::externalCondition( const BevInputParam &input ) const
{
	return m_lhs->externalCondition(input) && m_rhs->externalCondition(input);
}

BevPreconditionOR::BevPreconditionOR( BevPrecondition *lhs, BevPrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BevPreconditionOR::~BevPreconditionOR()
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

bool BevPreconditionOR::externalCondition( const BevInputParam &input ) const
{
	return m_lhs->externalCondition(input) || m_rhs->externalCondition(input);
}

BevPreconditionXOR::BevPreconditionXOR( BevPrecondition *lhs, BevPrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BevPreconditionXOR::~BevPreconditionXOR()
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

bool BevPreconditionXOR::externalCondition( const BevInputParam &input ) const
{
	return m_lhs->externalCondition(input) ^ m_rhs->externalCondition(input);
}

