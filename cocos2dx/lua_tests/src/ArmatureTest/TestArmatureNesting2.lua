local Hero = class("Hero", function() 
    local hero = ccs.Armature:create("hero")
    hero.mount = nil
    return hero
end)

function Hero:getMount()
    return self.mount
end

function Hero:setMount(mount)
    self.mount = mount
end

function Hero:getLayer()
    return self.layer
end

function Hero:setLayer(layer)
    self.layer = layer
end

function Hero:playWithIndex(index)
    self:getAnimation():playWithIndex(index)
    if self.mount then
        self.mount:getAnimation():playWithIndex(index)
    end
end

function Hero:changeMount(mount)
    if mount then
        self.mount = mount
        self:retain()
        self:removeFromParent(false) -- remove from layer
        local bone = mount:getBone("hero")
        bone:addDisplay(self, 0)
        bone:changeDisplayWithIndex(0, true)
        self:setPosition(0, 0)
        self:playWithIndex(1)
        self:setScale(1)
        self:release()
    elseif self.mount then
        self:retain()
        self:playWithIndex(0)
        self.mount:getBone("hero"):removeDisplay(0)
        self.mount:stopAllActions()
        self:setPosition(cc.p(self.mount:getPosition()))
        self:getLayer():addChild(self)
        self:release()
        self.mount = nil
    end
end

local TestClass = class("TestArmatureNesting2", require("src.ArmatureTest.ArmatureTestBase"))

function TestClass:onEnter()
    self:setDesc("")
    
    self:createBG()

    local function onAsyncLoaded() 
        -- create hero
        local hero = Hero.new()
        hero:setPosition(display.cx, display.cy)
        hero:getAnimation():playWithIndex(0)
        self:addChild(hero, 10000)
        hero:setLayer(self)
        
        -- create horse
        local horse = ccs.Armature:create("horse")
        horse:setPosition(100, 100)
        horse:getAnimation():playWithIndex(0)
        self:addChild(horse)
        
        -- create panda
        local panda = ccs.Armature:create("bear")
        panda:setPosition(300, 200)
        panda:getAnimation():playWithIndex(0)
        self:addChild(panda)
        
        -- create change button
        local label = cc.Label:createWithTTF({
            fontFilePath="res/fonts/arial.ttf", 
            fontSize=20
        }, "CHANGE MOUNT")
        local item = cc.MenuItemLabel:create(label)
        item:registerScriptTapHandler(function() 
            if hero:getMount() then
                hero:changeMount(nil)
            else
                local hero_x, hero_y = hero:getPosition()
                local horse_x, horse_y = horse:getPosition()
                local panda_x, panda_y = panda:getPosition()
                if cc.distance(cc.p(hero:getPosition()), cc.p(horse:getPosition())) < 20 then
                    hero:changeMount(horse)
                elseif cc.distance(cc.p(hero:getPosition()), cc.p(panda:getPosition())) < 30 then
                    hero:changeMount(panda)   
                end
            end
        end)
        local menu = cc.Menu:create(item)
        menu:setPosition(display.right-100, display.bottom+100)
        self:addChild(menu)
        
        -- register hero move event
        local listener = cc.EventListenerTouchAllAtOnce:create()
        listener:registerScriptHandler(function(touches, event) 
            local point = touches[1]:getLocation()
            
            local armature = hero:getMount() or hero
            
            -- set direction
            local current_x, current_y = armature:getPosition()
            if point.x < current_x then
                armature:setScaleX(-1)
            else
                armature:setScaleX(1)
            end
            
            -- calc action time
            local distance = math.sqrt((current_x-point.x)*(current_x-point.x)
                +(current_y-point.y)*(current_y-point.y))
            local time = distance / 200
            
            -- create action
            local action = cc.MoveTo:create(time, point)
            armature:stopAllActions()
            armature:runAction(cc.Sequence:create(action))
        end, cc.Handler.EVENT_TOUCHES_ENDED)
        self:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, self)
    end
    
    self:asyncLoad(onAsyncLoaded)  
end

return TestClass
