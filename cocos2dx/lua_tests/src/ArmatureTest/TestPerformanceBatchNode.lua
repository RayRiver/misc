local TestClass = class("TestPerformanceBatchNode", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("ccs.BatchNode is invalid in current version of cocos2dx")
    
    local nArmatureCount = 0
    local ARMATURE_PERFORMANCE_TAG = 20000
    
    local function refreshTitle()
        self:setDesc("count = " .. tostring(nArmatureCount))
    end
    
    local function addArmatureToParent(node, armature)
        node:addChild(armature, 
            ARMATURE_PERFORMANCE_TAG + nArmatureCount, 
            ARMATURE_PERFORMANCE_TAG + nArmatureCount)
    end
    
    local function removeArmatureFromParent(node, tag)
        node:removeChildByTag(tag)
    end
    
    local function onIncreaseArmatures()
        if nArmatureCount >= 100 then return end
        for i = 1, 20 do
            nArmatureCount = nArmatureCount + 1
            local armature = ccs.Armature:create("Knight_f/Knight")
            armature:getAnimation():playWithIndex(0)
            armature:setPosition(50+nArmatureCount*2, 150)
            armature:setScale(0.6)
            addArmatureToParent(self.batchNode, armature)
        end
        refreshTitle()
    end
    
    local function onDecreaseArmatures()
        if nArmatureCount <= 0 then return end
        for i = 1, 20 do
            removeArmatureFromParent(self.batchNode, ARMATURE_PERFORMANCE_TAG + nArmatureCount)
            nArmatureCount = nArmatureCount - 1
        end
        refreshTitle()
    end

    local function onAsyncLoaded()
        cc.MenuItemFont:setFontSize(65)
    
        local decrease = cc.MenuItemFont:create(" - ")
        decrease:setColor({r=0, g=200, b=20})
        decrease:registerScriptTapHandler(onDecreaseArmatures)
        
        local increase = cc.MenuItemFont:create(" + ")
        increase:setColor({r=0, g=200, b=20})
        increase:registerScriptTapHandler(onIncreaseArmatures)
        
        local menu = cc.Menu:create(decrease, increase)
        menu:alignItemsHorizontally()
        menu:setPosition(display.cx, display.top-100)
        self:addChild(menu)

    end
    
    -- 设置背景
    local bg = cc.Sprite:create("res/armature/bg.jpg")
    bg:setPosition(display.cx, display.cy)
    local scaleX = display.width / bg:getContentSize().width
    local scaleY = display.height / bg:getContentSize().height
    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)
    self:addChild(bg, -10000)
    
    -- create batch node
    self.batchNode = ccs.BatchNode:create()
    self:addChild(self.batchNode)

    -- 异步加载资源
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/knight.png",
        "res/armature/knight.plist",
        "res/armature/knight.xml",
        onAsyncLoaded)
end

return TestClass