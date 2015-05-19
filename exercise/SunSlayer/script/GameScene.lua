
local Utils = require("Utils")

local SceneClass = Utils.Class("GameScene")

function SceneClass:initialize()
    self.m_cloud_sprite = love.graphics.newImage("texture/cloud.png")
end

function SceneClass:update(dt)
    
end

function SceneClass:draw()
    love.graphics.draw(self.m_cloud_sprite, 100, 120, 0, 2, 2)
end

return SceneClass
