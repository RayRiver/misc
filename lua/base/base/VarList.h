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

	// add for lua
	inline void addInt8(LUA_NUMBER val) { add((int8_t)val); }
	inline void addInt16(LUA_NUMBER val) { add((int16_t)val); }
	inline void addInt32(LUA_NUMBER val) { add((int32_t)val); }
	inline void addInt64(LUA_NUMBER val) { add((int64_t)val); }
	inline void addFloat(LUA_NUMBER val) { add((float)val); }
	inline void addDouble(LUA_NUMBER val) { add((double)val); }
	inline void addString(const char *val) { add((const char *)val); }

	inline LUA_NUMBER toInt8(int index) { return get(index).toNumber(); }
	inline LUA_NUMBER toInt16(int index) { return get(index).toNumber(); }
	inline LUA_NUMBER toInt32(int index) { return get(index).toNumber(); }
	inline LUA_NUMBER toInt64(int index) { return get(index).toNumber(); }
	inline LUA_NUMBER toFloat(int index) { return get(index).toNumber(); }
	inline LUA_NUMBER toDouble(int index) { return get(index).toNumber(); }
	inline const char *toString(int index) { return get(index).toString(); }

private:
	std::vector<Var> m_vars;

};

#endif // VarList_h__
