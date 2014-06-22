
local GameObject = require("app.classes.game_object")
local InputLayer = require("app.classes.input_layer")
local AnimationController = require("app.components.animation_controller")
local StateMachine = require("app.components.state_machine")

local SCENE_NAME = "GameScene"

local SceneClass = class(SCENE_NAME, function() 
    local scene = display.newScene(SCENE_NAME)
    return scene
end)

function SceneClass:ctor()
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



    local cfg = {
        events =
        {
            { name="doStartup", from=StateMachine.STATE_READY, to="idle" },
            { name="doIdle", from=nil, to="idle" },
            { name="doWalk", from="idle", to="walk" },
            { name="doWalk", from="run", to="walk" },
            { name="doRun", from="idle", to="run" },
            { name="doRun", from="walk", to="run" },
        },

        callbacks =
        {
            on_before_doStartup = function(event) printInfo("before do Startup") end,
            on_before_doIdle = function(event) printInfo("before do Idle") end,
            on_after_doIdle = function(event) printInfo("after do Idle") end,
        },

    }
    local component = StateMachine.new()
    component:setupState(cfg)
    player:addComponent(component)
    
    self.player = player
    
    
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

function SceneClass:onEnter()
    self.player:getComponent("StateMachine"):doEvent("doStartup")
end

return SceneClass
