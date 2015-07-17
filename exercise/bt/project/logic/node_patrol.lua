
local bt = require("bt.init")

local ObjectClass = bt.ActionNodeClass("NodePatrol")

function ObjectClass:onEnter(owner, input)
    local x, y = owner:getPosition()

    local rx = math.random(-50, 50)
    local ry = math.random(-50, 50)
    self.m_patrol_x, self.m_patrol_y = x + rx, y + ry

    bt.debugFormat("patrol enter: x, y = %d, %d", math.floor(rx), math.floor(ry))
end

function ObjectClass:onExit(owner, input, state)
    self.m_patrol_x, self.m_patrol_y = nil, nil

    bt.debugFormat("patrol exit")
end

function ObjectClass:onExecute(owner, input, output)
    local x, y = owner:getPosition()
    local dx = self.m_patrol_x - x
    local dy = self.m_patrol_y - y
    --local dist2 = dx * dx + dy * dy

    if math.abs(dx) < 10 and math.abs(dy) < 10 then
        local n = 50
        dx = math.random(-n, n)
        dy = math.random(-n, n)
    end

    owner:setVelocity(dx, dy)

    return bt.RunningStatus.Executing
end

return ObjectClass
