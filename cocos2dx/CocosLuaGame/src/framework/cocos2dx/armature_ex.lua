
ccs.ArmatureEx = class("ccui.ArmatureEx", cc.NodeEx)

local ArmatureEx = ccs.ArmatureEx
ArmatureEx.__index = ArmatureEx
ArmatureEx.isArmature = true

function ArmatureEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, ArmatureEx)
    return target
end
