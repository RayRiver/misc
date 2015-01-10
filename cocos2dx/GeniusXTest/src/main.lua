
cc.FileUtils:getInstance():addSearchPath("src")
cc.FileUtils:getInstance():addSearchPath("res")

-- CC_USE_DEPRECATED_API = true
require "cocos.init"

local __require = require
local require_table = {}
require = function(package_name)
    require_table[package_name] = package_name
    return __require(package_name)
end

function assert(cond, msg)
    if not cond then
        --msg = "assert failed: " .. tostring(msg)
        msg = msg or "[unknown error]"
        error(msg)
    end
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    local content = {}
    table.insert(content, "--------------------------------------------------------------------------------\n")
    table.insert(content, "LUA ERROR: " .. tostring(msg) .. "\n\n")
    table.insert(content, debug.traceback() .. "\n")
    table.insert(content, "--------------------------------------------------------------------------------\n")
    msg = table.concat(content)
    print(msg)
    helper.show_error(msg)
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

    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(function(keycode, event)
        if keycode == cc.KeyCode.KEY_F12 then
            local backup = {}
            for package_name, _ in pairs(require_table) do
                print("package loaded: ", package_name)
                table.insert(backup, package_name)
                require_table[package_name] = nil
                package.loaded[package_name] = nil
            end
            for _, package_name in ipairs(backup) do
                print("requring: ", package_name)
                require(package_name)
            end
        end
    end, cc.Handler.EVENT_KEYBOARD_RELEASED)
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, 1)

    require("app").new():run()

end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
