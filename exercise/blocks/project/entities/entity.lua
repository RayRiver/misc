
local Utils = require("utils")

local ObjectClass = Utils.Class("Entity")

local GRAVITY_ACCEL = 2000

function ObjectClass:initialize(world, config)
    config = config or {}

    self.world = world

    self.x, self.y = config.x or 0, config.y or 0
    self.width, self.height = config.width or 1, config.height or 1
    self.r = config.r or 255
    self.g = config.g or 255
    self.b = config.b or 255
    self.opacity = config.opacity or 1
    self.static = config.static or false

    self.vx, self.vy = 0, 0
    self.onGround = false

    self.world:add(self, self.x, self.y, self.width, self.height)
end

function ObjectClass:destroy()
    self.world:remove(self)
end

function ObjectClass:getCenter()
    return self.x + self.width / 2, self.y + self.height / 2
end

function ObjectClass:connectInput(input_func)
    if type(input_func) == "function" then
        self.input_func = input_func
    end
end

function ObjectClass:disconnectInput()
    self.input_func = nil
end

local function changeVelocityByGravity(self, dt)
    self.vy = self.vy + GRAVITY_ACCEL * dt
end

local function moveColliding(self, dt)
    local desired_x = self.x + self.vx * dt
    local desired_y = self.y + self.vy * dt

    local next_x, next_y, cols, len = self.world:move(self, desired_x, desired_y, self.onCollideFilter)

    local onGround = false
    local onTop = false
    for i = 1, len do
        local col = cols[i]
        if col.normal.y < 0 then
            onGround = true
        end
        if col.normal.y > 0 then
            onTop = true
        end
    end

    self.onGround = onGround
    if onGround or onTop then
        self.vy = 0
    end

    self.x, self.y = next_x, next_y
end

function ObjectClass:update(dt)
    if type(self.input_func) == "function" then
        self.input_func(self, dt)
    end

    if not self.static then
        changeVelocityByGravity(self, dt)
        moveColliding(self, dt)
    end
end

function ObjectClass:draw()
    Utils.drawFilledRectangle(self.x, self.y, self.width, self.height,
        self.r, self.g, self.b, self.opacity)
end

return ObjectClass
