local TestClass = class("ActionSkew", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("SkewTo / SkewBy")

    self:createSprites(3)

    local actionTo = cc.SkewTo:create(2,45,-45)
    local actionToBack = cc.SkewTo:create(2,0,0)
    local actionBy = cc.SkewBy:create(2,0,-90)
    local actionBy2 = cc.SkewBy:create(2,45,45)
   
    self.spriteTamara:runAction(cc.Sequence:create(actionTo,actionToBack))
    self.spriteGrossini:runAction(cc.Sequence:create(actionBy,actionBy:reverse()))
    self.spriteKathia:runAction(cc.Sequence:create(actionBy2,actionBy2:reverse()))
end

return TestClass