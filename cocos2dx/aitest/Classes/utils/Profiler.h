#ifndef ProfilerHelper_h__
#define ProfilerHelper_h__

#include <string>
#include <map>

#include "TimeVal.h"

class ProfilerHelper
{
public:
	static ProfilerHelper *instance();
	~ProfilerHelper();

	void reset(const char *key);
	void begin(const char *key);
	void end(const char *key);
	void print(const char *key);

	void resetall();
	void printall();

private:
	ProfilerHelper();
	static ProfilerHelper *s_instance;

private:
	struct TimeInfo
	{
		TimeVal current;
		TimeVal last;
		TimeVal total;
		TimeVal min;
		TimeVal max;
		long calls;
		TimeInfo() : calls(0) {}
	};
	std::map<std::string, TimeInfo> m_times;
};

#define _ENABLE_PROFILER_HELPER 0

#if _ENABLE_PROFILER_HELPER

#define PROFILE_RESET(key)		ProfilerHelper::instance()->reset(key);
#define PROFILE_BEGIN(key)		ProfilerHelper::instance()->begin(key);
#define PROFILE_END(key)		ProfilerHelper::instance()->end(key);
#define PROFILE_PRINT(key)		ProfilerHelper::instance()->print(key);

#define PROFILE_RESET_ALL()		ProfilerHelper::instance()->resetall();
#define PROFILE_PRINT_ALL()		ProfilerHelper::instance()->printall();

#else

#define PROFILE_RESET(key)
#define PROFILE_BEGIN(key)
#define PROFILE_END(key)
#define PROFILE_PRINT(key)

#define PROFILE_RESET_ALL()
#define PROFILE_PRINT_ALL()

#endif 

#endif // Profiler_h__
