#include "ThreadObj.h"

#include "ThreadManager.h"

ThreadObj::ThreadObj()
	: m_thread(nullptr)
	, m_bRunning(false)
{

}

ThreadObj::~ThreadObj() 
{
	if (m_thread)
	{
		m_thread->join();
		delete m_thread;
	}
}
