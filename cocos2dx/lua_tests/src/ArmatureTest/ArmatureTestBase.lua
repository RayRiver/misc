local TestClass = class("ArmatureTestBase", require("src.TestBase"))

function TestClass:asyncLoad(finishCallback, everyCallback)
    local function onAsyncLoaded(percent)
        if type(everyCallback) == "function" then
            everyCallback(percent)
        end
        if type(finishCallback) == "function" and percent >= 1 then
            finishCallback()
        end
    end

    -- 异步加载资源
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/knight.png",
        "res/armature/knight.plist",
        "res/armature/knight.xml",
        onAsyncLoaded)
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/weapon.png",
        "res/armature/weapon.plist",
        "res/armature/weapon.xml",
        onAsyncLoaded)
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/robot.png",
        "res/armature/robot.plist",
        "res/armature/robot.xml",
        onAsyncLoaded)
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/cyborg.png",
        "res/armature/cyborg.plist",
        "res/armature/cyborg.xml",
        onAsyncLoaded)
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/Dragon.png",
        "res/armature/Dragon.plist",
        "res/armature/Dragon.xml",
        onAsyncLoaded)
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/Cowboy.ExportJson",
        onAsyncLoaded)
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/hero.ExportJson",
        onAsyncLoaded)        
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/horse.ExportJson",
        onAsyncLoaded)  
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/bear.ExportJson",
        onAsyncLoaded)    
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/HeroAnimation.ExportJson",
        onAsyncLoaded)      
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfoAsync(
        "res/armature/testEasing.ExportJson",
        onAsyncLoaded)  
end

function TestClass:createBG()
    local bg = cc.Sprite:create("res/armature/bg.jpg")
    bg:setPosition(display.cx, display.cy)
    local scaleX = display.width / bg:getContentSize().width
    local scaleY = display.height / bg:getContentSize().height
    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)
    self:addChild(bg, -10000)
end

return TestClass
