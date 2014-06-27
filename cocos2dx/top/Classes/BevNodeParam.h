#ifndef BevNodeParam_h__
#define BevNodeParam_h__

#include <assert.h>

class BevNodeParam
{
public:
	template<typename RealDataType>
	BevNodeParam(RealDataType *data)
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
	BevNodeParam& operator =(RealDataType* data)
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

typedef BevNodeParam BevNodeInputParam;
typedef BevNodeParam BevNodeOutputParam;

#endif // BevNodeParam_h__
