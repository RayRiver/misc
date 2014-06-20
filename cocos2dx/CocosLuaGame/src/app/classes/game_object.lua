
local ACTION_STATE_IDLE = 1

local GameObject = class("GameObject", function() 
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/animation.ExportJson")
    local obj = display.newArmature("animation")
    return obj
end)

function GameObject:ctor()
    self:schedule(function() 
        self:onFrame()
    end, 1)
    

    --self:init("viking")
    
    self:doIdle()
end

function GameObject:onFrame()
    printInfo("fame")
end

function GameObject:setSpeedX(speed_x)
    self.speed_x = speed_x
end

function GameObject:setSpeedY(speed_y)
    self.speed_y = speed_y
end

function GameObject:getSpeedX()
    return self.speed_x
end

function GameObject:getSpeedY()
    return self.speed_y
end

function GameObject:doIdle()
    self.speed_x = 0
    self.speed_y = 0
    self:getAnimation():play("run")
end

function GameObject:doMove()
    
end

return GameObject
