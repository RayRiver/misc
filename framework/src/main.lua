
-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
    return msg
end

local function main()
    collectgarbage("collect")
    
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    
	cc.FileUtils:getInstance():addSearchPath("src");
    cc.FileUtils:getInstance():addSearchPath("res");

    require("app.app").new():run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
