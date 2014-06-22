
local AnimationController = require("app.components.animation_controller")
local StateMachine = require("app.components.state_machine")

local OBJECT_NAME = "GameCharacter"

local ObjectClass = class(OBJECT_NAME, function() 
    local obj = GameEntity:create() 
    return obj
end)

function ObjectClass:ctor()
    -- animation controller
    local ani = AnimationController.new()
    self:addComponent(ani)
    self.ani = ani
    
    -- state machine
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
            on_idle = function(event) self:onIdle() end,
            on_walk = function(event) self:onWalk() end,
            on_run = function(event) self:onRun() end,
        },

    }
    local fsm = StateMachine.new()
    fsm:setupState(cfg)
    self:addComponent(fsm)
    self.fsm = fsm
    
    -- node event
    self:registerScriptHandler(function(event)
        if event == "enter" then
            self:onEnter()
        end
    end)
end

function ObjectClass:onEnter()
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/animation.ExportJson")
    self.ani:load("animation"):play("run")
    
    self.fsm:doEvent("doStartup")
end

function ObjectClass:onIdle()
    self.ani:play("idle")
end

function ObjectClass:onWalk()
    self.ani:play("walk")
end

function ObjectClass:onRun()
    self.ani:play("run")
end

function ObjectClass:doIdle()
    self.fsm:doEvent("doIdle")
end

function ObjectClass:doWalk()
    self.fsm:doEvent("doWalk")
end

function ObjectClass:doRun()
    self.fsm:doEvent("doRun")
end

return ObjectClass
