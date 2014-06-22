
local COMPONENT_NAME = "StateMachine"

local StateMachine = class(COMPONENT_NAME, function() 
    local component = cc.Component:create()
    component:setName(COMPONENT_NAME)
    return component
end)

StateMachine.WILDCARD = "*"
StateMachine.STATE_READY = "_"

-- the event transitioned successfully from one state to another
StateMachine.SUCCEEDED = 1
-- the event was successfull but no state transition was necessary
StateMachine.NOTRANSITION = 2
-- the event was cancelled by the caller in a beforeEvent callback
StateMachine.CANCELLED = 3
-- the event is asynchronous and the caller is in control of when the transition occurs
StateMachine.PENDING = 4
-- the event was failure
StateMachine.FAILURE = 5

-- caller tried to fire an event that was innapropriate in the current state
StateMachine.INVALID_TRANSITION_ERROR = "INVALID_TRANSITION_ERROR"
-- caller tried to fire an event while an async transition was still pending
StateMachine.PENDING_TRANSITION_ERROR = "PENDING_TRANSITION_ERROR"
-- caller provided callback function threw an exception
StateMachine.INVALID_CALLBACK_ERROR = "INVALID_CALLBACK_ERROR"

function StateMachine:ctor()
    
end

function StateMachine:setupState(cfg)
    self.map_ = {}
    self.events_ = cfg.events or {}
    self.current_ = StateMachine.STATE_READY
    self.callbacks_ = cfg.callbacks or {}
    self.inTransition_ = false
    
    for _, event in ipairs(self.events_) do
        self:addEvent_(event)
    end
end

function StateMachine:isReady()
    return self.current_ ~= StateMachine.STATE_READY
end

function StateMachine:getState()
    return self.current_
end

function StateMachine:isState(state)
    if type(state) == "table" then
        for _, s in ipairs(state) do
            if s == self.current_ then return true end
        end
        return false
    else
        return self.current_ == state
    end
end

function StateMachine:canDoEvent(name)
    return not self.inTransition_ and
        (self.map_[name][self.current_] ~= nil or self.map_[name][StateMachine.WILDCARD] ~= nil)
end

function StateMachine:doEvent(name, ...)
    assert(self.map_[name] ~= nil, string.format("StateMachine:doEvent() - invalid event %s", tostring(name)))
    
    local from = self.current_
    local map = self.map_[name]
    local to = (map[from] or map[StateMachine.WILDCARD]) or from
    local args = {...}
    
    local event =
    {
        name = name,
        from = from,
        to = to,
        args = args,
    }
    
    if self.inTransition then
        self:onError_(event,
            StateMachine.PENDING_TRANSITION_ERROR,
            "event " .. name .. " inappropriate because previous transition did not complete")
        return StateMachine.FAILURE
    end
    
    if not self:canDoEvent(name) then
        self:onError_(event,
            StateMachine.INVALID_TRANSITION_ERROR,
            "event " .. name .. " inappropriate in current state " .. self.current_)
        return StateMachine.FAILURE
    end
    
    if self:beforeEvent_(event) == false then
        return StateMachine.CANCELLED
    end
    
    if from == to then
        self:afterEvent_(event)
        return StateMachine.NOTRANSITION
    end
    
    event.transition = function()
        self.inTransition_  = false
        self.current_ = to
        self:enterState_(event)
        self:changeState_(event)
        self:afterEvent_(event)
        return StateMachine.SUCCEEDED
    end
    
    self.inTransition_ = true
    local leave = self:leaveState_(event) 
    if leave == false then
        event.transition = nil
        event.cancel = nil
        self.inTransition_ = false
        return StateMachine.CANCELLED
    else
        if event.transition then
            return event.transition()
        else
            self.inTransition_ = false
        end
    end
end

function StateMachine:addEvent_(event)
    -- parse from states to table
    local fromStates = {}
    if type(event.from) == "table" then
        for _, fromState in ipairs(event.from) do
            fromStates[fromState] = true
        end
    elseif event.from then
        fromStates[event.from] = true
    else
        fromStates[StateMachine.WILDCARD] = true
    end
    
    -- parse eventName,fromState -> toState
    self.map_[event.name] = self.map_[event.name] or {}
    for fromState, _ in pairs(fromStates) do
        self.map_[event.name][fromState] = event.to or fromState
    end
end

local function doCallback_(callback, event)
    if callback then return callback(event) end
end

function StateMachine:beforeAnyEvent_(event)
    return doCallback_(self.callbacks_["on_before_event"], event)
end

function StateMachine:afterAnyEvent_(event)
    return doCallback_(self.callbacks_["on_after_event"] or self.callbacks_["on_event"], event)
end

function StateMachine:leaveAnyState_(event)
    return doCallback_(self.callbacks_["on_leave_state"], event)
end

function StateMachine:enterAnyState_(event)
    return doCallback_(self.callbacks_["on_enter_state"] or self.callbacks_["on_state"], event)
end

function StateMachine:beforeThisEvent_(event)
    return doCallback_(self.callbacks_["on_before_" .. event.name], event)
end

function StateMachine:afterThisEvent_(event)
    return doCallback_(self.callbacks_["on_after_" .. event.name] or self.callbacks_["on_" .. event.name], event)
end

function StateMachine:beforeEvent_(event)
    if self:beforeThisEvent_(event) == false or self:beforeAnyEvent_(event) == false then
        return false
    end
end

function StateMachine:leaveThisState_(event)
    return doCallback_(self.callbacks_["on_leave_" .. event.from], event)
end

function StateMachine:enterThisState_(event)
    return doCallback_(self.callbacks_["on_enter_" .. event.to] or self.callbacks_["on_" .. event.to], event)
end

function StateMachine:afterEvent_(event)
    self:afterThisEvent_(event)
    self:afterAnyEvent_(event)
end

function StateMachine:leaveState_(event)
    local specific = self:leaveThisState_(event)
    local general = self:leaveAnyState_(event)
    if specific == false or general == false then
        return false
    end
end

function StateMachine:enterState_(event)
    self:enterThisState_(event)
    self:enterAnyState_(event)
end

function StateMachine:changeState_(event)
    return doCallback_(self.callbacks_["on_change_state"], event)
end

function StateMachine:onError_(event, error, message)
    printf("ERROR: error %s, event %s, from %s to %s", tostring(error), event.name, event.from, event.to)
    echoError(message)
end

return StateMachine
