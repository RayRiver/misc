#ifndef LuaValueList_h__
#define LuaValueList_h__

#include <string>
#include <vector>

#include "cocos2d.h"
#include "CCLuaValue.h"

class LuaValueList : public cocos2d::Ref
{
public:
	//typedef cocos2d::LuaValueArrayIterator value_iter;
	typedef std::vector<cocos2d::LuaValue> value_list;
	typedef value_list::iterator value_iter;

	LuaValueList()
	{

	}

	virtual ~LuaValueList()
	{

	}

public:
	inline void push_back(const cocos2d::LuaValue &val)
	{
		m_luaValues.push_back(val);
	}

	inline void push_back(int val)
	{
		m_luaValues.push_back(cocos2d::LuaValue::intValue(val));
	}

	inline void push_back(float val)
	{
		m_luaValues.push_back(cocos2d::LuaValue::floatValue(val));
	}

	inline void push_back(bool val)
	{
		m_luaValues.push_back(cocos2d::LuaValue::booleanValue(val));
	}

	inline void push_back(const char *val)
	{
		m_luaValues.push_back(cocos2d::LuaValue::stringValue(val));
	}

	inline int size() const
	{
		return m_luaValues.size();
	}

	inline void clear()
	{
		m_luaValues.clear();
	}

	inline value_iter begin()
	{
		return m_luaValues.begin();
	}

	inline value_iter end()
	{
		return m_luaValues.end();
	}

	inline const cocos2d::LuaValue &getValue(int index) const
	{
		return m_luaValues[index];
	}

private:
	//cocos2d::LuaValueArray m_luaValues;
	value_list m_luaValues;
};

#endif // LuaValueList_h__
