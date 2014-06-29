#ifndef BTParam_h__
#define BTParam_h__

#include <assert.h>

class BTParam
{
public:
	template<typename RealDataType>
	BTParam(RealDataType *data)
		: m_realData(data)
	{}

	template<typename RealDataType>
	RealDataType& getRealData(){
		assert(m_realData);
		return *reinterpret_cast<RealDataType*>(m_realData);
	}

	template<typename RealDataType>
	const RealDataType& getRealData() const{
		assert(m_realData);
		return *reinterpret_cast<const RealDataType*>(m_realData);
	}

	template<typename RealDataType>
	BTParam& operator =(RealDataType* data)
	{
		set<RealDataType>(data);
		return *this;
	}

private:
	template<typename RealDataType>
	void set(RealDataType* data)
	{
		m_realData = reinterpret_cast<void*>(data);
	}

private:
	void *m_realData;
};

typedef BTParam BTInputParam;
typedef BTParam BTOutputParam;

#endif // BTParam_h__
