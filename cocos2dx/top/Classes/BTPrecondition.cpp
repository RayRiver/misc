#include "BTPrecondition.h"

#include <assert.h>

bool BTPreconditionTRUE::onEvaluate( const BTInputParam &input ) const
{
	return true;
}

bool BTPreconditionFALSE::onEvaluate( const BTInputParam &input ) const
{
	return false;
}

BTPreconditionNOT::BTPreconditionNOT( BTPrecondition *lhs )
	: m_lhs(lhs)
{
	assert(m_lhs);
}

BTPreconditionNOT::~BTPreconditionNOT()
{
	if (m_lhs)
	{
		delete m_lhs;
		m_lhs = nullptr;
	}
}

bool BTPreconditionNOT::onEvaluate( const BTInputParam &input ) const
{
	return !m_lhs->onEvaluate(input);
}

BTPreconditionAND::BTPreconditionAND( BTPrecondition *lhs, BTPrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BTPreconditionAND::~BTPreconditionAND()
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

bool BTPreconditionAND::onEvaluate( const BTInputParam &input ) const
{
	return m_lhs->onEvaluate(input) && m_rhs->onEvaluate(input);
}

BTPreconditionOR::BTPreconditionOR( BTPrecondition *lhs, BTPrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BTPreconditionOR::~BTPreconditionOR()
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

bool BTPreconditionOR::onEvaluate( const BTInputParam &input ) const
{
	return m_lhs->onEvaluate(input) || m_rhs->onEvaluate(input);
}

BTPreconditionXOR::BTPreconditionXOR( BTPrecondition *lhs, BTPrecondition *rhs )
	: m_lhs(lhs)
	, m_rhs(rhs)
{
	assert(m_lhs && m_rhs);
}

BTPreconditionXOR::~BTPreconditionXOR()
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

bool BTPreconditionXOR::onEvaluate( const BTInputParam &input ) const
{
	return m_lhs->onEvaluate(input) ^ m_rhs->onEvaluate(input);
}

