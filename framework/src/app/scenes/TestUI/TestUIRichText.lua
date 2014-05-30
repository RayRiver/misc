
local SCENE_NAME = "TestUIRichText"

local SceneClass = class(SCENE_NAME, import(".TestUIBase"))

function SceneClass:ctor()
    SceneClass.super.ctor(self)
    
    
    -- rich text
    local richtext = ccui.RichText:create()
    richtext:setPosition(display.cx, display.cy)
    richtext:ignoreContentAdaptWithSize(true)

    local re1 = ccui.RichElementText:create(1, cc.c3b(255, 255, 255), 255, "This color is white. ", "Arial", 30)
    local re2 = ccui.RichElementText:create(2, cc.c3b(255, 255,   0), 255, "And this is yellow. ", "Arial", 60)
    local re3 = ccui.RichElementText:create(4, cc.c3b(0,   0,   255), 255, "This one is blue. ", "Arial", 10)
    local reimg = ccui.RichElementImage:create(6, cc.c3b(255, 255, 255), 255, "textures/ui/sliderballnormal.png")

    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("textures/ui/100/100.ExportJson")
    local arr = ccs.Armature:create("100")
    arr:getAnimation():play("Animation1")
    local recustom = ccui.RichElementCustomNode:create(1, cc.c3b(255, 255, 255), 255, arr)
    
    local re4 = ccui.RichElementText:create(7, cc.c3b(255, 127,   0), 255, "Have fun!! ", "Arial", 60)

    richtext:pushBackElement(re1)
    richtext:pushBackElement(re2)
    richtext:pushBackElement(re3)
    richtext:insertElement(reimg,2)
    richtext:insertElement(recustom,2)
    richtext:pushBackElement(re4)

    self:addChild(richtext)
    
    -- button change to 400x200
    local button = ccui.Button:create(
        "textures/ui/Button01.png", 
        "textures/ui/Button01Pressed.png", 
        "textures/ui/Button01Disabled.png"
    )
    button:setPosition(display.cx/2, display.cy/2*3)
    button:setScale9Enabled(true)
    button:setSize(cc.size(200,100))
    button:setTitleFontName("Arial")
    button:setTitleFontSize(32)
    button:setTitleText("")
    self:addChild(button)
    
    button:addTouchEventListener(function(sender, type) 
        if type == ccui.TouchEventType.ended then
            richtext:ignoreContentAdaptWithSize(true)
            richtext:ignoreContentAdaptWithSize(false)
            richtext:setSize(cc.size(400, 200))
        end
    end)
    
    -- button change to 200x400
    local button = ccui.Button:create(
        "textures/ui/Button01.png", 
        "textures/ui/Button01Pressed.png", 
        "textures/ui/Button01Disabled.png"
    )
    button:setPosition(display.cx/2*3, display.cy/2*3)
    button:setScale9Enabled(true)
    button:setSize(cc.size(100,200))
    button:setTitleFontName("Arial")
    button:setTitleFontSize(32)
    button:setTitleText("")
    self:addChild(button)
    
    button:addTouchEventListener(function(sender, type) 
        if type == ccui.TouchEventType.ended then
            richtext:ignoreContentAdaptWithSize(true)
            richtext:ignoreContentAdaptWithSize(false)
            richtext:setSize(cc.size(200, 400))
        end
    end)

end

return SceneClass
