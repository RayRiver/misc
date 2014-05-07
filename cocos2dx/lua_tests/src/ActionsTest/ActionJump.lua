local TestClass = class("ActionJump", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("JumpTo / JumpBy")

    self:createSprites(3)

    local actionTo = cc.JumpTo:create(2,cc.p(300,300),50,4)
    local actionBy = cc.JumpBy:create(2,cc.p(300,0),50,4)
    local actionBy2 = cc.JumpBy:create(2,cc.p(0,0),80,4)
    
    self.spriteTamara:runAction(actionTo)
    self.spriteGrossini:runAction(cc.Sequence:create(actionBy,actionBy:reverse()))
    self.spriteKathia:runAction(cc.RepeatForever:create(actionBy2))
end

return TestClass