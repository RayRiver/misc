
local ACTIONS = 
{
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
local KEYMAP = {}

local InputLayer = class("InputLayer", function() 
    local obj = display.newLayer()
    return obj
end)

function InputLayer:ctor()
    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(function(keycode, event) 
        self:onKeyPressed(keycode, event)
    end, cc.Handler.EVENT_KEYBOARD_PRESSED)
    listener:registerScriptHandler(function(keycode, event) 
        self:onKeyReleased(keycode, event)
    end, cc.Handler.EVENT_KEYBOARD_RELEASED)
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
    
    
    self:updateKeyMap()
end

function InputLayer:updateKeyMap()
    KEYMAP = {}
    for action, action_table in pairs(ACTIONS) do
        for _, key in pairs(action_table.keys) do
            if KEYMAP[key] then
                printInfo("key %d already defined for action %s", key, action)
            end
            KEYMAP[key] = action
        end
    end
end

function InputLayer:onKeyPressed(keycode, event)
    if KEYMAP[keycode] and type(self.pressedHandler) == "function" then
        self.pressedHandler(KEYMAP[keycode])
    end 
end

function InputLayer:onKeyReleased(keycode, event)
    if KEYMAP[keycode] and type(self.releasedHandler) == "function" then
        self.releasedHandler(KEYMAP[keycode])
    end 
end

function InputLayer:registerPressedHandler(fn)
    self.pressedHandler = fn
end

function InputLayer:registerReleasedHandler(fn)
    self.releasedHandler = fn
end

return InputLayer
