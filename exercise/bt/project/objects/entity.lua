
local lib = require("lib.init")
local utils = require("utils.init")
local BT = require("lib.bt")

local ObjectClass = lib.Class("Entity")

function ObjectClass:initialize(config, id, world, blackboard)
    self.m_config = config
    self.m_id = id
    self.m_world = world
    self.m_blackboard = blackboard

    self.m_data = {}

    self.m_x, self.m_y = 0, 0
    self.m_vx, self.m_vy = 0, 0
    self.m_w, self.m_h = self.m_config.size.width, self.m_config.size.height

    if self.m_world then
        self.m_world:add(self, self.m_x, self.m_y, self.m_w, self.m_h)
    end

    if config.components then
        self.m_components = {}
        for _, component_config in ipairs(config.components) do
            self:addComponent(component_config.class, component_config.config)
        end
    end
end

function ObjectClass:destroy()
    self:removeAllComponents()

    self.m_config = nil
    self.m_blackboard = nil

    self.m_data = {}

    if self.m_world then
        self.m_world:remove(self)
    end
end

function ObjectClass:getId()
    return self.m_id
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

function ObjectClass:hasComponent(class_name)
    return self.m_components[class_name] and true or false
end

function ObjectClass:getConfig()
    return self.m_config
end

function ObjectClass:getBlackboard()
    return self.m_blackboard
end

function ObjectClass:update(dt)
    local x = self.m_x + self.m_vx * dt
    local y = self.m_y + self.m_vy * dt

    self:setPosition(x, y)

    if self.m_components then
        for _, com in pairs(self.m_components) do
            com:update(dt)
        end
    end
end

function ObjectClass:draw()
    if self.m_config.eyeshot then
        local x = self.m_x + self.m_w / 2
        local y = self.m_y + self.m_h / 2
        love.graphics.setColor(100, 255, 100, 30)
        love.graphics.circle("fill", x, y, self.m_config.eyeshot, 32)
        love.graphics.setColor(100, 255, 100, 60)
        love.graphics.circle("line", x, y, self.m_config.eyeshot, 32)
    end

    love.graphics.setColor(255, 100, 100, 155)
    love.graphics.rectangle("fill", self.m_x, self.m_y, self.m_w, self.m_h)
    love.graphics.setColor(255, 100, 100)
    love.graphics.rectangle("line", self.m_x, self.m_y, self.m_w, self.m_h)
end

function ObjectClass:setData(key, val)
    self.m_data[key] = val
end

function ObjectClass:getData(key)
    return self.m_data[key]
end

function ObjectClass:getPosition()
    return self.m_x, self.m_y
end

function ObjectClass:setPosition(x, y)
    self.m_x, self.m_y = x, y

    if self.m_world then
        self.m_world:update(self, self.m_x, self.m_y)
    end
end

function ObjectClass:getVelocity()
    return self.m_vx, self.m_vy
end

function ObjectClass:setVelocity(vx, vy)
    self.m_vx, self.m_vy = vx, vy
end

function ObjectClass:attack(target)
    if self.m_attack_cool_down then
        return
    end

    print("attack")
    target:hit()

    self.m_attack_cool_down = true
    utils.CronMgr:after(2, function()
        self.m_attack_cool_down = false
    end)
end

function ObjectClass:hit()
    self.m_hp = self.m_hp or 3
    self.m_hp = self.m_hp - 1
    print("hit, hp = " .. tostring(self.m_hp))
    if self.m_hp <= 0 then
        self.m_hp = 0
        self:setData("dead", true)
    end
end

return ObjectClass

