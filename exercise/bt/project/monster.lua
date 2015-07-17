
local lib = require("lib.init")
local BT = require("lib.bt")

local ObjectClass = lib.Class("Monster")

function ObjectClass:initialize(config, blackboard)
    if config.ai then
        self.m_ai = BT.Reader:loadFile(config.ai)
    end

    self.m_blackboard = blackboard

    self.m_x, self.m_y = 300, 200
    self.m_vx, self.m_vy = 0, 0
end

local static_time = 0
local BT_INTERVAL = 0.5
function ObjectClass:update(dt)
    self.m_x = self.m_x + self.m_vx * dt
    self.m_y = self.m_y + self.m_vy * dt

    if self.m_ai then
        static_time = static_time + dt
        if static_time > BT_INTERVAL then
            static_time = static_time - BT_INTERVAL
            self:updateBehavior()
        end
    end
end

function ObjectClass:draw()
    love.graphics.setColor(255, 255, 255)
    love.graphics.circle("fill", self.m_x, self.m_y, 5, 100)
end

function ObjectClass:updateBehavior()
    local ai = self.m_ai
    if ai then
        local input = self.m_blackboard
        local output = self.m_blackboard
        if ai:evaluate(input) then
            ai:update(self, input, output)
        end
    end
end

function ObjectClass:getPosition()
    return self.m_x, self.m_y
end

function ObjectClass:getVelocity()
    return self.m_vx, self.m_vy
end

function ObjectClass:setVelocity(vx, vy)
    self.m_vx, self.m_vy = vx, vy
end

return ObjectClass
