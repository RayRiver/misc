
cc.SpriteEx = class("cc.SpriteEx", cc.NodeEx)

local SpriteEx = cc.SpriteEx
SpriteEx.__index = SpriteEx
SpriteEx.isSprite = true

function SpriteEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SpriteEx)
    return target
end
