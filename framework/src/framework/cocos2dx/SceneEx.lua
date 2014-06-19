
cc.SceneEx = class("cc.SceneEx", cc.NodeEx)

local SceneEx = cc.SceneEx
SceneEx.__index = SceneEx
SceneEx.isScene = true

function SceneEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SceneEx)
    
    target:setNodeEventEnabled(true)
    
    return target
end
