
local lib = require("lib.init")
local BT = require("lib.bt")

local ObjectClass = BT.ConditionClass("CondFoundTarget")

function ObjectClass:onEvaluate(owner, input)
    local target = input.player
    if not target then
        return false
    end

    if target:getData("dead") then
        return false
    end

    local eyeshot = owner:getConfig().eyeshot
    if not eyeshot then
        return false
    end

    local x, y = owner:getPosition()
    local tx, ty = target:getPosition()
    local dx, dy = tx - x, ty - y
    if dx * dx + dy * dy <= eyeshot * eyeshot then
        return true
    else
        return false
    end
end

return ObjectClass
