local TestClass = class("LogicTest", require("src.TestBase"))

function TestClass:onEnter()
    local sprite = cc.Sprite:create("res/Images/grossini.png")
    sprite:setPosition(display.cx, display.cy)
    self:addChild(sprite)
    
    local action = cc.Sequence:create(
        cc.MoveBy:create(1, cc.p(150, 0)),
        cc.CallFunc:create(function()
            sprite:stopAllActions()
            sprite:runAction(cc.ScaleTo:create(1, 2))
        end)
    )
    sprite:runAction(action)
end

return TestClass
