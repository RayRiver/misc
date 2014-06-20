
local GameObject = require("app.classes.game_object")
local InputLayer = require("app.classes.input_layer")
local AnimationController = require("app.components.animation_controller")

local SCENE_NAME = "GameScene"

local SceneClass = class(SCENE_NAME, function() 
    local scene = display.newScene()
    return scene
end)

function SceneClass:ctor()
    self:registerScriptHandler(function(event) 
        printInfo(SCENE_NAME .. " event: " .. tostring(event))
    end)
    
    self:setNodeDrawEnabled(true)
    self:setNodeDrawDebugEnabled(true)
    

    --local player = GameObject.new()
    --player:setPosition(display.cx, display.cy)
    --self:addChild(player)
    
    local player = GameEntity:create()
    player:setPosition(display.cx, display.cy)
    self:addChild(player)
    
    local component = AnimationController.new()
    component:registerHandler("enter", function()
        printInfo("component enter")
    end)
    component:registerHandler("exit", function()
        printInfo("component exit")
    end)
    component:registerHandler("frame", function(dt)
        --printInfo("component frame %f", dt)
    end)

    player:addComponent(component)

    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/animation.ExportJson")
    component:load("animation"):play("run")


    
    
    
    local inputLayer = InputLayer.new()
    inputLayer:registerPressedHandler(function(action) 
        if action == "left" then
            local scale_x = player:getScaleX()
            if scale_x > 0 then
                player:setScaleX(scale_x * (-1))
            end
        elseif action == "right" then
            local scale_x = player:getScaleX()
            if scale_x < 0 then
                player:setScaleX(scale_x * (-1))
            end
        end
    end)
    self:addChild(inputLayer)

end

return SceneClass
