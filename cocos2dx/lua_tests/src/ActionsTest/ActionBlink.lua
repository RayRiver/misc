local TestClass = class("ActionBlink", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("Blink")

    self:createSprites(2)

    self.spriteTamara:runAction(cc.Blink:create(2,10))
    self.spriteKathia:runAction(cc.Blink:create(2,2))
end

return TestClass