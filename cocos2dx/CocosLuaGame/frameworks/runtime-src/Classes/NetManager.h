#ifndef NetManager_h__
#define NetManager_h__

#include <vector>
#include <thread>
#include <mutex>

#include "ITickable.h"

class NetSocket;
class NetManager : public ITickable
{
public:
	static NetManager *instance();
	virtual ~NetManager();

	void start();
	void stop();
	void run();
	inline bool isStarted() { return m_thread ? true : false; }

	void add(NetSocket *sock);
	void remove(NetSocket *sock);
	bool find(NetSocket *sock, size_t &index);

	virtual void update(float dt);

private:
	NetManager();
	static void thread_task(NetManager *engine);

private:
	std::thread *m_thread;
	bool m_bRunning;
	std::vector<NetSocket *> m_socks;
	std::mutex m_socks_mutex;
};

extern NetSocket *GetNetImp();


#endif // NetManager_h__
