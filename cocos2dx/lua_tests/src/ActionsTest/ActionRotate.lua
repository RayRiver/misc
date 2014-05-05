local TestClass = class("ActionRotate", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("RotateTo / RotateBy")

    self:createSprites(3)

    local actionTo = cc.RotateTo:create(2,45)
    local actionTo0 = cc.RotateTo:create(2,0)
    self.spriteTamara:runAction(cc.Sequence:create(actionTo,actionTo0))
    
    local actionBy = cc.RotateBy:create(2,360)
    local actionByBack = actionBy:reverse()
    self.spriteGrossini:runAction(cc.Sequence:create(actionBy,actionByBack))
    
    local actionTo2 = cc.RotateTo:create(2,-45)
    self.spriteKathia:runAction(cc.Sequence:create(actionTo2,actionTo0:clone())) -- clone() is necessary here
end

return TestClass