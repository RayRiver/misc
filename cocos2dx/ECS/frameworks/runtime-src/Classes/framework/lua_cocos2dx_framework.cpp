/*
** Lua binding: lua_cocos2dx_framework
** Generated automatically by tolua++-1.0.92 on 12/18/14 21:42:09.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "tolua_fix.h"

#include "cocos2d.h"
#include "CCLuaValue.h"
#include "LuaBasicConversions.h"

#include "GXMacros.h"

#include "ECS/Entity.h"
#include "ECS/ECSManager.h"

USING_NS_CC;
USING_NS_GX;



/* Exported function */
TOLUA_API int  tolua_lua_cocos2dx_framework_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ECSManager (lua_State* tolua_S)
{
 ECSManager* self = (ECSManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Entity");
 tolua_usertype(tolua_S,"cc.Ref");
 tolua_usertype(tolua_S,"ECSManager");
}

/* method: sendEvent of class  Entity */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_framework_gx_Entity_sendEvent00
static int tolua_lua_cocos2dx_framework_gx_Entity_sendEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Entity",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Entity* self = (Entity*)  tolua_tousertype(tolua_S,1,0);
  const std::string eventName = ((const std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendEvent'", NULL);
#endif
  {
   self->sendEvent(eventName);
   tolua_pushcppstring(tolua_S,(const char*)eventName);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ECSManager */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_framework_gx_ECSManager_new00
static int tolua_lua_cocos2dx_framework_gx_ECSManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ECSManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ECSManager* tolua_ret = (ECSManager*)  Mtolua_new((ECSManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ECSManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ECSManager */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_framework_gx_ECSManager_new00_local
static int tolua_lua_cocos2dx_framework_gx_ECSManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ECSManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ECSManager* tolua_ret = (ECSManager*)  Mtolua_new((ECSManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ECSManager");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createEntity of class  ECSManager */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_framework_gx_ECSManager_createEntity00
static int tolua_lua_cocos2dx_framework_gx_ECSManager_createEntity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ECSManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ECSManager* self = (ECSManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createEntity'", NULL);
#endif
  {
   Entity* tolua_ret = (Entity*)  self->createEntity();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Entity");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeEntity of class  ECSManager */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_framework_gx_ECSManager_removeEntity00
static int tolua_lua_cocos2dx_framework_gx_ECSManager_removeEntity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ECSManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Entity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ECSManager* self = (ECSManager*)  tolua_tousertype(tolua_S,1,0);
  Entity* entity = ((Entity*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeEntity'", NULL);
#endif
  {
   self->removeEntity(entity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeEntity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_lua_cocos2dx_framework_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"gx",0);
  tolua_beginmodule(tolua_S,"gx");
   tolua_cclass(tolua_S,"Entity","Entity","cc.Ref",NULL);
   tolua_beginmodule(tolua_S,"Entity");
    tolua_function(tolua_S,"sendEvent",tolua_lua_cocos2dx_framework_gx_Entity_sendEvent00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"gx",0);
  tolua_beginmodule(tolua_S,"gx");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ECSManager","ECSManager","cc.Ref",tolua_collect_ECSManager);
   #else
   tolua_cclass(tolua_S,"ECSManager","ECSManager","cc.Ref",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ECSManager");
    tolua_function(tolua_S,"new",tolua_lua_cocos2dx_framework_gx_ECSManager_new00);
    tolua_function(tolua_S,"new_local",tolua_lua_cocos2dx_framework_gx_ECSManager_new00_local);
    tolua_function(tolua_S,".call",tolua_lua_cocos2dx_framework_gx_ECSManager_new00_local);
    tolua_function(tolua_S,"createEntity",tolua_lua_cocos2dx_framework_gx_ECSManager_createEntity00);
    tolua_function(tolua_S,"removeEntity",tolua_lua_cocos2dx_framework_gx_ECSManager_removeEntity00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_lua_cocos2dx_framework (lua_State* tolua_S) {
 return tolua_lua_cocos2dx_framework_open(tolua_S);
};
#endif

