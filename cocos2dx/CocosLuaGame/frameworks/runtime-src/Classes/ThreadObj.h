#ifndef ThreadObj_h__
#define ThreadObj_h__

#include <thread>

class ThreadObj
{
public:
	ThreadObj();
	virtual ~ThreadObj();
	virtual void run() = 0;
	virtual void finish() = 0;

	inline bool isRunning() { return m_bRunning; }
	inline void stop() { m_bRunning = false; }

	inline void setName(const char *name) { m_name = name; }
	inline const char *getName() { return m_name.c_str(); }

public:
	friend class ThreadManager;

protected:
	std::thread *m_thread;	
	bool m_bRunning;
	std::string m_name;
};

#endif // ThreadObj_h__
