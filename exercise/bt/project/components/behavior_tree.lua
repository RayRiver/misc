
local lib = require("lib.init")
local Component = import(".component")
local BT = require("lib.bt")

local ObjectClass = lib.Class("BehaviorTree", Component)

function ObjectClass:onAttached()
    local config = self:getConfig()
    self.m_bt = BT.Reader:loadFile(config.bt)
    self.m_bt_interval = config.interval or 1
    self.m_bt_current_time = 0
end

function ObjectClass:onDetached()
    self.m_bt = nil
    self.m_bt_interval = nil
    self.m_bt_current_time = nil
end

function ObjectClass:onUpdate(dt)
    self.m_bt_current_time = self.m_bt_current_time + dt
    if self.m_bt_current_time > self.m_bt_interval then
        self.m_bt_current_time = self.m_bt_current_time - self.m_bt_interval
        self:updateBehavior()
    end
end

function ObjectClass:updateBehavior()
    local bt = self.m_bt
    if bt then
        local owner = self:getOwner()
        local blackboard = owner:getBlackboard()

        local input = blackboard
        local output = blackboard
        if bt:evaluate(input) then
            bt:update(owner, input, output)
        end
    end
end

return ObjectClass
