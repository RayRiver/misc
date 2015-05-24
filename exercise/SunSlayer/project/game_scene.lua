
local Utils = require("utils")
local Hydrant = require("hydrant")
local Sun = require("sun")
local SceneManager = require("scene_manager")

local SceneClass = Utils.Class("GameScene")

function SceneClass:initialize()
    self.m_cloud_sprite = love.graphics.newImage("data/texture/cloud.png")
    self.m_stars_sprite = love.graphics.newImage("data/texture/stars.png")
    self.m_soil_sprite = love.graphics.newImage("data/texture/soil.png")
    self.m_warning_sprite = love.graphics.newImage('data/texture/warning.png')
    self.m_indicator_sprite = love.graphics.newImage('data/texture/indicator.png')

    self.m_font = love.graphics.newFont('data/font/red-alert.ttf', 26)
    self.m_big_font = love.graphics.newFont('data/font/upheaval.ttf', 40)
    love.graphics.setFont(self.m_font)

    love.audio.setVolume(0.5)

    self.m_hydrant = Hydrant:new()
    self.m_sun = Sun:new()

    self.m_camera = Utils.Camera:new()
    self.m_camera:lookAt(self.m_sun.x, self.m_sun.y)

    self.m_is_title = true
end

function SceneClass:update(dt)
    local camera = self.m_camera

    if self.m_is_title then
        function love.keypressed(key)
            if key == 'return' then
                if self.m_is_title then
                    self.m_is_title = false
                end
            elseif key == 'escape' then
                if self.m_is_title then
                    love.event.push('quit')
                else
                    SceneManager:instance():replaceScene(SceneClass:new())
                end
            end
        end
    else
        local cx, cy = self.m_camera:pos()
        local dx, dy = self.m_hydrant.x - cx, self.m_hydrant.y - cy
        dx, dy = dx/10, dy/10
        self.m_camera:move(dx, dy)
        self.m_camera.y = math.min(self.m_camera.y, -96)
    end

    local height = -96 - camera.y
    local ds = 1/(1 + height/1200) - camera.scale
    camera.scale = camera.scale + ds/10
    if height < 1200 then
        love.graphics.setBackgroundColor(45 - 35*height/1200, 80 - 80*height/1200, 120 - 100*height/1200)
    else
        love.graphics.setBackgroundColor(10, 0, 20)
    end

    if not self.m_is_title then
        self.m_hydrant:update(dt)
    end
    self.m_sun:update(dt)
end

function SceneClass:draw()
    local sw, sh = love.graphics.getWidth(), love.graphics.getHeight()

    local height = -96 - self.m_camera.y
    if height < 3000 then
        love.graphics.setColor(255, 255, 255, height*255/3000)
    end
    love.graphics.draw(self.m_stars_sprite, -self.m_camera.x/50, -self.m_camera.y/50, 0, 2, 2)
    love.graphics.setColor(255, 255, 255, 255)
    
    self.m_camera:draw(function()
        local left = self.m_camera.x - sw/2/self.m_camera.scale
        love.graphics.draw(self.m_cloud_sprite, math.floor(left/1200)*1200 + 900, -220, 0, 2, 2)

        self.m_hydrant:draw()
        self.m_sun:draw()

        local left = math.floor(self.m_camera.x/32)*32 - sw/2 - 256
        for i = left, left + sw + 512, 32 do
            love.graphics.draw(self.m_soil_sprite, i, 0, 0, 2, 2)
        end

        for i = -96, 96, 16 do
            love.graphics.draw(self.m_warning_sprite, i - 8, 0, 0, 2, 2)
        end
    end)

    if self.m_is_title then
        local title = 'SUN SLAYER'
        local subtitle = 'Press ENTER to start'
        love.graphics.setColor(10, 0, 20)
        love.graphics.setFont(self.m_big_font)
        love.graphics.print(title, sw/2 - self.m_big_font:getWidth(title)/2, sh/2 - self.m_big_font:getHeight()/2 - 12)
        love.graphics.setFont(self.m_font)
        love.graphics.print(subtitle, sw/2 - self.m_font:getWidth(subtitle)/2, sh/2 - self.m_font:getHeight()/2 + 12)
        love.graphics.setColor(255, 255, 255)
    else
        local hydrant = self.m_hydrant
        love.graphics.print(hydrant.m_water, 16, 8)
        love.graphics.print('gal', 70, 8)
        love.graphics.setColor(128, 255, 255)
        love.graphics.rectangle('fill', 108, 18, 100*hydrant.m_water/hydrant.m_water_max, 10)
        love.graphics.rectangle('line', 108, 18, 100, 10)
        love.graphics.setColor(255, 255, 255)

        local sun = self.m_sun
        love.graphics.print(sun.m_hp, 412, 8)
        love.graphics.print('sun', 475, 8)
        love.graphics.setColor(255, 128, 128)
        love.graphics.rectangle('fill', 520, 18, 100*sun.m_hp/sun.m_hp_max, 10)
        love.graphics.rectangle('line', 520, 18, 100, 10)
        love.graphics.setColor(255, 255, 255)

        local dx, dy = hydrant.x - sun.x, hydrant.y - sun.y
        local dist = math.sqrt(dx*dx + dy*dy) - sun.r
        if dist > 200 then
            local delta = dist - 200
            local d = 1000 - delta
            if d < 0 then d = 0 end
            local scale = d / 2000 + 0.5

            local angle = math.atan2(dy, dx)
            love.graphics.setColor(255, 255, 0)
            love.graphics.draw(self.m_indicator_sprite,
                sw/2 - 160*math.cos(angle),
                sh/2 - 160*math.sin(angle),
                angle - math.pi/2,
                scale, scale,
                8, 8)
        end
    end
end

return SceneClass
