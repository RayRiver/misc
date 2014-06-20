
local COMPONENT_NAME = "AnimationController"

local AnimationController = class(COMPONENT_NAME, function() 
    local component = cc.Component:create()
    component:setName(COMPONENT_NAME)
    return component
end)

AnimationController.PlayMode = 
{
    Default = -1,
    Once = 0,
    Loop = 1,
}

function AnimationController:ctor()
    self.armature = nil
    self.armatureName = ""
end

function AnimationController:load(armatureName)
    local owner = self:getOwner()
    if owner then
        if armatureName == self.armatureName then
            return self
        end
    
        local armature = ccs.Armature:create(armatureName)
        if not armature then
            printError("animation_controller load error: %s", armatureName)
            return self
        end
        
        if self.armature then
            owner:removeChild(self.armature, true)
            self.armature = nil
        end

        owner:addChild(armature)
        self.armature = armature
        self.armatureName = armatureName
    end
    return self
end

function AnimationController:play(movementName, playMode)
    if self.armature then
        if self.armature:getAnimation():getAnimationData():getMovement(movementName) then
            playMode = playMode or AnimationController.PlayMode.Default
            self.armature:getAnimation():play(movementName, -1, playMode)
        end
    end
    return self
end

function AnimationController:pause()
    if self.armature then
        self.armature:getAnimation():pause()
    end
end

function AnimationController:resume()
    if self.armature then
        self.armature:getAnimation():resume()
    end
end

function AnimationController:stop()
    if self.armature then
        self.armature:getAnimation():stop()
    end
end

return AnimationController
