local TestClass = class("ActionTestBase", require("src.TestBase"))

function TestClass:createSprites(num)
    self.spriteGrossini = cc.Sprite:create("res/Images/grossini.png")
    self:addChild(self.spriteGrossini)
    
    self.spriteTamara = cc.Sprite:create("res/Images/grossinis_sister1.png")
    self:addChild(self.spriteTamara)
    
    self.spriteKathia = cc.Sprite:create("res/Images/grossinis_sister2.png")
    self:addChild(self.spriteKathia)

    if num == 1 then
        self.spriteGrossini:setPosition(display.cx, display.cy)
        self.spriteTamara:setVisible(false)
        self.spriteKathia:setVisible(false)
    elseif num == 2 then
        self.spriteGrossini:setVisible(false)
        self.spriteTamara:setPosition(display.left+display.width*2/3, display.bottom+display.height/2)
        self.spriteKathia:setPosition(display.left+display.width/3, display.bottom+display.height/2)
    elseif num == 3 then
        self.spriteGrossini:setPosition(display.cx, display.cy)
        self.spriteTamara:setPosition(display.left+display.width/4, display.bottom+display.height/2)
        self.spriteKathia:setPosition(display.left+display.width*3/4, display.bottom+display.height/2)
    end
end

return TestClass
