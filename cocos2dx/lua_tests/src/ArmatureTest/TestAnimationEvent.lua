local TestClass = class("TestAnimationEvent", require("src.ArmatureTest.ArmatureTestBase"))

function TestClass:onEnter()
    self:setDesc("")
    
    local function callback1(armature)
        armature:runAction(cc.ScaleBy:create(0.3,-1,1))
        armature:getAnimation():play("FireMax", 10)
    end
    
    local function callback2(armature)
        armature:runAction(cc.ScaleBy:create(0.3,-1,1))
        armature:getAnimation():play("Fire", 10)
    end
    
    local function animationEvent(armature, movementType, movementID)
        log("animationEvent")
        if movementType == ccs.MovementEventType.loopComplete then
            log("loopComplete, movementID=" .. tostring(movementID))
            if movementID == "Fire" then
                armature:stopAllActions()
                armature:getAnimation():play("Walk")
                local action = cc.MoveTo:create(2, cc.p(display.right-50, display.cy))
                armature:runAction(cc.Sequence:create(action, cc.CallFunc:create(callback1,{armature})))
            elseif movementID == "FireMax" then
                armature:stopAllActions()
                armature:getAnimation():play("Walk")
                local action = cc.MoveTo:create(2, cc.p(display.left+50, display.cy))
                armature:runAction(cc.Sequence:create(action, cc.CallFunc:create(callback2,{armature})))
            end
        end
    end
    
    local function onAsyncLoaded()
        local armature = ccs.Armature:create("Cowboy");
        armature:setScaleX(-0.24)
        armature:setScaleY(0.24)
        armature:setAnchorPoint(0.5, 0.5)
        armature:setPosition(display.cx, display.cy)
        self:addChild(armature)
        
        armature:getAnimation():setMovementEventCallFunc(animationEvent)
        armature:getAnimation():play("Fire")
    end

    self:asyncLoad(onAsyncLoaded) 

end

return TestClass
