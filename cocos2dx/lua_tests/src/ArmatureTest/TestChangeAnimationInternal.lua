local TestClass = class("TestChangeAnimationInternal", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    -- 异步加载资源完成回调
    local function onAsyncLoaded()
        local armature = ccs.Armature:create("Cowboy")
        armature:getAnimation():playWithIndex(0)
        armature:setScale(0.2)
        armature:setPosition(display.cx, display.cy)
        self:addChild(armature)
        
        -- 注册点击事件
        local listener = cc.EventListenerTouchAllAtOnce:create()
        listener:registerScriptHandler(function(touches, event) 
            if cc.Director:getInstance():getAnimationInterval() == 1/15 then
                cc.Director:getInstance():setAnimationInterval(1/60)
            else
                cc.Director:getInstance():setAnimationInterval(1/15)
            end
        end, cc.Handler.EVENT_TOUCHES_ENDED)
        self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
    end
    
    -- 异步加载资源
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync("res/armature/Cowboy.ExportJson", onAsyncLoaded)
    
end

return TestClass