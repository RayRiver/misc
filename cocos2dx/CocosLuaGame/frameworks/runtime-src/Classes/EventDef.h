#ifndef EventDef_h__
#define EventDef_h__

#include "LuaScriptHandlerMgr.h"

#define EVENT_USEREXT_CUSTOM_NETWORK (ScriptHandlerMgr::HandlerType)((int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN+1) 
#define EVENT_USEREXT_CUSTOM_COMPONENT_ONENTER (ScriptHandlerMgr::HandlerType)((int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN+2)
#define EVENT_USEREXT_CUSTOM_COMPONENT_ONEXIT (ScriptHandlerMgr::HandlerType)((int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN+3)
#define EVENT_USEREXT_CUSTOM_COMPONENT_ONFRAME (ScriptHandlerMgr::HandlerType)((int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN+4)
#define EVENT_USEREXT_CUSTOM_ANIAMTION_ONMOVEMENT (ScriptHandlerMgr::HandlerType)((int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN+5)

#endif // EventDef_h__
