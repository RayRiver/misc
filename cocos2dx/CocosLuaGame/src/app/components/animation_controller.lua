
local COMPONENT_NAME = "AnimationController"

local ComponentClass = class(COMPONENT_NAME, function() 
    local component = cc.Component:create()
    component:setName(COMPONENT_NAME)
    return component
end)

ComponentClass.PlayMode = 
{
    Default = -1,
    Once = 0,
    Loop = 1,
}

function ComponentClass:ctor()
    self.armature = nil
    self.armatureName = ""
end

function ComponentClass:load(armatureName, animationEventCallback)
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
        
        if animationEventCallback then
            local function animationEvent(armature, movementType, movementID)
                animationEventCallback(movementType, movementID)
            end
            self.armature:getAnimation():setMovementEventCallFunc(animationEvent)
        end
    end
    return self
end

function ComponentClass:play(movementName, playMode)
    if self.armature then
        if self.armature:getAnimation():getAnimationData():getMovement(movementName) then
            playMode = playMode or ComponentClass.PlayMode.Default
            self.armature:getAnimation():play(movementName, -1, playMode)
        end
    end
    return self
end

function ComponentClass:setMovementEventCallFunc(callback)
    if callback then
        self.armature:getAnimation():setMovementEventCallFunc(callback)
    end
end

function ComponentClass:pause()
    if self.armature then
        self.armature:getAnimation():pause()
    end
end

function ComponentClass:resume()
    if self.armature then
        self.armature:getAnimation():resume()
    end
end

function ComponentClass:stop()
    if self.armature then
        self.armature:getAnimation():stop()
    end
end

return ComponentClass
