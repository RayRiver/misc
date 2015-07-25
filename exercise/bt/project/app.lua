
require("init")

local lib = require("lib.init")
local utils = require("utils.init")

local drawDebug = false
local camera
local player
local monster
local blackboard = {}

function love.load()
    print("load...")

    local world = lib.Bump.newWorld()
    lib.BumpDebug.setWorld(world)

    utils.EntityMgr:setWorld(world)
    utils.EntityMgr:setBlackboard(blackboard)

    local config = require("data.objects.test_player")
    player = utils.EntityMgr:createEntity(config)
    player:setPosition(100, 100)

    blackboard.player = player

    local config = require("data.objects.test_monster")
    monster = utils.EntityMgr:createEntity(config)
    monster:setPosition(300, 200)

    local width = 1000
    local height = 1000
    local gamera_cam = lib.Gamera.new(0, 0, width, height)
    camera = lib.ShakyCam.new(gamera_cam)

    utils.Camera = camera.camera
end

function love.update(dt)
    function love.keypressed(key, unicdoe)
        if key == "tab" then
            drawDebug = not drawDebug
        elseif key == "escape" then
            love.event.push('quit')
        end
    end

    utils.CronMgr:update(dt)

    utils.EntityMgr:update(dt)

    camera:setPosition(player:getPosition())
    camera:update(dt)
end

function love.draw()
    camera:draw(function(x, y, w, h)
        if drawDebug then
            lib.BumpDebug.draw()
        end

        utils.EntityMgr:draw()
    end)
end
