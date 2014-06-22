
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
    local player = GameCharacter.new()
    player:setPosition(display.cx, display.cy)
    self:addChild(player)
    self.player = player


    -- create input manager
    local inputManager = InputManager.new()
    self:addChild(inputManager)
    self.inputManager = inputManager

end

function SceneClass:onEnter()
    self.inputManager:registerInputBeganHandler("left", function() 
        local scale_x = self.player:getScaleX()
        if scale_x > 0 then
            self.player:setScaleX(scale_x * (-1))
        end
    end)
    self.inputManager:registerInputBeganHandler("right", function() 
        local scale_x = self.player:getScaleX()
        if scale_x < 0 then
            self.player:setScaleX(scale_x * (-1))
        end
    end)
end

return SceneClass
