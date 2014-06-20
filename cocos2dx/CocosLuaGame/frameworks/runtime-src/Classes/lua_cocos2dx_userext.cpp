/*
** Lua binding: lua_cocos2dx_userext
** Generated automatically by tolua++-1.0.92 on 06/19/14 20:55:45.
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

#include "ScriptFunctions.h"
#include "LuaValueList.h"
#include "NetManager.h"
#include "NetImp.h"
#include "GameEntity.h"
#include "EntityComponent.h"
#include "AnimationController.h"

USING_NS_CC;



/* Exported function */
TOLUA_API int  tolua_lua_cocos2dx_userext_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_LuaValueList (lua_State* tolua_S)
{
 LuaValueList* self = (LuaValueList*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_AnimationController (lua_State* tolua_S)
{
 AnimationController* self = (AnimationController*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"LuaValueList");
 tolua_usertype(tolua_S,"cc.Ref");
 tolua_usertype(tolua_S,"EntityComponent");
 tolua_usertype(tolua_S,"AnimationController");
 
 tolua_usertype(tolua_S,"cc.Component");
 tolua_usertype(tolua_S,"cc.Sprite");
 tolua_usertype(tolua_S,"GameEntity");
}

/* method: new of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_new00
static int tolua_lua_cocos2dx_userext_LuaValueList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaValueList* tolua_ret = (LuaValueList*)  Mtolua_new((LuaValueList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaValueList");
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

/* method: new_local of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_new00_local
static int tolua_lua_cocos2dx_userext_LuaValueList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaValueList* tolua_ret = (LuaValueList*)  Mtolua_new((LuaValueList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaValueList");
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

/* method: push_back of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_pushInt00
static int tolua_lua_cocos2dx_userext_LuaValueList_pushInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaValueList* self = (LuaValueList*)  tolua_tousertype(tolua_S,1,0);
  int val = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_pushFloat00
static int tolua_lua_cocos2dx_userext_LuaValueList_pushFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaValueList* self = (LuaValueList*)  tolua_tousertype(tolua_S,1,0);
  float val = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_pushBoolean00
static int tolua_lua_cocos2dx_userext_LuaValueList_pushBoolean00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaValueList* self = (LuaValueList*)  tolua_tousertype(tolua_S,1,0);
  bool val = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushBoolean'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_pushString00
static int tolua_lua_cocos2dx_userext_LuaValueList_pushString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaValueList* self = (LuaValueList*)  tolua_tousertype(tolua_S,1,0);
  const char* val = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_size00
static int tolua_lua_cocos2dx_userext_LuaValueList_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LuaValueList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LuaValueList* self = (const LuaValueList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  LuaValueList */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_LuaValueList_clear00
static int tolua_lua_cocos2dx_userext_LuaValueList_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaValueList* self = (LuaValueList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_start */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_start00
static int tolua_lua_cocos2dx_userext_network_start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   network_start();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_stop */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_stop00
static int tolua_lua_cocos2dx_userext_network_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   network_stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_connect */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_connect00
static int tolua_lua_cocos2dx_userext_network_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* hostname = ((const char*)  tolua_tostring(tolua_S,1,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  {
   network_connect(hostname,port);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_disconnect */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_disconnect00
static int tolua_lua_cocos2dx_userext_network_disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   network_disconnect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_send */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_send00
static int tolua_lua_cocos2dx_userext_network_send00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const LuaValueList",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int id = ((unsigned int)  tolua_tonumber(tolua_S,1,0));
  const LuaValueList* args = ((const LuaValueList*)  tolua_tousertype(tolua_S,2,0));
  {
   network_send(id,*args);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'send'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_registerHandler */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_registerHandler00
static int tolua_lua_cocos2dx_userext_network_registerHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !toluafix_isfunction(tolua_S,1,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,1,0));
  {
   network_registerHandler(handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: network_unregisterHandler */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_network_unregisterHandler00
static int tolua_lua_cocos2dx_userext_network_unregisterHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   network_unregisterHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  GameEntity */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_GameEntity_create00
static int tolua_lua_cocos2dx_userext_GameEntity_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GameEntity",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GameEntity* tolua_ret = (GameEntity*)  GameEntity::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GameEntity");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  EntityComponent */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_EntityComponent_create00
static int tolua_lua_cocos2dx_userext_EntityComponent_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EntityComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EntityComponent* tolua_ret = (EntityComponent*)  EntityComponent::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EntityComponent");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerHandler of class  EntityComponent */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_EntityComponent_registerHandler00
static int tolua_lua_cocos2dx_userext_EntityComponent_registerHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EntityComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EntityComponent* self = (EntityComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* event_name = ((const char*)  tolua_tostring(tolua_S,2,0));
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerHandler'", NULL);
#endif
  {
   self->registerHandler(event_name,handler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterHandler of class  EntityComponent */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_EntityComponent_unregisterHandler00
static int tolua_lua_cocos2dx_userext_EntityComponent_unregisterHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EntityComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EntityComponent* self = (EntityComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* event_name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterHandler'", NULL);
#endif
  {
   self->unregisterHandler(event_name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterAllHandlers of class  EntityComponent */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_EntityComponent_unregisterAllHandlers00
static int tolua_lua_cocos2dx_userext_EntityComponent_unregisterAllHandlers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EntityComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EntityComponent* self = (EntityComponent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterAllHandlers'", NULL);
#endif
  {
   self->unregisterAllHandlers();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterAllHandlers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_create00
static int tolua_lua_cocos2dx_userext_AnimationController_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationController* tolua_ret = (AnimationController*)  AnimationController::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationController");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_new00
static int tolua_lua_cocos2dx_userext_AnimationController_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationController* tolua_ret = (AnimationController*)  Mtolua_new((AnimationController)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationController");
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

/* method: new_local of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_new00_local
static int tolua_lua_cocos2dx_userext_AnimationController_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AnimationController* tolua_ret = (AnimationController*)  Mtolua_new((AnimationController)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationController");
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

/* method: load of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_load00
static int tolua_lua_cocos2dx_userext_AnimationController_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const char* armatureName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'", NULL);
#endif
  {
   self->load(armatureName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_play00
static int tolua_lua_cocos2dx_userext_AnimationController_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const char* movementName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int playMode = ((int)  tolua_tonumber(tolua_S,3,AnimationController::Default));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play(movementName,playMode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_pause00
static int tolua_lua_cocos2dx_userext_AnimationController_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_resume00
static int tolua_lua_cocos2dx_userext_AnimationController_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_lua_cocos2dx_userext_AnimationController_stop00
static int tolua_lua_cocos2dx_userext_AnimationController_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_lua_cocos2dx_userext_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"LuaValueList","LuaValueList","cc.Ref",tolua_collect_LuaValueList);
  #else
  tolua_cclass(tolua_S,"LuaValueList","LuaValueList","cc.Ref",NULL);
  #endif
  tolua_beginmodule(tolua_S,"LuaValueList");
   tolua_function(tolua_S,"new",tolua_lua_cocos2dx_userext_LuaValueList_new00);
   tolua_function(tolua_S,"new_local",tolua_lua_cocos2dx_userext_LuaValueList_new00_local);
   tolua_function(tolua_S,".call",tolua_lua_cocos2dx_userext_LuaValueList_new00_local);
   tolua_function(tolua_S,"pushInt",tolua_lua_cocos2dx_userext_LuaValueList_pushInt00);
   tolua_function(tolua_S,"pushFloat",tolua_lua_cocos2dx_userext_LuaValueList_pushFloat00);
   tolua_function(tolua_S,"pushBoolean",tolua_lua_cocos2dx_userext_LuaValueList_pushBoolean00);
   tolua_function(tolua_S,"pushString",tolua_lua_cocos2dx_userext_LuaValueList_pushString00);
   tolua_function(tolua_S,"size",tolua_lua_cocos2dx_userext_LuaValueList_size00);
   tolua_function(tolua_S,"clear",tolua_lua_cocos2dx_userext_LuaValueList_clear00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"network",0);
  tolua_beginmodule(tolua_S,"network");
   tolua_function(tolua_S,"start",tolua_lua_cocos2dx_userext_network_start00);
   tolua_function(tolua_S,"stop",tolua_lua_cocos2dx_userext_network_stop00);
   tolua_function(tolua_S,"connect",tolua_lua_cocos2dx_userext_network_connect00);
   tolua_function(tolua_S,"disconnect",tolua_lua_cocos2dx_userext_network_disconnect00);
   tolua_function(tolua_S,"send",tolua_lua_cocos2dx_userext_network_send00);
   tolua_function(tolua_S,"registerHandler",tolua_lua_cocos2dx_userext_network_registerHandler00);
   tolua_function(tolua_S,"unregisterHandler",tolua_lua_cocos2dx_userext_network_unregisterHandler00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"GameEntity","GameEntity","cc.Sprite",NULL);
  tolua_beginmodule(tolua_S,"GameEntity");
   tolua_function(tolua_S,"create",tolua_lua_cocos2dx_userext_GameEntity_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EntityComponent","EntityComponent","cc.Component",NULL);
  tolua_beginmodule(tolua_S,"EntityComponent");
   tolua_function(tolua_S,"create",tolua_lua_cocos2dx_userext_EntityComponent_create00);
   tolua_function(tolua_S,"registerHandler",tolua_lua_cocos2dx_userext_EntityComponent_registerHandler00);
   tolua_function(tolua_S,"unregisterHandler",tolua_lua_cocos2dx_userext_EntityComponent_unregisterHandler00);
   tolua_function(tolua_S,"unregisterAllHandlers",tolua_lua_cocos2dx_userext_EntityComponent_unregisterAllHandlers00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AnimationController","AnimationController","EntityComponent",tolua_collect_AnimationController);
  #else
  tolua_cclass(tolua_S,"AnimationController","AnimationController","EntityComponent",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AnimationController");
   tolua_constant(tolua_S,"Default",AnimationController::Default);
   tolua_constant(tolua_S,"Once",AnimationController::Once);
   tolua_constant(tolua_S,"Loop",AnimationController::Loop);
   tolua_function(tolua_S,"create",tolua_lua_cocos2dx_userext_AnimationController_create00);
   tolua_function(tolua_S,"new",tolua_lua_cocos2dx_userext_AnimationController_new00);
   tolua_function(tolua_S,"new_local",tolua_lua_cocos2dx_userext_AnimationController_new00_local);
   tolua_function(tolua_S,".call",tolua_lua_cocos2dx_userext_AnimationController_new00_local);
   tolua_function(tolua_S,"load",tolua_lua_cocos2dx_userext_AnimationController_load00);
   tolua_function(tolua_S,"play",tolua_lua_cocos2dx_userext_AnimationController_play00);
   tolua_function(tolua_S,"pause",tolua_lua_cocos2dx_userext_AnimationController_pause00);
   tolua_function(tolua_S,"resume",tolua_lua_cocos2dx_userext_AnimationController_resume00);
   tolua_function(tolua_S,"stop",tolua_lua_cocos2dx_userext_AnimationController_stop00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_lua_cocos2dx_userext (lua_State* tolua_S) {
 return tolua_lua_cocos2dx_userext_open(tolua_S);
};
#endif

