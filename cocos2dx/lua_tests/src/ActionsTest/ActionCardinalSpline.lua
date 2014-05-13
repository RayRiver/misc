local TestClass = class("ActionCardinalSpline", require("src.ActionsTest.ActionTestBase"))

function TestClass:onEnter()
    self:setDesc("CardinalSplineBy / CardinalSplineTo")


    self:createSprites(2)

    -- sprite 1
    local position1 = cc.p(self.spriteTamara:getPosition())
    local points1 = {
        cc.p(0,0),
        cc.p(100,100), 
        cc.p(-100,100),
        cc.p(100,-200),
    }

    -- sprite 1 calc track
    self.track_points1 = {}
    for _, p in pairs(points1) do
        local track_p = cc.pAdd(position1, p)
        table.insert(self.track_points1, track_p)
    end
    
    -- sprite 1 action
    local action = cc.CatmullRomBy:create(3, points1)
    local actionReverse = action:reverse()
    self.spriteTamara:runAction(cc.Sequence:create(action,actionReverse))
    self.spriteTamara:runAction(cc.RepeatForever:create(
        cc.Sequence:create(
            cc.MoveBy:create(0.05,cc.p(10,0)),
            cc.MoveBy:create(0.05,cc.p(-10,0))
        )
    ))
    
    -- sprite 2
    local position2 = cc.p(self.spriteKathia:getPosition())
    local points2 = {
        position2,
        cc.p(100,100), 
        cc.p(400,100),
        cc.p(100,300),
    }
    
    -- sprite 2 calc track
    self.track_points2 = points2
    
    -- sprite 2 action
    local action = cc.CatmullRomTo:create(3, points2)
    local actionReverse = action:reverse()
    self.spriteKathia:runAction(cc.Sequence:create(action,actionReverse))
    self.spriteKathia:runAction(cc.RepeatForever:create(
        cc.Sequence:create(
            cc.MoveBy:create(0.05,cc.p(0,10)),
            cc.MoveBy:create(0.05,cc.p(0,-10))
        )
    ))
    
    self:registerOnDraw()
end

function TestClass:onDraw()
    cc.DrawPrimitives.drawColor4F(255, 255, 255, 255)
    cc.DrawPrimitives.drawPoly(self.track_points1, #self.track_points1, false)
    cc.DrawPrimitives.drawPoly(self.track_points2, #self.track_points2, false)

    --self:onDrawDebug()
end

function TestClass:onDrawDebug()
    local function _drawNode(node)
        if not node:isVisible() then return end
    
        local x, y = node:getPosition()
        local size = node:getContentSize()
        cc.DrawPrimitives.drawRect(cc.p(x-size.width/2, y-size.height/2),
            cc.p(x+size.width/2, y+size.height/2))
    end
    
    local function drawNodes(node)
        _drawNode(node)
        local children = node:getChildren()
        for _, n in pairs(children) do
            drawNodes(n)
        end
    end
 
 
    cc.DrawPrimitives.drawColor4F(255, 255, 0, 255)
    local vertexes = 
    {
        0, 0, 10000,
        0, 200, 10000,
        200, 200, 10000,
        200, 0, 10000,
    }
    gl.drawElements(gl.TRIANGLE_STRIP, 4, gl.UNSIGNED_INT, #vertexes, vertexes)
    

    --drawNodes(self)

end

return TestClass
