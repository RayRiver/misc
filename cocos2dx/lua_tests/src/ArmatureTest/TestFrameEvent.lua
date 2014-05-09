local TestClass = class("TestFrameEvent", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    -- 动画播放完成回调
    local function onFrameEvent(bone, eventname, originFrameIndex, currentFrameIndex)
        -- json中配置的hit事件会在这里触发
        log("event: " .. tostring(eventname))
        log("origin: " .. tostring(originFrameIndex))
        log("current: " .. tostring(currentFrameIndex))
    end
    
    -- 异步加载完成回调
    local function onAsyncLoaded()
        local armature = ccs.Armature:create("HeroAnimation");
        armature:setAnchorPoint(0.5, 0.5)
        armature:setPosition(display.cx-50, display.cy)
        self:addChild(armature)
        
        armature:getAnimation():play("attack")
        armature:getAnimation():setFrameEventCallFunc(onFrameEvent)
        
    end

    -- 异步加载资源
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync("res/armature/HeroAnimation.ExportJson", onAsyncLoaded)
    
end

return TestClass
