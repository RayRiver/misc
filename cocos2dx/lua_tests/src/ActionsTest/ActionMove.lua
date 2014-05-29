local TestClass = class("ActionMove", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("MoveTo / MoveBy")

    self:createSprites(3)

    --[[
    local actionMoveTo = cc.MoveTo:create(2, cc.p(display.width-40, display.height-40))
    local actionMoveBy = cc.MoveBy:create(2, cc.p(80, 80))
    local actionMoveByBack = actionMoveBy:reverse()

    self.spriteTamara:runAction(actionMoveTo)
    self.spriteGrossini:runAction(cc.Sequence:create(actionMoveBy,actionMoveByBack))
    self.spriteKathia:runAction(cc.MoveTo:create(1,cc.p(40,40)))
    --]]
    
    transition.moveTo(self.spriteTamara, {
        x = display.width - 40,
        y = display.height - 40,
        time = 2,
    })
    
    local actionBy = cc.MoveBy:create(0.5, cc.p(80,80))
    transition.execute(self.spriteGrossini, 
        cc.Sequence:create(actionBy, actionBy:reverse()),
        {delay=1, onComplete = function()
            -- on complete callback
            transition.execute(self.spriteGrossini, cc.JumpBy:create(0.3,cc.p(0,0),30,1))
        end}
    )
    
    transition.moveTo(self.spriteKathia, {
        x = 40,
        y = 40,
        time = 2,
    })
end

return TestClass
