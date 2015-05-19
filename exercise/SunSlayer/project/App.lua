
local SceneManager = require("SceneManager")
local GameScene = require("GameScene")

function love.load()
    love.graphics.setBackgroundColor(145, 145, 145)
    
    SceneManager:instance():replaceScene(GameScene:new())
end

function love.update(dt)
    SceneManager:instance():getRunningScene():update(dt)
    
	if love.keyboard.isDown('escape') then
		love.event.push('quit')
	end
end

function love.draw()
    SceneManager:instance():getRunningScene():draw()
end
