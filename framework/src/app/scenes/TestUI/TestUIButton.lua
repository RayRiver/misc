
local SCENE_NAME = "TestUIButton"

local SceneClass = class(SCENE_NAME, import(".TestUIBase"))

function SceneClass:ctor()
    SceneClass.super.ctor(self)

    -- button
    local button = ccui.Button:create(
        "textures/ui/Button01.png", 
        "textures/ui/Button01Pressed.png", 
        "textures/ui/Button01Disabled.png"
    )
    button:setPosition(display.cx, display.cy)
    button:setScale9Enabled(true)
    button:setSize(cc.size(300,60))
    button:setTitleFontName("Arial")
    button:setTitleFontSize(32)
    button:setTitleText("click me")
    self:addChild(button)
    
    button:addTouchEventListener(function(sender, type) 
        if type == ccui.TouchEventType.began then
            button:setTitleText("down")
        elseif type == ccui.TouchEventType.ended then
            button:setTouchEnabled(false)
            button:setBright(false)
            
            local seconds = 3
            
            local function cb()
                button:setTitleText("after " .. seconds .. " seconds")
                if seconds == 0 then
                    button:stopAllActions()
                    button:setTouchEnabled(true)
                    button:setBright(true)
                    button:setTitleText("click me")
                    return
                end
                seconds = seconds - 1
            end

            local action = cc.Repeat:create(cc.Sequence:create(
                cc.CallFunc:create(cb),
                cc.DelayTime:create(1)
            ), seconds+1)
            button:runAction(action)
        elseif type == ccui.TouchEventType.canceled then
            button:setTitleText("click me")
        end
    end)

end

return SceneClass
