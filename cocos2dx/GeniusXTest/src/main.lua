
cc.FileUtils:getInstance():addSearchPath("src")
cc.FileUtils:getInstance():addSearchPath("res")

-- CC_USE_DEPRECATED_API = true
require "cocos.init"

-- cclog
local cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
    return msg
end

local function main()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    -- initialize director
    local director = cc.Director:getInstance()

    --turn on display FPS
    director:setDisplayStats(true)

    --set FPS. the default value is 1.0/60 if you don't call this
    director:setAnimationInterval(1.0 / 60)
    
    cc.Director:getInstance():getOpenGLView():setDesignResolutionSize(960, 640, 1)
    
    require("framework.init")
    
    -- 初始化game system
    local game_system = gx.GameSystem:getInstance()
    local ecs = game_system:getECS()
    ecs:registerSystem(require("Systems.EntrySystem").new())
    ecs:registerCom(require("Coms.EntryCom").new())

    -- 测试
    local scene = require("Scenes.EntryScene").new()
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(scene)
    else
        cc.Director:getInstance():runWithScene(scene)
    end

    --[[
    --create scene 
    local scene = require("GameScene")
    local gameScene = scene.create()
    gameScene:playBgMusic()
    
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(gameScene)
    else
        cc.Director:getInstance():runWithScene(gameScene)
    end
    --]]

end


local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
