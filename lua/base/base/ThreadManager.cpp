#include "ThreadManager.h"

#include <assert.h>

#include "ThreadObj.h"

using namespace std;

ThreadManager * ThreadManager::instance()
{
	static ThreadManager obj;
	return &obj;
}

void ThreadManager::s_thread_func(void *_mgr, void *_obj)
{
	ThreadManager *mgr = (ThreadManager *)_mgr;
	ThreadObj *obj = (ThreadObj *)_obj;

	obj->m_bRunning = true;
	obj->run();
	obj->finish();

	mgr->m_finished_mutex.lock();
	mgr->m_finished_threads.push_back(obj);
	mgr->m_finished_mutex.unlock();
}

ThreadManager::ThreadManager()
{

}

ThreadManager::~ThreadManager()
{
	this->stopAll();
}

void ThreadManager::start( ThreadObj *obj, const char *name )
{
	assert(obj && name);

	THREAD_MAP::iterator it = m_thread_map.find(name);	
	if (it != m_thread_map.end())
	{
		assert(false);
		return;
	}

	m_thread_map.insert(pair<string, size_t>(name, m_threads.size()));
	m_threads.push_back(obj);
	obj->m_thread = new thread(s_thread_func, this, obj);
}

void ThreadManager::stop( const char *name )
{
	assert(name);

	THREAD_MAP::iterator it = m_thread_map.find(name);	
	if (it == m_thread_map.end())
	{
		assert(false);
		return;
	}
	ThreadObj *obj = m_threads[it->second];

	obj->stop();
}

void ThreadManager::stopAll()
{
	for (auto obj : m_threads)
	{
		obj->stop();	
	}
}

void ThreadManager::update()
{
	m_finished_mutex.lock();
	for (auto finished_obj : m_finished_threads)
	{
		for (THREAD_LIST::iterator it=m_threads.begin(); it!=m_threads.end(); ++it)	
		{
			auto obj = *it;
			if (finished_obj == obj)	
			{
				delete obj;
				*it = nullptr;
			}
		}
	}
	m_finished_mutex.unlock();
}


