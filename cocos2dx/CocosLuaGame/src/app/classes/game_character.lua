
local AnimationController = require("app.components.animation_controller")
local StateMachine = require("app.components.state_machine")

local OBJECT_NAME = "GameCharacter"

local ObjectClass = class(OBJECT_NAME, function() 
    local obj = GameEntity:create() 
    return obj
end)

ObjectClass.DIRECTION_LEFT = -1
ObjectClass.DIRECTION_RIGHT = 1

function ObjectClass:ctor()
    -- animation controller
    local ani = AnimationController.new()
    self:addComponent(ani)
    self.ani = ani
    
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("animation/animation.ExportJson")
    self.ani:load("animation", function(movementType, movementID) 
        if movementID == "attack_down" then
            if movementType == ccs.MovementEventType.complete then
                self.fsm:doEvent("doIdle")
            end
        end
    end)
    
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
            { name="doAction1", from={"idle", "run", "walk"}, to="action1" },
        },

        callbacks =
        {
            on_idle = function(event) self:onIdle() end,
            on_walk = function(event) self:onWalk() end,
            on_run = function(event) self:onRun() end,
            on_action1 = function(event) self:onAttack() end,
        },

    }
    local fsm = StateMachine.new()
    fsm:setupState(cfg)
    self:addComponent(fsm)
    self.fsm = fsm
    
    -- position
    self.desiredPositionX = self:getPositionX()
    self.desiredPositionY = self:getPositionY()
    
    -- node event
    self:registerScriptHandler(function(event)
        if event == "enter" then
            self:onEnter()
        end
    end)
    

    
    -- schedule update
    self:scheduleUpdateWithPriorityLua(handler(self, self.onFrame), 0)
end

function ObjectClass:onEnter()
    self.ani:play("run")
    
    self.fsm:doEvent("doStartup")
end

function ObjectClass:onFrame(dt)
    

    local state = self.fsm:getState()
    
    if state == "walk" then
        local speed = 2
        local direction = self:getDirection()      
        self.desiredPositionX = self:getPositionX() + speed * direction
    elseif state == "run" then
        local speed = 4
        local direction = self:getDirection()      
        self.desiredPositionX = self:getPositionX() + speed * direction
    end
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

function ObjectClass:onAttack()
    self.ani:play("attack_down")
end

function ObjectClass:doIdle()
    if self.fsm:canDoEvent("doIdle") then self.fsm:doEvent("doIdle") end
end

function ObjectClass:doWalk(direction)
    if self.fsm:canDoEvent("doWalk") then 
        self:changeDirection(direction)
        self.fsm:doEvent("doWalk") 
    end
end

function ObjectClass:doRun(direction)
    if self.fsm:canDoEvent("doRun") then 
        self:changeDirection(direction)
        self.fsm:doEvent("doRun") 
    end
end

function ObjectClass:doAttack()
    if self.fsm:canDoEvent("doAction1") then 
        self.fsm:doEvent("doAction1") 
    end
end

function ObjectClass:getDirection()
    return self:getScaleX()>0 and ObjectClass.DIRECTION_RIGHT or ObjectClass.DIRECTION_LEFT
end

function ObjectClass:changeDirection(direction)
    local current_direction = self:getDirection()
    if current_direction * direction < 0 then
        self:setScaleX(self:getScaleX() * (-1))
    end
end

function ObjectClass:getDesiredPosition()
    return self.desiredPositionX, self.desiredPositionY
end

function ObjectClass:setDesiredPosition(x, y)
    self.desiredPositionX = x
    self.desiredPositionY = y
end

return ObjectClass

