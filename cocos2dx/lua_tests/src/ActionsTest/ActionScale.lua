local TestClass = class("ActionScale", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("ScaleTo / ScaleBy")

    self:createSprites(3)

    local actionTo = cc.ScaleTo:create(2,0.5)
    local actionBy = cc.ScaleBy:create(2,1,10)
    local actionBy2 = cc.ScaleBy:create(2,5,1)
   
    self.spriteGrossini:runAction(actionTo)
    self.spriteTamara:runAction(cc.Sequence:create(actionBy,actionBy:reverse()))
    self.spriteKathia:runAction(cc.Sequence:create(actionBy2,actionBy2:reverse()))
end

return TestClass