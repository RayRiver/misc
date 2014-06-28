#ifndef BevNodeParam_h__
#define BevNodeParam_h__

#include <assert.h>

class BevParam
{
public:
	template<typename RealDataType>
	BevParam(RealDataType *data)
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
	BevParam& operator =(RealDataType* data)
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

typedef BevParam BevInputParam;
typedef BevParam BevOutputParam;

#endif // BevNodeParam_h__
