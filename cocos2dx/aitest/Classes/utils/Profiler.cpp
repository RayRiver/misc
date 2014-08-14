#include "Profiler.h"

#include "cocos2d.h"
USING_NS_CC;

ProfilerHelper * ProfilerHelper::s_instance = nullptr;

ProfilerHelper * ProfilerHelper::instance()
{
	if (!s_instance)
	{
		s_instance = new ProfilerHelper;
	}
	return s_instance;
}

ProfilerHelper::ProfilerHelper()
{

}

ProfilerHelper::~ProfilerHelper()
{

}

void ProfilerHelper::reset( const char *key )
{
	const auto &it = m_times.find(key);
	if (it != m_times.end())
	{
		TimeInfo &info = it->second;
		info.current = TimeVal::Zero;
		info.last = TimeVal::Zero;
		info.total = TimeVal::Zero;
		info.max = TimeVal::Zero;
		info.min = TimeVal::Zero;
		info.calls = 0;
	}
}

void ProfilerHelper::begin( const char *key )
{
	TimeInfo *info = nullptr;

	const auto &it = m_times.find(key);
	if (it == m_times.end())
	{
		m_times[key] = TimeInfo();
		info = &m_times[key];
	}
	else
	{
		info = &it->second;
	}

	TimeVal::getTimeVal(info->current);
}

void ProfilerHelper::end( const char *key )
{
	const auto &it = m_times.find(key);
	if (it != m_times.end())
	{
		TimeInfo &info = it->second;

		// Î´µ÷ÓÃbegin;
		if (info.current == TimeVal::Zero)
		{
			return;
		}

		TimeVal tv;
		TimeVal::getTimeVal(tv);
		TimeVal::sub(tv, info.current, info.last);
		TimeVal::add(info.last, info.total, info.total);
		++info.calls;

		if (info.max < info.last)
		{
			info.max = info.last;
		}
		if (info.min == TimeVal::Zero || info.min > info.last)
		{
			info.min = info.last;
		}
	}
}

void ProfilerHelper::print( const char *key )
{
	const auto &it = m_times.find(key);
	if (it != m_times.end())
	{
		TimeInfo &info = it->second;

		log("[PROFILER] %s: last=%f, min=%f, max=%f, total=%f, calls=%ld", key, info.last.to_s(), info.min.to_s(), info.max.to_s(), info.total.to_s(), info.calls);
	}
}

void ProfilerHelper::resetall()
{
	for (auto &it : m_times)
	{
		auto &info = it.second;
		info.current = TimeVal::Zero;
		info.last = TimeVal::Zero;
		info.total = TimeVal::Zero;
		info.max = TimeVal::Zero;
		info.min = TimeVal::Zero;
		info.calls = 0;
	}
}

void ProfilerHelper::printall()
{
	log("[PROFILER] begin ==============================================================");
	for (auto &it : m_times)
	{
		auto &key = it.first;
		auto &info = it.second;

		log("[PROFILER] %s: last=%f, min=%f, max=%f, total=%f, calls=%ld", key.c_str(), info.last.to_s(), info.min.to_s(), info.max.to_s(), info.total.to_s(), info.calls);
	}
	log("[PROFILER]  end  ==============================================================\n");
}

