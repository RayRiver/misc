
local lib = require("lib.init")

local drawDebug = false
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

    blackboard.player = player

    local config = require("data.objects.test_monster")
    monster = entity_manager:createEntity(config)
    monster:setPosition(300, 200)

    local width = 1000
    local height = 1000
    local gamera_cam = lib.Gamera.new(0, 0, width, height)
    camera = lib.ShakyCam.new(gamera_cam)
end

function love.update(dt)
    function love.keypressed(key, unicdoe)
        if key == "tab" then
            drawDebug = not drawDebug
        elseif key == "escape" then
            love.event.push('quit')
        end
    end

    player:update(dt)
    monster:update(dt)

    camera:setPosition(player:getPosition())
    camera:update(dt)
end

function love.draw()
    camera:draw(function(x, y, w, h)
        if drawDebug then
            lib.BumpDebug.draw()
        end
        player:draw()
        monster:draw()
    end)
end
