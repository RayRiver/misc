
local GameCharacter = require("app.classes.game_character")

local SCENE_NAME = "PhysicsScene"

local SceneClass = class(SCENE_NAME, function() 
    local scene = display.newSceneWithPhysics(SCENE_NAME)
    return scene
end)

function SceneClass:ctor()
    -- border
    local node = display.newNode()
    node:setPhysicsBody(cc.PhysicsBody:createEdgeBox(cc.size(display.width, display.height)))
    node:setPosition(display.cx, display.cy)
    self:addChild(node)

    -- register touch event
    local touchListener = cc.EventListenerTouchOneByOne:create()
    touchListener:registerScriptHandler(function() return true end, cc.Handler.EVENT_TOUCH_BEGAN) 
    touchListener:registerScriptHandler(handler(self, self.onTouch), cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(touchListener, self)
    
    -- DEBUG DRAW
    local debug = false
    local function toggleDebugCallback(sender)
        debug = not debug
        cc.Director:getInstance():getRunningScene():getPhysicsWorld():
            setDebugDrawMask(debug and cc.PhysicsWorld.DEBUGDRAW_ALL or cc.PhysicsWorld.DEBUGDRAW_NONE)
    end

    self.toggleDebug = function(self) toggleDebugCallback(nil) end;
    cc.MenuItemFont:setFontSize(18)
    local item = cc.MenuItemFont:create("Toogle debug")
    item:registerScriptTapHandler(toggleDebugCallback)
    local menu = cc.Menu:create(item)
    self:addChild(menu)
    menu:setPosition(display.right - 70, display.top - 20)
end

function SceneClass:onEnter()

end

function SceneClass:onTouch(touch, event)
    printInfo("onTouch")
    local location = touch:getLocation()
    
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/Cowboy.ExportJson")
    local obj = GameCharacter.new("Cowboy")
    obj:setPosition(location)
    local scale = 0.1
    obj:setScale(scale)
    local size = obj:getContentSize()
    obj:setPhysicsBody(cc.PhysicsBody:createBox(cc.size(size.width*scale, size.height*scale)))
    self:addChild(obj)
end

return SceneClass
