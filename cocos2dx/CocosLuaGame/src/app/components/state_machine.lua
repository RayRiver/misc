
local COMPONENT_NAME = "StateMachine"

local StateMachine = class(COMPONENT_NAME, function() 
    local component = cc.Component:create()
    component:setName(COMPONENT_NAME)
    return component
end)

function StateMachine:ctor()

end

function StateMachine:setupState(cfg)

end

function StateMachine:doEvent(name, ...)

end

return StateMachine
