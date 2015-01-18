
local MOVEMAP = {
    onMoveUp        = cc.KeyCode.KEY_W,
    onMoveDown      = cc.KeyCode.KEY_S,
    onMoveLeft      = cc.KeyCode.KEY_A,
    onMoveRight     = cc.KeyCode.KEY_D,
}

local SystemClass = class("ControllableSystem", function(system_name, com_name)
    return ECS.createSystemBase(system_name, com_name)
end)

function SystemClass:onAttached()
    self.m_keymap = {}
    for move, keycode in pairs(MOVEMAP) do
        self.m_keymap[keycode] = move
    end

    local listener = cc.EventListenerKeyboard:create()
    listener:registerScriptHandler(function(keycode, event)
        if self.m_keymap[keycode] then
            local com = self:getComByType("DynamicObjectCom")
            com[ self.m_keymap[keycode] ](com)
        end
    end, cc.Handler.EVENT_KEYBOARD_PRESSED)
    listener:registerScriptHandler(function(keycode, event)
        if self.m_keymap[keycode] then
            local com = self:getComByType("DynamicObjectCom")
            com[ self.m_keymap[keycode] .. "Stop" ](com)
        end
    end, cc.Handler.EVENT_KEYBOARD_RELEASED)
    cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(listener, 1)
    self.m_listener = listener
end

function SystemClass:onDetached()
    if self.m_listener then
        cc.Director:getInstance():getEventDispatcher():removeEventListener(self.m_listener)
        self.m_listener = nil
    end
end

return SystemClass
