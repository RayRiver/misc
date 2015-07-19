
local lib = require("lib.init")

local camera
local player
local monster
local blackboard = {}

function love.load()
    print("load...")

    local world = lib.Bump.newWorld()
    lib.BumpDebug.setWorld(world)

    local entity_manager = require("objects.entity_manager"):instance()
    entity_manager:setWorld(world)
    entity_manager:setBlackboard(blackboard)

    local config = require("data.objects.test_player")
    player = entity_manager:createEntity(config)
    player:setPosition(100, 100)

    local config = require("data.objects.test_monster")
    monster = entity_manager:createEntity(config)
    monster:setPosition(300, 200)

    local width = 1000
    local height = 1000
    local gamera_cam = lib.Gamera.new(0, 0, width, height)
    camera = lib.ShakyCam.new(gamera_cam)
end

function love.update(dt)
    if love.keyboard.isDown('escape') then
        love.event.push('quit')
    end

    player:update(dt)
    monster:update(dt)

    camera:setPosition(player:getPosition())
    camera:update(dt)
end

function love.draw()
    camera:draw(function(x, y, w, h)
        lib.BumpDebug.draw()
        player:draw()
        monster:draw()
    end)
end
