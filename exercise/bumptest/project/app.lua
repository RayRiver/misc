
local Utils = require("utils")
local Map = require("map")

local UPDATE_RADIUS = 100

local drawDebug = false
local width, height = 4000, 2000


local map
local camera

function love.load()
    camera = Utils.Camera.new(0, 0, width, height)
    camera = Utils.ShakyCam.new(camera)
    map = Map:new(width, height, camera)
end

function love.update(dt)
    local x, y, w, h = camera:getVisible()
    x, y, w, h = x - UPDATE_RADIUS, y - UPDATE_RADIUS, w + 2 * UPDATE_RADIUS, h + 2 * UPDATE_RADIUS

    --map:update(dt, x, y, w, h)
    map:update(dt, 0, 0, width, height)

    camera:setPosition(map.player:getCenter())
    camera:update(dt)
end

function love.draw()
    camera:draw(function(x, y, w, h)
        map:draw(drawDebug, x, y, w, h)
    end)
end

function love.keypressed(k)
    if k == "escape" then
        love.event.quit()
    elseif k == "tab" then
        drawDebug = not drawDebug
    elseif k == "return" then
        map:reset()
    elseif k == "backspace" then
        print("collect")
        collectgarbage("collect")
    else
        local Input = require("input")
        Input:instance():pushInput(k)
    end
end
