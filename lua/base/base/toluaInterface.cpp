/*
** Lua binding: toluaInterface
** Generated automatically by tolua++-1.0.92 on 04/22/14 18:55:03.
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

extern "C" {
#include "tolua_fix.h"
}

#include "ScriptInterface.h"
#include "VarList.h"






/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_VarList (lua_State* tolua_S)
{
 VarList* self = (VarList*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 
 tolua_usertype(tolua_S,"VarList");
}

/* function: sys_sleep */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_sys_sleep00
static int tolua_toluaInterface_sys_sleep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int msec = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   sys_sleep(msec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sleep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: net_connect */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_net_connect00
static int tolua_toluaInterface_net_connect00(lua_State* tolua_S)
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
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  int port = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   net_connect(name,port);
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

/* function: net_disconnect */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_net_disconnect00
static int tolua_toluaInterface_net_disconnect00(lua_State* tolua_S)
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
   net_disconnect();
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

/* function: event_register */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_event_register00
static int tolua_toluaInterface_event_register00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  LUA_FUNCTION fn = (  toluafix_ref_function(tolua_S,2,0));
  {
   event_register(name,fn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'register'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: event_unregister */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_event_unregister00
static int tolua_toluaInterface_event_unregister00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   event_unregister(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregister'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: event_call */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_event_call00
static int tolua_toluaInterface_event_call00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* name = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   event_call(name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'call'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_new00
static int tolua_toluaInterface_VarList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   VarList* tolua_ret = (VarList*)  Mtolua_new((VarList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VarList");
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

/* method: new_local of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_new00_local
static int tolua_toluaInterface_VarList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   VarList* tolua_ret = (VarList*)  Mtolua_new((VarList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VarList");
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

/* method: addInt8 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addInt800
static int tolua_toluaInterface_VarList_addInt800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  double val = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInt8'", NULL);
#endif
  {
   self->addInt8(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInt8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInt16 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addInt1600
static int tolua_toluaInterface_VarList_addInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  double val = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInt16'", NULL);
#endif
  {
   self->addInt16(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInt16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInt32 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addInt3200
static int tolua_toluaInterface_VarList_addInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  double val = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInt32'", NULL);
#endif
  {
   self->addInt32(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addInt64 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addInt6400
static int tolua_toluaInterface_VarList_addInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  double val = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addInt64'", NULL);
#endif
  {
   self->addInt64(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addFloat of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addFloat00
static int tolua_toluaInterface_VarList_addFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  double val = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFloat'", NULL);
#endif
  {
   self->addFloat(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addDouble of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addDouble00
static int tolua_toluaInterface_VarList_addDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  double val = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addDouble'", NULL);
#endif
  {
   self->addDouble(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addString of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_addString00
static int tolua_toluaInterface_VarList_addString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  const char* val = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addString'", NULL);
#endif
  {
   self->addString(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toInt8 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toInt800
static int tolua_toluaInterface_VarList_toInt800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toInt8'", NULL);
#endif
  {
   double tolua_ret = (double)  self->toInt8(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toInt8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toInt16 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toInt1600
static int tolua_toluaInterface_VarList_toInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toInt16'", NULL);
#endif
  {
   double tolua_ret = (double)  self->toInt16(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toInt16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toInt32 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toInt3200
static int tolua_toluaInterface_VarList_toInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toInt32'", NULL);
#endif
  {
   double tolua_ret = (double)  self->toInt32(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toInt64 of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toInt6400
static int tolua_toluaInterface_VarList_toInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toInt64'", NULL);
#endif
  {
   double tolua_ret = (double)  self->toInt64(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toFloat of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toFloat00
static int tolua_toluaInterface_VarList_toFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toFloat'", NULL);
#endif
  {
   double tolua_ret = (double)  self->toFloat(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toDouble of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toDouble00
static int tolua_toluaInterface_VarList_toDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toDouble'", NULL);
#endif
  {
   double tolua_ret = (double)  self->toDouble(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: toString of class  VarList */
#ifndef TOLUA_DISABLE_tolua_toluaInterface_VarList_toString00
static int tolua_toluaInterface_VarList_toString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VarList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VarList* self = (VarList*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'toString'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->toString(index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'toString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_toluaInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"sys",0);
  tolua_beginmodule(tolua_S,"sys");
   tolua_function(tolua_S,"sleep",tolua_toluaInterface_sys_sleep00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"net",0);
  tolua_beginmodule(tolua_S,"net");
   tolua_function(tolua_S,"connect",tolua_toluaInterface_net_connect00);
   tolua_function(tolua_S,"disconnect",tolua_toluaInterface_net_disconnect00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"event",0);
  tolua_beginmodule(tolua_S,"event");
   tolua_function(tolua_S,"register",tolua_toluaInterface_event_register00);
   tolua_function(tolua_S,"unregister",tolua_toluaInterface_event_unregister00);
   tolua_function(tolua_S,"call",tolua_toluaInterface_event_call00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"VarList","VarList","",tolua_collect_VarList);
  #else
  tolua_cclass(tolua_S,"VarList","VarList","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"VarList");
   tolua_function(tolua_S,"new",tolua_toluaInterface_VarList_new00);
   tolua_function(tolua_S,"new_local",tolua_toluaInterface_VarList_new00_local);
   tolua_function(tolua_S,".call",tolua_toluaInterface_VarList_new00_local);
   tolua_function(tolua_S,"addInt8",tolua_toluaInterface_VarList_addInt800);
   tolua_function(tolua_S,"addInt16",tolua_toluaInterface_VarList_addInt1600);
   tolua_function(tolua_S,"addInt32",tolua_toluaInterface_VarList_addInt3200);
   tolua_function(tolua_S,"addInt64",tolua_toluaInterface_VarList_addInt6400);
   tolua_function(tolua_S,"addFloat",tolua_toluaInterface_VarList_addFloat00);
   tolua_function(tolua_S,"addDouble",tolua_toluaInterface_VarList_addDouble00);
   tolua_function(tolua_S,"addString",tolua_toluaInterface_VarList_addString00);
   tolua_function(tolua_S,"toInt8",tolua_toluaInterface_VarList_toInt800);
   tolua_function(tolua_S,"toInt16",tolua_toluaInterface_VarList_toInt1600);
   tolua_function(tolua_S,"toInt32",tolua_toluaInterface_VarList_toInt3200);
   tolua_function(tolua_S,"toInt64",tolua_toluaInterface_VarList_toInt6400);
   tolua_function(tolua_S,"toFloat",tolua_toluaInterface_VarList_toFloat00);
   tolua_function(tolua_S,"toDouble",tolua_toluaInterface_VarList_toDouble00);
   tolua_function(tolua_S,"toString",tolua_toluaInterface_VarList_toString00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_toluaInterface (lua_State* tolua_S) {
 return tolua_toluaInterface_open(tolua_S);
};
#endif

