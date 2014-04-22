#ifndef Var_h__
#define Var_h__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

class Var
{
public:
	enum Type
	{
		UNDEFINED,
		STRING,
		_RESERVED_DONT_USE_1,
		INT,
		FLOAT,
		NUMBER,
		BOOL,
		INT64,
	};

private:
	char m_type;
	union
	{
		bool m_boolValue;
		double m_numberValue;
		const char* m_stringValue;
	};

private:
	inline void clear()
	{
		if (m_type == Var::STRING)	
		{
			if (m_stringValue)
			{
				free((char *)m_stringValue);
				m_stringValue = nullptr;
			}
		}
		m_type = Var::UNDEFINED;
	}

	inline const char *newstring(const char *s)
	{
		return _strdup(s);
	}

	inline void set(int val)
	{
		this->clear();
		m_type = Var::INT;
		m_numberValue = val;
	}

	inline void set(int64_t val)
	{
		this->clear();
		m_type = Var::INT64;
		m_numberValue = (double)val;
	}

	inline void set(float val)
	{
		this->clear();
		m_type = Var::FLOAT;
		m_numberValue = val;
	}

	inline void set(double val)
	{
		this->clear();
		m_type = Var::NUMBER;
		m_numberValue = val;
	}

	inline void set(bool val)
	{
		this->clear();
		m_type = Var::BOOL;
		m_boolValue = val;
	}

	inline void set(const char *val)
	{
		if (val == m_stringValue) return;
		this->clear();
		m_type = Var::STRING;
		m_stringValue = this->newstring(val);
	}

	inline void set(const Var &val)
	{
		if (&val == this)
		{
			return;
		}

		switch (val.m_type)
		{
		case Var::INT:
			this->set((int)val.m_numberValue);
			break;
		case Var::INT64:
			this->set((int64_t)val.m_numberValue);
			break;
		case Var::FLOAT:
			this->set((float)val.m_numberValue);
			break;
		case Var::NUMBER:
			this->set(val.m_numberValue);
			break;
		case Var::BOOL:
			this->set(val.m_boolValue);
			break;
		case Var::STRING:
			this->set(val.m_stringValue);
			break;
		case Var::UNDEFINED:
			break;
		default:
			assert(false);
			break;
		}
	}

public:
	Var()
	{
		this->init();
	}

	~Var()
	{
		this->clear();
	}

	Var(int val)
	{
		this->init();
		this->set(val);
	}

	Var(int64_t val)
	{
		this->init();
		this->set(val);
	}

	Var(float val)
	{
		this->init();
		this->set(val);
	}

	Var(double val)
	{
		this->init();
		this->set(val);
	}

	Var(bool val)
	{
		this->init();
		this->set(val);
	}

	Var(const char *val)
	{
		this->init();
		this->set(val);
	}

	Var(const Var &val)
	{
		this->init();
		this->set(val);
	}

	inline void init()
	{
		m_type = Var::UNDEFINED;
		m_numberValue = 0;
		m_stringValue = 0;
	}

	inline int getType() const
	{
		return m_type;
	}

	inline bool isBool() const
	{
		return m_type == Var::BOOL;
	}

	inline bool isNumber() const
	{
		return m_type == Var::NUMBER || m_type == Var::INT || m_type == Var::INT64 || m_type == Var::FLOAT;
	}

	inline bool isString() const
	{
		return m_type == Var::STRING;
	}

	inline bool toBool() const
	{
		assert(this->isBool());
		return m_boolValue;
	}

	inline int toInt() const
	{
		assert(this->isNumber());
		return (int)m_numberValue;
	}

	inline int64_t toInt64() const
	{
		assert(this->isNumber());
		return (int64_t)m_numberValue;
	}

	inline float toFloat() const
	{
		assert(this->isNumber());
		return (float)m_numberValue;
	}

	inline double toNumber() const
	{
		assert(this->isNumber());
		return (double)m_numberValue;
	}

	inline const char *toString() const
	{
		assert(this->isString());
		return m_stringValue;
	}


	inline void operator = (int val)
	{
		this->set(val);
	}

	inline void operator = (int64_t val)
	{
		this->set(val);
	}

	inline void operator = (float val)
	{
		this->set(val);
	}

	inline void operator = (double val)
	{
		this->set(val);
	}

	inline void operator = (bool val)
	{
		this->set(val);
	}

	inline void operator = (const char *val)
	{
		this->set(val);
	}

	inline void operator = (const Var& val)
	{
		this->set(val);
	}


	inline bool operator == (int val) const
	{
		if (!this->isNumber()) return false;
		return (int)m_numberValue == val;
	}

	inline bool operator == (int64_t val) const
	{
		if (!this->isNumber()) return false;
		return (int64_t)m_numberValue == val;
	}

	inline bool operator == (float val) const
	{
		if (!this->isNumber()) return false;
		return (float)m_numberValue == val;
	}

	inline bool operator == (double val) const
	{
		if (!this->isNumber()) return false;
		return (double)m_numberValue == val;
	}

	inline bool operator == (bool val) const
	{
		if (!this->isBool()) return false;
		return m_boolValue == val;
	}

	inline bool operator == (const char *val) const
	{
		if (!val) return false;
		if (!this->isString()) return false;
		return strcmp(m_stringValue, val) == 0;
	}

	inline bool operator == (const Var& val) const
	{
		if (m_type != val.m_type)
		{
			if (val.isString() && this->isString())
				return strcmp(m_stringValue, val.m_stringValue) == 0;
			else
				return false;
		}
		if (val.m_type == Var::UNDEFINED)
		{
			return true;
		}
		switch(val.m_type)
		{
		case Var::STRING:
			return strcmp(m_stringValue, val.m_stringValue) == 0;
		case Var::NUMBER:
		case Var::FLOAT:
		case Var::INT:
		case Var::INT64:
			return m_numberValue == val.m_numberValue;
		case Var::BOOL:
			return m_boolValue == val.m_boolValue;
		default:
			assert(false);
			break;
		}
		return false;
	}
};

#endif // Var_h__
