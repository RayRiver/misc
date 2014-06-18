
cc.DrawNodeEx = class("cc.DrawNodeEx", cc.NodeEx)

local DrawNodeEx = cc.DrawNodeEx
DrawNodeEx.__index = DrawNodeEx
DrawNodeEx.isDrawNode = true

function DrawNodeEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, DrawNodeEx)
    return target
end

