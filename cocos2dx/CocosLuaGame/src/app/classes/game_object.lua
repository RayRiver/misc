
local GameObject = class("GameObject", function() 
    local obj = display.newArmature()
    return obj
end)

function GameObject:ctor()
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/viking.ExportJson")
    self:init("viking")
    self:getAnimation():play("run_right")
end

return GameObject
