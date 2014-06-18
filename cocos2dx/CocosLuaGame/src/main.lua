require "Cocos2d"
require "Cocos2dConstants"

-- cclog
cclog = function(...)
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

local function test_network()
    require("network")
    network.register(network.MSG_LOGIN_RESP, function(args)
        cclog("0xA006: username=%s", tostring(args[4]))
        --network.disconnect()
    end)
    network.connect("192.168.6.227", 9090)
end

local function main()
    collectgarbage("collect")
    
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    
    --cc.Director:getInstance():getOpenGLView():setDesignResolutionSize(480, 320, 0)
    
    cc.FileUtils:getInstance():addSearchPath("src")
    cc.FileUtils:getInstance():addSearchPath("res")
	cc.FileUtils:getInstance():addSearchResolutionsOrder("src");
	cc.FileUtils:getInstance():addSearchResolutionsOrder("res");
	
	require("app.app").new():run()
    --test_network()
end


local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
