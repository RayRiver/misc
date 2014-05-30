
ccui.WidgetEx = class("ccui.WidgetEx", cc.NodeEx)

local WidgetEx = ccui.WidgetEx
WidgetEx.__index = WidgetEx

function WidgetEx.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, WidgetEx)
    return target
end
