local TestClass = class("ActionRotateBy3D", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("RotateBy in 3D(tolua NO CONVERSION TO NATIVE FOR Vertex3F)")

    self:createSprites(3)

    local vertex = cc.Vertex3F(360,0,0)
    local actionBy1 = cc.RotateBy:create(4,360,0)
    
    self.spriteTamara:runAction(cc.Sequence:create(actionBy1,actionBy1:reverse()))
    
    self.spriteGrossini:runAction(cc.MoveTo:create(2,cc.p(0,0)))
end

return TestClass