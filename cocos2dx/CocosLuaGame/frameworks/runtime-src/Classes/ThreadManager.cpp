#include "ThreadManager.h"

#include <assert.h>

#include "Log.h"
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
		Log("ThreadManager::start a same thread called '%s'", name);
		return;
	}

	m_thread_map.insert(pair<string, size_t>(name, m_threads.size()));
	m_threads.push_back(obj);
	obj->m_thread = new thread(s_thread_func, this, obj);
	obj->setName(name);
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

ThreadObj * ThreadManager::find( const char *name )
{
	assert(name);

	THREAD_MAP::iterator it = m_thread_map.find(name);	
	if (it == m_thread_map.end())
	{
		return nullptr;
	}
	ThreadObj *obj = m_threads[it->second];

	return obj;
}

void ThreadManager::stopAll()
{
	for (auto obj : m_threads)
	{
		if (obj)
		{
			obj->stop();	
		}
	}
}

void ThreadManager::update(float dt)
{
	lock_guard<mutex> lock(m_finished_mutex);
	if (m_finished_threads.size() > 0)
	{
		for (THREAD_LIST::iterator itFinished=m_finished_threads.begin(); itFinished!=m_finished_threads.end(); ++itFinished)	
		//for (auto finished_obj : m_finished_threads)
		{
			auto finished_obj = *itFinished;
			for (THREAD_LIST::iterator it=m_threads.begin(); it!=m_threads.end(); ++it)	
			{
				auto obj = *it;
				if (finished_obj == obj)	
				{
					*it = nullptr;
					//m_threads.erase(it); // ¿ÕÎ»Áô×Å²»É¾³ý
					m_thread_map.erase(obj->getName());
					m_finished_threads.erase(itFinished);
					obj->finish();
					delete obj;
					return;
				}
			}
		}
	}
}


