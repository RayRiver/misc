local TestClass = class("ActionFade", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("FadeIn / FadeOut")

    self:createSprites(2)
      
    local action1 = cc.FadeIn:create(3)
    local action2 = cc.FadeOut:create(1)
    self.spriteTamara:setOpacity(0)
    self.spriteTamara:runAction(cc.Sequence:create(action1,action2))
    
    local action3 = action2:clone()
    self.spriteKathia:runAction(cc.Sequence:create(
        action3,
        action3:reverse(),
        action3:reverse():reverse(),
        action3:reverse():reverse():reverse())
    )
end

return TestClass