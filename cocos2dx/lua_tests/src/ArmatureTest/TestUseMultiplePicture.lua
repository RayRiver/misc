local TestClass = class("TestUseMultiplePicture", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")
    
    local displayIndex = 0
    
    -- 异步加载完成回调
    local function onAsyncLoadedAllFinished()
        -- 创建骨骼动画
        local armature = ccs.Armature:create("Knight_f/Knight");
        armature:setAnchorPoint(0.5, 0.5)
        armature:setPosition(display.cx, display.cy)
        self:addChild(armature)
        armature:getAnimation():playWithIndex(0)
        
        -- 增加武器
        local weapons = 
        {
            "weapon_f-sword.png", 
            "weapon_f-sword2.png", 
            "weapon_f-sword3.png", 
            "weapon_f-sword4.png", 
            "weapon_f-sword5.png", 
            "weapon_f-knife.png", 
            "weapon_f-hammer.png"
        }
        for i, name in ipairs(weapons) do
            local skin = ccs.Skin:createWithSpriteFrameName(name)
            armature:getBone("weapon"):addDisplay(skin, i-1)
        end
        
        local l = cc.Label:createWithTTF("===|============>", "fonts/arial.ttf", 18);
        l:setAnchorPoint(cc.p(0.15, 0.15))
        armature:getBone("weapon"):addDisplay(l, #weapons)
        
        -- 注册点击切换武器事件
        local listener = cc.EventListenerTouchAllAtOnce:create()
        listener:registerScriptHandler(function(touches, event) 
            displayIndex = displayIndex + 1
            displayIndex = displayIndex % 8
            log("display index = " .. tostring(displayIndex))
            armature:getBone("weapon"):changeDisplayWithIndex(displayIndex, true)
        end, cc.Handler.EVENT_TOUCHES_ENDED)
        self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
    end

    local function onAsyncLoaded()
        -- 异步加载武器资源
        ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
            "res/armature/weapon.png",
            "res/armature/weapon.plist",
            "res/armature/weapon.xml",
            onAsyncLoadedAllFinished)
    end
    
    -- 设置背景
    local bg = cc.Sprite:create("res/armature/bg.jpg")
    bg:setPosition(display.cx, display.cy)
    local scaleX = display.width / bg:getContentSize().width
    local scaleY = display.height / bg:getContentSize().height
    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)
    self:addChild(bg, -10000)

    -- 异步加载资源
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/knight.png",
        "res/armature/knight.plist",
        "res/armature/knight.xml",
        onAsyncLoaded)

    
end

return TestClass
