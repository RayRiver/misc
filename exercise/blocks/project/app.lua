
local Utils = require("utils")
local SceneManager = require("scene_manager")
local GameScene = require("game_scene")

local drawDebug = false

function love.load()
    love.graphics.setDefaultFilter("nearest", "nearest")

    SceneManager:instance():replaceScene(GameScene:new())
end

function love.update(dt)
    SceneManager:instance():getRunningScene():update(dt)
end

function love.draw()
    SceneManager:instance():getRunningScene():draw(drawDebug)
end

function love.keypressed(k)
    if k == "escape" then
        love.event.quit()
    elseif k == "tab" then
        drawDebug = not drawDebug
    elseif k == "return" then
        --map:reset()
    elseif k == "backspace" then
        print("collect")
        collectgarbage("collect")
    else
        local Input = require("input")
        Input:instance():pushInput(k)
    end
end
