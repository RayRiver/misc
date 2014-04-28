#ifndef VarList_h__
#define VarList_h__

#include <stdint.h>
#include <assert.h>
#include <vector>

#include "Var.h"

class VarList
{
public:
	VarList()
	{

	}

	virtual ~VarList()
	{

	}

	template <class T> 
	inline void add(T value)
	{
		m_vars.push_back(value);
	}

	inline void clear()
	{
		m_vars.clear();
	}

	inline int count() const
	{
		return (int)m_vars.size();
	}

	inline const Var &get(int index) const 
	{
		assert(index>=0 && index<(int)m_vars.size());
		return m_vars[index];
	}

	inline void set(int index, const Var &var)
	{
		assert(index>=0 && index<(int)m_vars.size());
		m_vars[index] = var;
	}


private:
	std::vector<Var> m_vars;

};

#endif // VarList_h__
