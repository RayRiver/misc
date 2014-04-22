#ifndef ThreadManager_h__
#define ThreadManager_h__

#include <string>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

class ThreadObj;
class ThreadManager
{
private:
	ThreadManager();
public:
	static ThreadManager *instance();
	virtual ~ThreadManager();

	static void s_thread_func(void *_mgr, void *_obj);

	void update();
	void start(ThreadObj *obj, const char *name);
	void stop(const char *name);
	void stopAll();

private:
	typedef std::vector<ThreadObj *> THREAD_LIST;
	typedef std::map<std::string, size_t> THREAD_MAP;
	THREAD_LIST m_threads;
	THREAD_LIST m_finished_threads;
	THREAD_MAP m_thread_map;
	std::mutex m_finished_mutex;
};

#endif // ThreadManager_h__