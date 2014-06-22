
local COMPONENT_NAME = "StateMachine"

local ComponentClass = class(COMPONENT_NAME, function() 
    local component = cc.Component:create()
    component:setName(COMPONENT_NAME)
    return component
end)

ComponentClass.WILDCARD = "*"
ComponentClass.STATE_READY = "_"

-- the event transitioned successfully from one state to another
ComponentClass.SUCCEEDED = 1
-- the event was successfull but no state transition was necessary
ComponentClass.NOTRANSITION = 2
-- the event was cancelled by the caller in a beforeEvent callback
ComponentClass.CANCELLED = 3
-- the event is asynchronous and the caller is in control of when the transition occurs
ComponentClass.PENDING = 4
-- the event was failure
ComponentClass.FAILURE = 5

-- caller tried to fire an event that was innapropriate in the current state
ComponentClass.INVALID_TRANSITION_ERROR = "INVALID_TRANSITION_ERROR"
-- caller tried to fire an event while an async transition was still pending
ComponentClass.PENDING_TRANSITION_ERROR = "PENDING_TRANSITION_ERROR"
-- caller provided callback function threw an exception
ComponentClass.INVALID_CALLBACK_ERROR = "INVALID_CALLBACK_ERROR"

function ComponentClass:ctor()
    
end

function ComponentClass:setupState(cfg)
    self.map_ = {}
    self.events_ = cfg.events or {}
    self.current_ = ComponentClass.STATE_READY
    self.callbacks_ = cfg.callbacks or {}
    self.inTransition_ = false
    
    for _, event in ipairs(self.events_) do
        self:addEvent_(event)
    end
end

function ComponentClass:isReady()
    return self.current_ ~= ComponentClass.STATE_READY
end

function ComponentClass:getState()
    return self.current_
end

function ComponentClass:isState(state)
    if type(state) == "table" then
        for _, s in ipairs(state) do
            if s == self.current_ then return true end
        end
        return false
    else
        return self.current_ == state
    end
end

function ComponentClass:canDoEvent(name)
    return not self.inTransition_ and
        (self.map_[name][self.current_] ~= nil or self.map_[name][ComponentClass.WILDCARD] ~= nil)
end

function ComponentClass:doEvent(name, ...)
    assert(self.map_[name] ~= nil, string.format("StateMachine:doEvent() - invalid event %s", tostring(name)))
    
    local from = self.current_
    local map = self.map_[name]
    local to = (map[from] or map[ComponentClass.WILDCARD]) or from
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
            ComponentClass.PENDING_TRANSITION_ERROR,
            "event " .. name .. " inappropriate because previous transition did not complete")
        return ComponentClass.FAILURE
    end
    
    if not self:canDoEvent(name) then
        self:onError_(event,
            ComponentClass.INVALID_TRANSITION_ERROR,
            "event " .. name .. " inappropriate in current state " .. self.current_)
        return ComponentClass.FAILURE
    end
    
    if self:beforeEvent_(event) == false then
        return ComponentClass.CANCELLED
    end
    
    if from == to then
        self:afterEvent_(event)
        return ComponentClass.NOTRANSITION
    end
    
    event.transition = function()
        self.inTransition_  = false
        self.current_ = to
        self:enterState_(event)
        self:changeState_(event)
        self:afterEvent_(event)
        return ComponentClass.SUCCEEDED
    end
    
    self.inTransition_ = true
    local leave = self:leaveState_(event) 
    if leave == false then
        event.transition = nil
        event.cancel = nil
        self.inTransition_ = false
        return ComponentClass.CANCELLED
    else
        if event.transition then
            return event.transition()
        else
            self.inTransition_ = false
        end
    end
end

function ComponentClass:addEvent_(event)
    -- parse from states to table
    local fromStates = {}
    if type(event.from) == "table" then
        for _, fromState in ipairs(event.from) do
            fromStates[fromState] = true
        end
    elseif event.from then
        fromStates[event.from] = true
    else
        fromStates[ComponentClass.WILDCARD] = true
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

function ComponentClass:beforeAnyEvent_(event)
    return doCallback_(self.callbacks_["on_before_event"], event)
end

function ComponentClass:afterAnyEvent_(event)
    return doCallback_(self.callbacks_["on_after_event"] or self.callbacks_["on_event"], event)
end

function ComponentClass:leaveAnyState_(event)
    return doCallback_(self.callbacks_["on_leave_state"], event)
end

function ComponentClass:enterAnyState_(event)
    return doCallback_(self.callbacks_["on_enter_state"] or self.callbacks_["on_state"], event)
end

function ComponentClass:beforeThisEvent_(event)
    return doCallback_(self.callbacks_["on_before_" .. event.name], event)
end

function ComponentClass:afterThisEvent_(event)
    return doCallback_(self.callbacks_["on_after_" .. event.name] or self.callbacks_["on_" .. event.name], event)
end

function ComponentClass:beforeEvent_(event)
    if self:beforeThisEvent_(event) == false or self:beforeAnyEvent_(event) == false then
        return false
    end
end

function ComponentClass:leaveThisState_(event)
    return doCallback_(self.callbacks_["on_leave_" .. event.from], event)
end

function ComponentClass:enterThisState_(event)
    return doCallback_(self.callbacks_["on_enter_" .. event.to] or self.callbacks_["on_" .. event.to], event)
end

function ComponentClass:afterEvent_(event)
    self:afterThisEvent_(event)
    self:afterAnyEvent_(event)
end

function ComponentClass:leaveState_(event)
    local specific = self:leaveThisState_(event)
    local general = self:leaveAnyState_(event)
    if specific == false or general == false then
        return false
    end
end

function ComponentClass:enterState_(event)
    self:enterThisState_(event)
    self:enterAnyState_(event)
end

function ComponentClass:changeState_(event)
    return doCallback_(self.callbacks_["on_change_state"], event)
end

function ComponentClass:onError_(event, error, message)
    printf("ERROR: error %s, event %s, from %s to %s", tostring(error), event.name, event.from, event.to)
    printError(message)
end

return ComponentClass
