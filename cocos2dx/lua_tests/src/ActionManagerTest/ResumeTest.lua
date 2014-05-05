local TestClass = class("ResumeTest", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("Grossini only rotate/scale in 2 seconds")

    self.sprite = cc.Sprite:create("res/Images/grossini.png")
    self.sprite:setPosition(display.cx, display.cy)
    self:addChild(self.sprite)

    self.sprite:runAction(cc.ScaleBy:create(2, 2))
    self.sprite:runAction(cc.RotateBy:create(2, 360))
    --self.sprite:pause()
   
    scheduler.performWithDelayGlobal(function() 
        cc.Director:getInstance():getActionManager():pauseTarget(self.sprite)
        --self.sprite:getActionManager():pauseTarget(self.sprite)
    end, 1)
end

return TestClass
