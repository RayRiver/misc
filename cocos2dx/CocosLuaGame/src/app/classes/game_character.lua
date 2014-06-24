
local ACTION_IDLE = "Walk"
local ACTION_WALK = "Walk"
local ACTION_RUN = "Walk"
local ACTION_ATTACK = "Fire"

--local AnimationController = require("app.components.animation_controller")
local StateMachine = require("app.components.state_machine")

local OBJECT_NAME = "GameCharacter"

local ObjectClass = class(OBJECT_NAME, function() 
    local obj = GameEntity:create() 
    return obj
end)

ObjectClass.DIRECTION_LEFT = -1
ObjectClass.DIRECTION_RIGHT = 1

function ObjectClass:ctor(animationName)
    -- animation controller
    local ani = AnimationController:create()
    self:addComponent(ani)
    self.ani = ani
    
    self.ani:load(animationName)
    self.ani:setMovementEventCallFunc(function(movementType, movementID) 
        if movementID == ACTION_ATTACK then
            if movementType == ccs.MovementEventType.complete or
                movementType == ccs.MovementEventType.loopComplete then
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

function ObjectClass:getContentSize()
    return self.ani:getArmature():getContentSize()
end

function ObjectClass:onEnter()
    self.fsm:doEvent("doStartup")
end

function ObjectClass:onFrame(dt)
    --[[
    local boneDict = self.ani.armature:getBoneDic()
    for type, bone in pairs(boneDict) do
        printInfo("%s = %s", tostring(type), tostring(bone))
        local detector = bone:getColliderDetector()
        if detector then
            local bodyList = ccs.ColliderDetector:getColliderBodyList
        end
    end
    --]]
    --self.ani.armature:drawContour()

    
    local state = self.fsm:getState()
    
    if state == "idle" then
        --self:fsm:doEvent("doWalk")
    elseif state == "walk" then
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
    self.ani:play(ACTION_IDLE)
end

function ObjectClass:onWalk()
    self.ani:play(ACTION_WALK)
end

function ObjectClass:onRun()
    self.ani:play(ACTION_RUN)
end

function ObjectClass:onAttack()
    self.ani:play(ACTION_ATTACK)
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
    -- TODO: 该资源方向刚好相反
    --if self:getScaleX() * ObjectClass.DIRECTION_RIGHT < 0 then
    if self:getScaleX() * ObjectClass.DIRECTION_RIGHT > 0 then
        return ObjectClass.DIRECTION_LEFT
    else
        return ObjectClass.DIRECTION_RIGHT
    end

    --return self:getScaleX()>0 and ObjectClass.DIRECTION_RIGHT or ObjectClass.DIRECTION_LEFT
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

function ObjectClass:checkCollider(rect)
    return self.ani:checkCollider(rect)
end

return ObjectClass

