local TestClass = class("ActionMove", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("MoveTo / MoveBy")

    self:createSprites(3)

    local actionMoveTo = cc.MoveTo:create(2, cc.p(display.width-40, display.height-40))
    local actionMoveBy = cc.MoveBy:create(2, cc.p(80, 80))
    local actionMoveByBack = actionMoveBy:reverse()

    self.spriteTamara:runAction(actionMoveTo)
    self.spriteGrossini:runAction(cc.Sequence:create(actionMoveBy,actionMoveByBack))
    self.spriteKathia:runAction(cc.MoveTo:create(1,cc.p(40,40)))
end

return TestClass
