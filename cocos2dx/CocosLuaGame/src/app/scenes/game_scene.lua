
local GameCharacter = require("app.classes.game_character")
local InputManager = require("app.classes.input_manager")

local SCENE_NAME = "GameScene"

local SceneClass = class(SCENE_NAME, function() 
    local scene = display.newScene(SCENE_NAME)
    return scene
end)

function SceneClass:ctor()
    -- debug mode
    self:setNodeDrawEnabled(true)
    self:setNodeDrawDebugEnabled(true)
    

    -- create new player
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/Cowboy.ExportJson")
    local player = GameCharacter.new("Cowboy")
    player:setScale(0.1)
    player:setPosition(display.cx, display.cy)
    player:setDesiredPosition(display.cx, display.cy)
    self:addChild(player)
    self.player = player


    -- create input manager
    local inputManager = InputManager.new()
    self:addChild(inputManager)
    self.inputManager = inputManager

    -- schedule update
    self:scheduleUpdateWithPriorityLua(handler(self, self.onFrame), 0)
end

function SceneClass:onEnter()
    local player = self.player
    
    self.inputManager:registerInputBeganHandler(InputManager.LEFT, function() 
        player:doRun(GameCharacter.DIRECTION_LEFT)
    end)
    self.inputManager:registerInputEndedHandler(InputManager.LEFT, function() 
        player:doIdle()
    end)
    self.inputManager:registerInputBeganHandler(InputManager.RIGHT, function() 
        player:doRun(GameCharacter.DIRECTION_RIGHT)
    end)
    self.inputManager:registerInputEndedHandler(InputManager.RIGHT, function() 
        player:doIdle()
    end)
    
    self.inputManager:registerInputBeganHandler(InputManager.ACTION1, function() 
        player:doAttack()
    end)
end

function SceneClass:onFrame(dt)
    local player = self.player
    
    
    
    local desiredPositionX, desiredPositionY = player:getDesiredPosition()
    player:setPosition(desiredPositionX, desiredPositionY)
    

    local bCollider = player:checkCollider(cc.rect(0, display.cy, 50, 50))
    if bCollider then
        printInfo("collider")
    end
end

return SceneClass
