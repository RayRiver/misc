local TestClass = class("ActionFollow", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("follow action")

    self:createSprites(1)

    self.spriteGrossini:setPosition(cc.p(-200, display.cy));
    
    local action = cc.MoveBy:create(2, cc.p(display.width*3, 0))
    local actionReverse = action:reverse()
    
    self.spriteGrossini:runAction(
        cc.RepeatForever:create(cc.Sequence:create(action,actionReverse))
    )
    
    self:runAction(
        cc.Follow:create(self.spriteGrossini,cc.rect(0,0,display.width*2,display.height))
    )
end

return TestClass