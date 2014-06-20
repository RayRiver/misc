
local COMPONENT_NAME = "StateMachine"

local StateMachine = class(COMPONENT_NAME, function() 
    local component = cc.Component:create()
    component:setName(COMPONENT_NAME)
    return component
end)

StateMachine.WILDCARD = "*"

function StateMachine:ctor()

end

function StateMachine:setupState(cfg)
    -- test
    cfg = 
    {
        events =
        {
            { name="doIdle", from={"walk","run"}, to="idle" },
            { name="doWalk", from="idle", to="walk" },
            { name="doWalk", from="run", to="walk" },
            { name="doRun", from="idle", to="run" },
            { name="doRun", from="walk", to="run" },
        }
    }
    
    
    self.map_ = {}
    self.events_ = cfg.events or {}
    
    for _, event in pairs(self.events_) do
        self:addEvent_(event)
    end
end

function StateMachine:doEvent(name, ...)

end

function StateMachine:addEvent_(event)
    -- parse from states
    local tFromStates = {}
    if type(event.from) == "table" then
        for _, name in pairs(event.from) do
            tFromStates[name] = true
        end
    elseif event.from then
        tFromStates[event.from] = true 
    else
        tFromStates[StateMachine.WILDCARD] = true   
    end
    
    -- save from self.map_
    self.map_[event.name] = self.map_[event.name] or {}
    for fromState, _ in pairs(tFromStates) do
        self.map_[event.name] = event.to or fromState
    end
    
end

return StateMachine
