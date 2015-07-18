
local lib = require("lib.init")
local BT = require("lib.bt")

local ObjectClass = lib.Class("Entity")

function ObjectClass:initialize(config, blackboard)
    config = config or {}
    self.m_config = config

    self.m_blackboard = blackboard

    self.m_x, self.m_y = 0, 0
    self.m_vx, self.m_vy = 0, 0

    if config.components then
        self.m_components = {}
        for _, component_config in ipairs(config.components) do
            self:addComponent(component_config.class, component_config.config)
        end
    end
end

function ObjectClass:destroy()
    self:removeAllComponents()
end

function ObjectClass:addComponent(class_name, config)
    self.m_components = self.m_components or {}

    if self.m_components[class_name] then
        assert(false)
        return
    end

    local component_class = require(class_name)
    local com = component_class:create(config)
    self.m_components[class_name] = com
    com:attach(self)
end

function ObjectClass:removeComponent(class_name)
    local com = self.m_components[class_name]
    if not com then
        assert(false)
        return
    end

    self.m_components[class_name] = nil
    com:detach()
end

function ObjectClass:removeAllComponents()
    if self.m_components then
        for _, com in pairs(self.m_components) do
            com:detach()
        end
        self.m_components = nil
    end
end

function ObjectClass:getConfig()
    return self.m_config
end

function ObjectClass:getBlackboard()
    return self.m_blackboard
end

function ObjectClass:update(dt)
    self.m_x = self.m_x + self.m_vx * dt
    self.m_y = self.m_y + self.m_vy * dt

    if self.m_components then
        for _, com in pairs(self.m_components) do
            com:update(dt)
        end
    end
end

function ObjectClass:draw()
    if self.m_config.eyeshot then
        love.graphics.setColor(100, 255, 100, 40)
        love.graphics.circle("fill", self.m_x, self.m_y, self.m_config.eyeshot, 32)
        love.graphics.setColor(100, 255, 100, 80)
        love.graphics.circle("line", self.m_x, self.m_y, self.m_config.eyeshot, 32)
    end

    love.graphics.setColor(255, 100, 100)
    love.graphics.circle("fill", self.m_x, self.m_y, 5, 32)
end

function ObjectClass:getPosition()
    return self.m_x, self.m_y
end

function ObjectClass:setPosition(x, y)
    self.m_x, self.m_y = x, y
end

function ObjectClass:getVelocity()
    return self.m_vx, self.m_vy
end

function ObjectClass:setVelocity(vx, vy)
    self.m_vx, self.m_vy = vx, vy
end

return ObjectClass

