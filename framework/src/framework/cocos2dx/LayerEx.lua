
cc.LayerEx = class("cc.LayerEx", cc.NodeEx)

local LayerEx = cc.LayerEx
LayerEx.__index = LayerEx
LayerEx.isLayer = true

function LayerEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LayerEx)
    return target
end

