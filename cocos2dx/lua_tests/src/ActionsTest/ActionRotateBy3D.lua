local TestClass = class("ActionRotateBy3D", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("RotateBy in 3D(NOT SUPPORT in lua, NO CONVERSION TO NATIVE FOR Vertex3F)")

    self:createSprites(3)

    local actionBy1 = cc.RotateBy:create(4, cc.Vertex3F(360,0,0))
    local actionBy2 = cc.RotateBy:create(4, cc.Vertex3F(0,360,0))
    local actionBy3 = cc.RotateBy:create(4, cc.Vertex3F(0,0,360))
   
    self.spriteTamara:runAction(cc.Sequence:create(actionBy1,actionBy1:reverse()))
    self.spriteGrossini:runAction(cc.Sequence:create(actionBy2,actionBy2:reverse()))
    self.spriteKathia:runAction(cc.Sequence:create(actionBy3,actionBy3:reverse()))
end

return TestClass