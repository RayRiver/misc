#include "lua_userext_auto.hpp"
#include "GameEntity.h"
#include "EntityComponent.h"
#include "AnimationController.h"
#include "LuaValueList.h"
#include "ScriptFunctions.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_userext_GameEntity_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"GameEntity",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        GameEntity* ret = GameEntity::create();
        object_to_luaval<GameEntity>(tolua_S, "GameEntity",(GameEntity*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_GameEntity_create'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_GameEntity_constructor(lua_State* tolua_S)
{
    int argc = 0;
    GameEntity* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new GameEntity();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"GameEntity");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "GameEntity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_userext_GameEntity_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_userext_GameEntity_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (GameEntity)");
    return 0;
}

int lua_register_userext_GameEntity(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"GameEntity");
    tolua_cclass(tolua_S,"GameEntity","GameEntity","cc.Sprite",nullptr);

    tolua_beginmodule(tolua_S,"GameEntity");
        tolua_function(tolua_S,"create", lua_userext_GameEntity_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(GameEntity).name();
    g_luaType[typeName] = "GameEntity";
    g_typeCast["GameEntity"] = "GameEntity";
    return 1;
}

int lua_userext_EntityComponent_unregisterHandler(lua_State* tolua_S)
{
    int argc = 0;
    EntityComponent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"EntityComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (EntityComponent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_EntityComponent_unregisterHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->unregisterHandler(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unregisterHandler",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_EntityComponent_unregisterHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_EntityComponent_unregisterAllHandlers(lua_State* tolua_S)
{
    int argc = 0;
    EntityComponent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"EntityComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (EntityComponent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_EntityComponent_unregisterAllHandlers'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unregisterAllHandlers();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unregisterAllHandlers",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_EntityComponent_unregisterAllHandlers'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_EntityComponent_registerHandler(lua_State* tolua_S)
{
    int argc = 0;
    EntityComponent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"EntityComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (EntityComponent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_EntityComponent_registerHandler'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->registerHandler(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "registerHandler",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_EntityComponent_registerHandler'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_EntityComponent_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"EntityComponent",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        EntityComponent* ret = EntityComponent::create();
        object_to_luaval<EntityComponent>(tolua_S, "EntityComponent",(EntityComponent*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_EntityComponent_create'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_EntityComponent_constructor(lua_State* tolua_S)
{
    int argc = 0;
    EntityComponent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new EntityComponent();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"EntityComponent");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "EntityComponent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_userext_EntityComponent_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_userext_EntityComponent_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (EntityComponent)");
    return 0;
}

int lua_register_userext_EntityComponent(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"EntityComponent");
    tolua_cclass(tolua_S,"EntityComponent","EntityComponent","cc.Component",nullptr);

    tolua_beginmodule(tolua_S,"EntityComponent");
        tolua_function(tolua_S,"unregisterHandler",lua_userext_EntityComponent_unregisterHandler);
        tolua_function(tolua_S,"unregisterAllHandlers",lua_userext_EntityComponent_unregisterAllHandlers);
        tolua_function(tolua_S,"registerHandler",lua_userext_EntityComponent_registerHandler);
        tolua_function(tolua_S,"new",lua_userext_EntityComponent_constructor);
        tolua_function(tolua_S,"create", lua_userext_EntityComponent_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(EntityComponent).name();
    g_luaType[typeName] = "EntityComponent";
    g_typeCast["EntityComponent"] = "EntityComponent";
    return 1;
}

int lua_userext_AnimationController_load(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_load'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->load(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "load",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_load'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_play(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_play'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->play(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->play(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "play",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_play'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_pause(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_pause'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pause();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pause",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_pause'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_resume(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_resume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->resume();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "resume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_resume'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_checkCollider(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_checkCollider'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        bool ret = cobj->checkCollider(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "checkCollider",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_checkCollider'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_setMovementEventCallFunc(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_setMovementEventCallFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setMovementEventCallFunc(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMovementEventCallFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_setMovementEventCallFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_stop(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AnimationController*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_AnimationController_stop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stop();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "stop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_stop'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_AnimationController_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AnimationController",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        AnimationController* ret = AnimationController::create();
        object_to_luaval<AnimationController>(tolua_S, "AnimationController",(AnimationController*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_create'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_AnimationController_constructor(lua_State* tolua_S)
{
    int argc = 0;
    AnimationController* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new AnimationController();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"AnimationController");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "AnimationController",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_userext_AnimationController_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_userext_AnimationController_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AnimationController)");
    return 0;
}

int lua_register_userext_AnimationController(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"AnimationController");
    tolua_cclass(tolua_S,"AnimationController","AnimationController","EntityComponent",nullptr);

    tolua_beginmodule(tolua_S,"AnimationController");
        tolua_function(tolua_S,"load",lua_userext_AnimationController_load);
        tolua_function(tolua_S,"play",lua_userext_AnimationController_play);
        tolua_function(tolua_S,"pause",lua_userext_AnimationController_pause);
        tolua_function(tolua_S,"resume",lua_userext_AnimationController_resume);
        tolua_function(tolua_S,"checkCollider",lua_userext_AnimationController_checkCollider);
        tolua_function(tolua_S,"setMovementEventCallFunc",lua_userext_AnimationController_setMovementEventCallFunc);
        tolua_function(tolua_S,"stop",lua_userext_AnimationController_stop);
        tolua_function(tolua_S,"new",lua_userext_AnimationController_constructor);
        tolua_function(tolua_S,"create", lua_userext_AnimationController_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(AnimationController).name();
    g_luaType[typeName] = "AnimationController";
    g_typeCast["AnimationController"] = "AnimationController";
    return 1;
}

int lua_userext_LuaValueList_pushFloat(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaValueList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_LuaValueList_pushFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->pushFloat(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pushFloat",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_pushFloat'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_LuaValueList_clear(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaValueList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_LuaValueList_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clear();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_LuaValueList_pushString(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaValueList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_LuaValueList_pushString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->pushString(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pushString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_pushString'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_LuaValueList_pushInt(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaValueList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_LuaValueList_pushInt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->pushInt(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pushInt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_pushInt'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_LuaValueList_pushBoolean(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaValueList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_LuaValueList_pushBoolean'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->pushBoolean(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "pushBoolean",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_pushBoolean'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_LuaValueList_size(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaValueList",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaValueList*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_userext_LuaValueList_size'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->size();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "size",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_size'.",&tolua_err);
#endif

    return 0;
}
int lua_userext_LuaValueList_constructor(lua_State* tolua_S)
{
    int argc = 0;
    LuaValueList* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new LuaValueList();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"LuaValueList");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "LuaValueList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_userext_LuaValueList_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_userext_LuaValueList_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LuaValueList)");
    return 0;
}

int lua_register_userext_LuaValueList(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"LuaValueList");
    tolua_cclass(tolua_S,"LuaValueList","LuaValueList","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"LuaValueList");
        tolua_function(tolua_S,"pushFloat",lua_userext_LuaValueList_pushFloat);
        tolua_function(tolua_S,"clear",lua_userext_LuaValueList_clear);
        tolua_function(tolua_S,"pushString",lua_userext_LuaValueList_pushString);
        tolua_function(tolua_S,"pushInt",lua_userext_LuaValueList_pushInt);
        tolua_function(tolua_S,"pushBoolean",lua_userext_LuaValueList_pushBoolean);
        tolua_function(tolua_S,"size",lua_userext_LuaValueList_size);
        tolua_function(tolua_S,"new",lua_userext_LuaValueList_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(LuaValueList).name();
    g_luaType[typeName] = "LuaValueList";
    g_typeCast["LuaValueList"] = "LuaValueList";
    return 1;
}

int lua_userext_network_unregisterHandler(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        network::unregisterHandler();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "unregisterHandler",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_unregisterHandler'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_network_disconnect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        network::disconnect();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "disconnect",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_disconnect'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_network_stop(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        network::stop();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "stop",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_stop'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_network_send(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        const LuaValueList* arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0);
        ok &= luaval_to_object<const LuaValueList>(tolua_S, 3, "LuaValueList",&arg1);
        if(!ok)
            return 0;
        network::send(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "send",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_send'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_network_start(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        network::start();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "start",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_start'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_network_connect(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        unsigned short arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_ushort(tolua_S, 3, &arg1);
        if(!ok)
            return 0;
        network::connect(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "connect",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_connect'.",&tolua_err);
#endif
    return 0;
}
int lua_userext_network_registerHandler(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        network::registerHandler(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "registerHandler",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_userext_network_registerHandler'.",&tolua_err);
#endif
    return 0;
}
static int lua_userext_network_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (network)");
    return 0;
}

int lua_register_userext_network(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"network");
    tolua_cclass(tolua_S,"network","network","",nullptr);

    tolua_beginmodule(tolua_S,"network");
        tolua_function(tolua_S,"unregisterHandler", lua_userext_network_unregisterHandler);
        tolua_function(tolua_S,"disconnect", lua_userext_network_disconnect);
        tolua_function(tolua_S,"stop", lua_userext_network_stop);
        tolua_function(tolua_S,"send", lua_userext_network_send);
        tolua_function(tolua_S,"start", lua_userext_network_start);
        tolua_function(tolua_S,"connect", lua_userext_network_connect);
        tolua_function(tolua_S,"registerHandler", lua_userext_network_registerHandler);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(network).name();
    g_luaType[typeName] = "network";
    g_typeCast["network"] = "network";
    return 1;
}
TOLUA_API int register_all_userext(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_userext_GameEntity(tolua_S);
	lua_register_userext_EntityComponent(tolua_S);
	lua_register_userext_AnimationController(tolua_S);
	lua_register_userext_LuaValueList(tolua_S);
	lua_register_userext_network(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

