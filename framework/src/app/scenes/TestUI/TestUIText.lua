
local SCENE_NAME = "TestUIText"

local SceneClass = class(SCENE_NAME, import(".TestUIBase"))

function SceneClass:ctor()
    SceneClass.super.ctor(self)
    
    local default_text = "Loading"

    -- label
    local label = ccui.Text:create(default_text, "fonts/Marker Felt.ttf", 30)
    label:setPosition(display.cx, display.cy)
    label:setColor(cc.c3b(200,35,35))
    label:setAnchorPoint(0, 1)
    self:addChild(label)

    local count = 0
    ccui.WidgetEx.extend(label)
    label:schedule(function() 
        local text = default_text
        for i = 1, count do
            text = text .. "."
        end
        label:setString(text)

        count = count + 1
        if count > 3 then
            count = 0
        end
    end, 0.2)
end

return SceneClass
