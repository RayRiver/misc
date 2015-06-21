
local Utils = require("utils")
local Block = require("entities.block")
local Blockman = require("entities.blockman")
local Input = require("input")

local function inputFunc(entity, dt)
    local RUN_ACCEL = 300
    local BRAKE_ACCEL = 3000
    local JUMP_VELOCITY = 1000

    local vx, vy = entity.vx, entity.vy

    if love.keyboard.isDown("a") then
        vx = -500--vx - RUN_ACCEL * dt--(vx > 0 and BRAKE_ACCEL or RUN_ACCEL) * dt
    elseif love.keyboard.isDown("d") then
        vx = 500--vx + RUN_ACCEL * dt--(vx < 0 and BRAKE_ACCEL or RUN_ACCEL) * dt
    else
        vx = 0
    end

    local inputs = Input:instance():popInputs()
    if inputs["k"] and entity.onGround then
        vy = -JUMP_VELOCITY
    end

    entity.vx, entity.vy = vx, vy
end

local SceneClass = Utils.Class("GameScene")

function SceneClass:initialize(config)
    config = config or {}

    self.width = 2000
    self.height = 1000
    local gamera = Utils.Gamera.new(0, 0, self.width, self.height)
    self.camera = Utils.ShakyCam.new(gamera)

    self.world = Utils.Bump.newWorld()

    Block:new(self.world, {
        x = 0,
        y = 0,
        width = self.width,
        height = 32,
    })
    Block:new(self.world, {
        x = 0,
        y = self.height - 32,
        width = self.width,
        height = 32,
    })
    Block:new(self.world, {
        x = 0,
        y = 32,
        width = 32,
        height = self.height - 64,
    })
    Block:new(self.world, {
        x = self.width - 32,
        y = 32,
        width = 32,
        height = self.height - 64,
    })

    for i = 1, 200 do
        Block:new(self.world, {
            x = math.random(200, self.width - 200),
            y = math.random(200, self.height - 200),
            width = math.random(32, 100),
            height = math.random(32, 100),
        })
    end

    self.player = Blockman:new(self.world, {
        x = 100, y = 100,
    })
    self.player:connectInput(inputFunc)

    self.enemy = Blockman:new(self.world, {
        x = 50, y = 100,
        r = 200, g = 100, b = 100, opacity = 1,
    })
end

function SceneClass:update(dt)
    local visibleObjects, len = self.world:queryRect(0, 0, self.width, self.height)
    for i = 1, len do
        visibleObjects[i]:update(dt)
    end

    self.camera:setPosition(self.player.x, self.player.y)
    self.camera:update(dt)
end

function SceneClass:draw(drawDebug)
    self.camera:draw(function()
        if drawDebug then
            Utils.BumpDebug.draw(self.world, 0, 0, self.width, self.height)
        end

        local visibleObjects, len = self.world:queryRect(0, 0, self.width, self.height)
        for i = 1, len do
            visibleObjects[i]:draw(drawDebug)
        end
    end)
end

return SceneClass
