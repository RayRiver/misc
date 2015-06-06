
local Utils = require("utils")
local SceneManager = require("scene_manager")
local Player = require("player")
local TiledMap = require("tiledmap")

local SceneClass = Utils.Class("GameScene")

function SceneClass:initialize()
    self.m_camera = Utils.Camera:new()
    self.m_camera:zoom(3)
    self.m_camera:lookAt(0, 0)

    --TiledMap_Load(string.format("data/map/test.tmx"))
    --[[
    self.m_tiled_map = Utils.Tiled.Map:new()
    self.m_tiled_map:load("data/map/home")
    self.m_tiled_map:setPos(0, 0)
    --]]

    self.m_tiled_map = TiledMap:new()

    self.m_player = Player:new()

end

function SceneClass:collide(a, b)
    if Utils.rectIntersect(a, b) then
        a:onOverlap(b)
        b:onOverlap(a)
    end
end

function SceneClass:update(dt)
    self.m_player:update(dt)

    self:collide(self.m_player, self.m_tiled_map)

    local cx, cy = self.m_camera:pos()
    local dx, dy = self.m_player.x - cx, self.m_player.y - cy
    self.m_camera:move(dx/10, dy/10)
end

function SceneClass:draw()
    local cx, cy = self.m_camera:pos()

    self.m_camera:draw(function()
        --TiledMap_DrawNearCam(0, 0)
        self.m_tiled_map:draw()

        self.m_player:draw()


    end)
end

return SceneClass
