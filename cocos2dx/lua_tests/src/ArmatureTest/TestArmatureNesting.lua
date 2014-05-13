local TestClass = class("TestArmatureNesting", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")
    
    local m_weaponIndex = 0
    
    -- 异步加载完成回调
    local function onAsyncLoaded()
        local armature = ccs.Armature:create("cyborg");
        armature:setAnchorPoint(0.5, 0.5)
        armature:setPosition(display.cx, display.cy)
        self:addChild(armature)

        armature:getAnimation():playWithIndex(1)
        armature:getAnimation():setSpeedScale(0.4)
        
        -- 注册点击切换武器事件
        local listener = cc.EventListenerTouchAllAtOnce:create()
        listener:registerScriptHandler(function(touches, event) 
            m_weaponIndex = m_weaponIndex + 1
            m_weaponIndex = m_weaponIndex % 4
            if armature then
                armature:getBone("armInside"):getChildArmature():getAnimation():playWithIndex(m_weaponIndex)
                armature:getBone("armOutside"):getChildArmature():getAnimation():playWithIndex(m_weaponIndex)
            end
        end, cc.Handler.EVENT_TOUCHES_ENDED)
        self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)

    end

    -- 异步加载资源
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/cyborg.png",
        "res/armature/cyborg.plist",
        "res/armature/cyborg.xml",
        onAsyncLoaded)
end

return TestClass
