local TestClass = class("BaseUI", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/BaseUI_1/BaseUI_1.json")
    self:addChild(widget, -10)
    
    local label1 = widget:getChildByName("Label1")
    local button1 = widget:getChildByName("Button1")
    button1:addTouchEventListener(function(sender, type)
        if type == ccui.TouchEventType.began then
            label1:setText("button down")
        elseif type == ccui.TouchEventType.ended then
            label1:setText("button up")
        end
    end)
    
    local labelAtlas1 = widget:getChildByName("LabelAtlas1")
    local slider1 = widget:getChildByName("Slider1")
    slider1:addEventListenerSlider(function(sender, type)
        if type == ccui.SliderEventType.percentChanged then
            local percent = slider1:getPercent()
            labelAtlas1:setStringValue(tostring(percent))
        end
    end)
    slider1:setPercent(50)
    labelAtlas1:setStringValue(tostring(slider1:getPercent()))
end

return TestClass