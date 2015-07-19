
local lib = require("lib.init")
local BT = require("lib.bt")

local ObjectClass = BT.ActionNodeClass("NodeChevy")

function ObjectClass:onEnter(owner, input)

end

function ObjectClass:onExit(owner, input, state)

end

function ObjectClass:onExecute(owner, input, output)
    local target = input.player

    local x, y = owner:getPosition()
    local tx, ty = target:getPosition()
    local dx, dy = tx - x, ty - y
    local n = math.sqrt(dx * dx + dy * dy)

    local speed = 100
    local vx, vy = dx / n * speed, dy / n * speed
    owner:setVelocity(vx, vy)

    return BT.RunningStatus.Executing
end

return ObjectClass
