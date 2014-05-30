
local SCENE_NAME = "TestUICheckBox"

local SceneClass = class(SCENE_NAME, import(".TestUIBase"))

function SceneClass:ctor()
    SceneClass.super.ctor(self)
        
    -- label
    local label = ccui.Text:create("unselected", "Arial", 48)
    label:setPosition(display.cx, display.cy/2)
    self:addChild(label)
    self.label = label
    
    -- checkbox
    local checkbox = ccui.CheckBox:create(
        "textures/ui/CheckBoxButton2Off.png", 
        "textures/ui/CheckBoxButton2Off.png", 
        "textures/ui/CheckBoxButton2On.png", 
        "", ""
    )
    checkbox:setPosition(display.cx, display.cy)
    checkbox:setSelectedState(false)
    self:addChild(checkbox)

    checkbox:addEventListenerCheckBox(function(sender, type) 
        if type == ccui.CheckBoxEventType.selected then
            self.label:setString("selected")
        elseif type == ccui.CheckBoxEventType.unselected then
            self.label:setString("unselected")
        end
    end)
end

return SceneClass
