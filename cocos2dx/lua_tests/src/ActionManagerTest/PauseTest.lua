local TestClass = class("PauseTest", require("src.TestBase"))

function TestClass:onEnter()
    self:setDesc("After 2 seconds grossini should move")
    
    self.sprite = cc.Sprite:create("res/Images/grossini.png")
    self.sprite:setPosition(display.cx, display.cy)
    self:addChild(self.sprite)
    
    local action = cc.MoveBy:create(1, cc.p(150, 0))
    cc.Director:getInstance():getActionManager():addAction(action, self.sprite, true)
    
    scheduler.performWithDelayGlobal(function() 
        cc.Director:getInstance():getActionManager():resumeTarget(self.sprite)
    end, 2)
    
end

return TestClass
