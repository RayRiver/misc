local TestClass = class("ActionRotationalSkew", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("RotationalSkewTo / RotationalSkewBy")

    self:createSprites(3)

    local actionTo = cc.RotateTo:create(2,180,180)
    local actionToBack = cc.RotateTo:create(2,0,0)
    local actionBy = cc.RotateBy:create(2,0,360)
    local actionByBack = actionBy:reverse()
    local actionBy2 = cc.RotateBy:create(2,360,0)
    local actionBy2Back = actionBy2:reverse()
   
    self.spriteTamara:runAction(cc.Sequence:create(actionBy,actionByBack))
    self.spriteGrossini:runAction(cc.Sequence:create(actionTo,actionToBack))
    self.spriteKathia:runAction(cc.Sequence:create(actionBy2,actionBy2Back))
end

return TestClass