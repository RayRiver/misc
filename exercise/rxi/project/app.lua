
local SceneManager = require("scene_manager")
local GameScene = require("game_scene")

function love.load()
    --love.graphics.setBackgroundColor(145, 145, 145)

    love.graphics.setDefaultFilter("nearest", "nearest")

    SceneManager:instance():replaceScene(GameScene:new())
end

function love.update(dt)
    SceneManager:instance():getRunningScene():update(dt)

    if love.keyboard.isDown('escape') then
        --    love.event.push('quit')
    end
end

function love.draw()
    SceneManager:instance():getRunningScene():draw()
end

