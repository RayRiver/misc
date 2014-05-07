local TestClass = class("TimeScale", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("Braid like? (TODO: we cannot set nagtive speed now)")
    
    local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("res/ccs/BaseUI/Export/TimeScale/TimeScale.json")
    self:addChild(widget)
    
    local labelAtlas1 = widget:getChildByName("LabelAtlas1")
    local slider1 = widget:getChildByName("Slider1")
    slider1:addEventListenerSlider(function(sender, type)
        if type == ccui.SliderEventType.percentChanged then
            local percent = slider1:getPercent()
            labelAtlas1:setStringValue(tostring(percent))
            local value = (percent-50)/100*3
            cc.Director:getInstance():getScheduler():setTimeScale(value)
        end
    end)
    slider1:setPercent(50)
    labelAtlas1:setStringValue(tostring(slider1:getPercent()))

    -- init sprites
    self.spriteGrossini = cc.Sprite:create("res/Images/grossini.png")
    self:addChild(self.spriteGrossini)
    
    self.spriteTamara = cc.Sprite:create("res/Images/grossinis_sister1.png")
    self:addChild(self.spriteTamara)
    
    self.spriteKathia = cc.Sprite:create("res/Images/grossinis_sister2.png")
    self:addChild(self.spriteKathia)
    
    self.spriteGrossini:setPosition(display.cx, display.cy)
    self.spriteTamara:setPosition(display.left+display.width/4, display.bottom+display.height/2)
    self.spriteKathia:setPosition(display.left+display.width*3/4, display.bottom+display.height/2)

    -- create actions
    local jump1 = cc.JumpBy:create(10,cc.p(display.width*2/3, 0),50,10)
    local action = cc.RepeatForever:create(jump1)
    self.spriteTamara:runAction(cc.Speed:create(action,1))

    local emitter = cc.ParticleFireworks:create()
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage("res/Images/stars.png"))
    self:addChild(emitter)

end

return TestClass