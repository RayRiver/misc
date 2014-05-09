local TestClass = class("BaseUI", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("")

    local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/BaseUI_1/BaseUI_1.json")
    self:addChild(widget, -10)
    
    local labelAtlas1 = widget:getChildByName("LabelAtlas1")
    local loadingBar1 = widget:getChildByName("LoadingBar1")
    local slider1 = widget:getChildByName("Slider1")
    local label1 = widget:getChildByName("Label1")
    local button1 = widget:getChildByName("Button1")

    local function onSliderPercentChanged(percent)
        slider1:setPercent(percent)
        labelAtlas1:setStringValue(tostring(percent))
        loadingBar1:setPercent(percent)
    end

    button1:addTouchEventListener(function(sender, type)
        if type == ccui.TouchEventType.began then
            label1:setText("button down")
        elseif type == ccui.TouchEventType.ended then
            label1:setText("button up")
            onSliderPercentChanged(88)
        end
    end)

    slider1:addEventListenerSlider(function(sender, type)
        if type == ccui.SliderEventType.percentChanged then
            local percent = slider1:getPercent()
            onSliderPercentChanged(percent)
        end
    end)
    onSliderPercentChanged(50)
    
end

return TestClass