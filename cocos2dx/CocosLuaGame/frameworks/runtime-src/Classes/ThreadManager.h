#ifndef ThreadManager_h__
#define ThreadManager_h__

#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

#include "ITickable.h"

class ThreadObj;
class ThreadManager : public ITickable
{
private:
	ThreadManager();
public:
	static ThreadManager *instance();
	virtual ~ThreadManager();

	static void s_thread_func(void *_mgr, void *_obj);

	virtual void update(float dt);
	void start(ThreadObj *obj, const char *name);
	void stop(const char *name);
	void stopAll();
	ThreadObj *find(const char *name);

private:
	typedef std::vector<ThreadObj *> THREAD_LIST;
	typedef std::map<std::string, size_t> THREAD_MAP;
	THREAD_LIST m_threads;
	THREAD_LIST m_finished_threads;
	THREAD_MAP m_thread_map;
	std::mutex m_finished_mutex;
};

#endif // ThreadManager_h__