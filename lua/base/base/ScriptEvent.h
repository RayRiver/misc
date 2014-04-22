#ifndef ScriptEvent_h__
#define ScriptEvent_h__

typedef int LUA_FUNCTION;

class ScriptEventManager
{
public:
	ScriptEventManager();
	virtual ~ScriptEventManager();

	void reg(const char *name, );
	void unreg();
};

#endif // ScriptEvent_h__
