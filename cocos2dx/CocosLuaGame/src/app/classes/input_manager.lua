
local ACTIONS = {
    up =    
    { 
        keys = { cc.KeyCode.KEY_W, cc.KeyCode.KEY_CAPITAL_W },
    },
    down =    
    { 
        keys = { cc.KeyCode.KEY_S, cc.KeyCode.KEY_CAPITAL_S },
    },
    left = 
    {
        keys = { cc.KeyCode.KEY_A, cc.KeyCode.KEY_CAPITAL_A },
    },
    right = 
    {
        keys = { cc.KeyCode.KEY_D, cc.KeyCode.KEY_CAPITAL_D },
    },
    action1 = 
    {
        keys = { cc.KeyCode.KEY_J, cc.KeyCode.KEY_CAPITAL_J },
    },
    action2 = 
    {
        keys = { cc.KeyCode.KEY_K, cc.KeyCode.KEY_CAPITAL_K },
    },
    action3 = 
    {
        keys = { cc.KeyCode.KEY_L, cc.KeyCode.KEY_CAPITAL_L },
    },
    esc = 
    {
        keys = { cc.KeyCode.KEY_ESCAPE },
    },
}

local ACTION_MAP = {}
local ACTION_ACTIVE_MAP = {}

-- actions map
local BEGAN_ACTIONS = {}
local ENDED_ACTIONS = {}

local OBJECT_NAME = "InputManager"

local ObjectClass = class(OBJECT_NAME, function() 
    return display.newNode()
end)

ObjectClass.UP = "up"
ObjectClass.DOWN = "down"
ObjectClass.LEFT = "left"
ObjectClass.RIGHT = "right"
ObjectClass.ACTION1 = "action1"
ObjectClass.ACTION2 = "action2"
ObjectClass.ACTION3 = "action3"
ObjectClass.ESC = "esc"

function ObjectClass:ctor()
    self:updateActionMap()
    
    -- input layer
    local layer = display.newLayer()
    self:addChild(layer)
    
    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(function(key, event) 
        local action = ACTION_MAP[key]
        if not self.isPaused and BEGAN_ACTIONS[action] then 
            BEGAN_ACTIONS[action]() 
            ACTION_ACTIVE_MAP[action] = true
        end
    end, cc.Handler.EVENT_KEYBOARD_PRESSED)
    listener:registerScriptHandler(function(key, event) 
        local action = ACTION_MAP[key]
        if not self.isPaused and ENDED_ACTIONS[action] then 
            ENDED_ACTIONS[action]() 
            ACTION_ACTIVE_MAP[action] = false
        end
    end, cc.Handler.EVENT_KEYBOARD_RELEASED)
    layer:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, layer)
end

function ObjectClass:updateActionMap()
    ACTION_MAP = {}
    for action, action_table in pairs(ACTIONS) do
        for _, key in pairs(action_table.keys) do
            if ACTION_MAP[key] then
                printInfo("key %d already defined for action %s", key, action)
            end
            ACTION_MAP[key] = action
        end
    end
end

function ObjectClass:registerInputBeganHandler(action, handler)
    assert(type(handler) == "function", "registerInputBegan error, handler is not a function")
    BEGAN_ACTIONS[action] = handler
end

function ObjectClass:registerInputEndedHandler(action, handler)
    assert(type(handler) == "function", "registerInputEnded error, handler is not a function")
    ENDED_ACTIONS[action] = handler
end

function ObjectClass:clearAllHandlers()
    BEGAN_ACTIONS = {}
    ENDED_ACTIONS = {}
end

function ObjectClass:pause()
    self.isPaused = true
end

function ObjectClass:resume()
    self.isPaused = false
end

function ObjectClass:isActionActive(action)
    return ACTION_ACTIVE_MAP[action]
end

return ObjectClass
